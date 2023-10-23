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

	Vec2 m_pos;
};

#endif // RDEBUGSCENE
