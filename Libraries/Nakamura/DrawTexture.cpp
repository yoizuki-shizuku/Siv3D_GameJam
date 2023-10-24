﻿/*
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
	, m_images{}						// イメージ配列
	, m_infos{}							// 画像の設定
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
	m_images.clear();
	m_infos.clear();
}

/// <summary>
/// テクスチャを追加する関数
/// </summary>
/// <param name="key">登録キーの文字列(U"文字列")</param>
/// <param name="path">ファイルパスの文字列</param>
/// <returns>なし</returns>
void DrawTexture::AddTexture(const char32_t* key, const char32_t* path)
{
	Texture _tex{ path };
	m_textures.emplace(key, _tex);

	Image _img{ path };
	m_images.emplace(key, _img);

	TexInfo _info;
	m_infos.emplace(key, _info);
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
	std::map<const char32_t*, Texture>::const_iterator _it = m_textures.find(key);
	std::map<const char32_t*, TexInfo>::iterator _in = m_infos.find(key);
	try
	{
		// テクスチャが見つかれば処理をする
		if (_it != m_textures.end())
		{
			// 情報を保存しておく
			_in->second.set(pos, scale, rotate, mirrored, flipped);

			// 左右反転、上下反転、拡大率、回転率、描画(座標指定)
			_it->second.mirrored(mirrored).flipped(flipped).scaled(scale).rotated(rotate).draw(pos, Palette::White);
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

/// <summary>
/// イメージを返す関数
/// </summary>
/// <param name="key">登録キーの文字列(U"文字列")</param>
/// <returns>イメージ</returns>
const Image& DrawTexture::GetImage(const char32_t* key)
{
	// イテレータを取得
	std::map<const char32_t*, Image>::const_iterator _it = m_images.find(key);

	// イメージが見つからなければ最初の画像を返す
	if (_it == m_images.end())
	{
		return m_images.begin()->second;
	}

	return _it->second;
}

/// <summary>
/// ポリゴンゲッター
/// </summary>
/// <param name="key">登録キーの文字列(U"文字列")</param>
/// <param name="pos">表示位置</param>
/// <param name="show">ポリゴンの可視化</param>
/// <param name="color">Gizmoの色</param>
/// <returns>テクスチャのポリゴン判定</returns>
const Polygon& DrawTexture::GetPolygon(const char32_t* key, const Vec2& pos, const bool& show, const ColorF& color)
{
	// アルファ値 1 以上の領域を Polygon 化する
	const Polygon _polygon = GetImage(key).alphaToPolygon(1, AllowHoles::No);

	std::map<const char32_t*, TexInfo>::iterator _in = m_infos.find(key);
	_polygon.scaled(_in->second.SCALE);
	_polygon.rotated(_in->second.ROTATE);

	// 単純化した Polygon
	const Polygon _simple = _polygon.simplified(MAX_DISTANCE);

	// Trueなら描画する
	if (show)
	{
		_simple.movedBy(pos).draw(ColorF{ color,0.5 }).drawWireframe(2, color);
	}

	return _simple;
}

/// <summary>
/// 画像に対応した情報
/// </summary>
/// <param name="keys">登録キーの文字列(U"文字列")</param>
/// <returns>情報</returns>
const DrawTexture::TexInfo& DrawTexture::GetTexInfo(const char32_t* key)
{
	std::map<const char32_t*, TexInfo>::iterator _it = m_infos.find(key);
	return _it->second;
}

/// <summary>
/// インフォセッター
/// </summary>
/// <param name="key">登録キーの文字列(U"文字列")</param>
/// <param name="pos">描画する位置</param>
/// <param name="scale">拡大率(デフォルトは1.0)</param>
/// <param name="rotate">回転率(デフォルトは0.0)</param>
/// <param name="mirrored">左右反転フラグ(デフォルトはfalse)</param>
/// <param name="flipped">上下反転フラグ(デフォルトはfalse)</param>
/// <returns>なし</returns>
void DrawTexture::SetTexInfo(const char32_t* key, const Vec2& pos, const double& scale, const double& rotate,
	const bool& mirrored, const bool& flipped)
{
	std::map<const char32_t*, TexInfo>::iterator _it = m_infos.find(key);

	TexInfo _texInfo;
	_texInfo.POS = pos;
	_texInfo.SCALE = scale;
	_texInfo.ROTATE = rotate;
	_texInfo.MIRRORED = mirrored;
	_texInfo.FLIPPED = flipped;

	m_infos[_it->first] = _texInfo;
}
