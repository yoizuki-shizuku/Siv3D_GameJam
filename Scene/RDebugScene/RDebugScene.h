/*
 *	@File	RDebugScene.h
 *	@Brief	中村のデバッグシーン(最終的に消す)。
 *	@Date	2023-10-23
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef RDEBUGSCENE
#define RDEBUGSCENE

#include "../MyScene.h"

class DrawTexture;
class RDebugScene : public MyClass::Scene
{
public:
	RDebugScene();
	~RDebugScene() = default;

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Finalize() override;

private:

	// テクスチャ描画クラス
	std::unique_ptr<DrawTexture> m_tex;

	// ポリゴン
	Array<const char32_t*> m_keys;
	Array<MultiPolygon> m_polygons;
	Array<Texture> m_textures;

	// 2D 物理演算のシミュレーションステップ（秒）
	double m_stepTimer = (1.0 / 200.0);

	// 2D 物理演算のシミュレーション蓄積時間（秒）
	double m_tribulation;

	// 2D 物理演算のワールド
	P2World m_world;


};

#endif // RDEBUGSCENE
