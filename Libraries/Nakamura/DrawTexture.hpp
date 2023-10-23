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

public:

	// コンストラクタ // コンストラクタ
	DrawTexture();
	~DrawTexture();

	// Add関数
	void AddTexture(const char32_t* key, const char32_t* path);

	// Draw関数
	void Draw(const char32_t* key, const Vec2& pos, const double& scale = 1.0, const double& rotate = 0.0,
		const bool& mirrored = false, const bool& flipped = false);

};
