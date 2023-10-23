/*
 *	@File	DrawTexture.cpp
 *	@Brief	描画ヘルパークラス
 *	@Date	2023-10-23
 *  @Author Ryo
 */

#include <Siv3D.hpp>

#include "DrawTexture.hpp"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="引数無し"></param>
/// <returns>なし</returns>
DrawTexture::DrawTexture()
	: m_textures{}						// テクスチャ配列
{
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param name="引数無し"></param>
/// <returns>なし</returns>
DrawTexture::~DrawTexture()
{
	m_textures.clear();
}

/// <summary>
/// テクスチャを追加する関数
/// </summary>
/// <param name="key">登録キーの文字列(U"文字列")</param>
/// <param name="path">ファイルパスの文字列</param>
/// <returns>なし</returns>
void DrawTexture::AddTexture(const char32_t* key, const char32_t* path)
{
	// 画像の登録
	Texture _input{ path };
	m_textures.emplace(key, _input);
}

/// <summary>
/// 登録したテクスチャを描画する関数
/// </summary>
/// <param name="key">登録キーの文字列(U"文字列")</param>
/// <param name="pos">描画する位置</param>
/// <param name="scale">拡大率(デフォルトは1.0)</param>
/// <param name="rotate>回転率(デフォルトは0.0)</param>
/// <param name="mirrored">左右反転フラグ(デフォルトはfalse)</param>
/// <param name="flipped">上下反転フラグ(デフォルトはfalse)</param>
/// <returns>なし</returns>
void DrawTexture::Draw(const char32_t* key, const Vec2& pos, const double& scale, const double& rotate,
	const bool& mirrored, const bool& flipped)
{
	// イテレータを取得
	std::map<const char32_t*, Texture>::const_iterator it = m_textures.find(key);
	try
	{
		// テクスチャが見つかれば処理をする
		if (it != m_textures.end())
		{
			// 左右反転、上下反転、拡大率、回転率、描画(座標指定)
			it->second.mirrored(mirrored).flipped(flipped).scaled(scale).rotated(rotate).drawAt(pos, Palette::White);
		}
		else
		{
			throw std::out_of_range("Texture not found");
		}
	}
	catch (const std::out_of_range& e)
	{
		// エラーメッセージを表示
		std::cerr << "Error: " << e.what() << std::endl;
	}
}
