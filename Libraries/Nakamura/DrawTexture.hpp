/*
 *	@File	DrawTexture.hpp
 *	@Brief	描画ヘルパークラス
 *	@Date	2023-10-23
 *  @Author NakamuraRyo
 */

class DrawTexture
{
private:

	// テクスチャの配列 // キー・テクスチャパス
	std::map<const char32_t*, Texture> m_textures;
	std::map<const char32_t*, Image> m_images;

private:

	// ポリゴン割り
	const double MAX_DISTANCE = 5.0;

public:

	// コンストラクタ // コンストラクタ
	DrawTexture();
	~DrawTexture();

	/// <summary>
	/// テクスチャを追加する関数
	/// </summary>
	/// <param name="key">登録キーの文字列(U"文字列")</param>
	/// <param name="path">ファイルパスの文字列</param>
	/// <returns>なし</returns>
	void AddTexture(const char32_t* key, const char32_t* path);

	/// <summary>
	/// 登録したテクスチャを描画する関数
	/// </summary>
	/// <param name="key">登録キーの文字列(U"文字列")</param>
	/// <param name="pos">描画する位置</param>
	/// <param name="scale">拡大率(デフォルトは1.0)</param>
	/// <param name="rotate">回転率(デフォルトは0.0)</param>
	/// <param name="mirrored">左右反転フラグ(デフォルトはfalse)</param>
	/// <param name="flipped">上下反転フラグ(デフォルトはfalse)</param>
	/// <returns>なし</returns>
	void Draw(const char32_t* key, const Vec2& pos, const double& scale = 1.0, const double& rotate = 0.0,
		const bool& mirrored = false, const bool& flipped = false);

	/// <summary>
	/// イメージを返す関数
	/// </summary>
	/// <param name="key">登録キーの文字列(U"文字列")</param>
	/// <returns>イメージ</returns>
	const Image& GetImage(const char32_t* key);

	/// <summary>
	/// ポリゴンゲッター
	/// </summary>
	/// <param name="key">登録キーの文字列(U"文字列")</param>
	/// <param name="show">ポリゴンの可視化</param>
	/// <param name="color">Gizmoの色</param>
	/// <returns>テクスチャのポリゴン判定</returns>
	const Polygon& GetPolygon(const char32_t* key, const bool& show = false, const ColorF& color = Palette::Yellow);

};
