/*
 *	@File	RDebugScene.cpp
 *	@Brief	中村のデバッグシーン(最終的に消す)。
 *	@Date	2023-10-23
 *  @Author NakamuraRyo
 */

#include "RDebugScene.h"
#include "../../Libraries/Nakamura/DrawTexture.hpp"

RDebugScene::RDebugScene() :
	MyClass::Scene(),m_pos{640,360}
{
}

void RDebugScene::Initialize()
{
	m_tex = std::make_unique<DrawTexture>();
	m_tex->AddTexture(U"Stage", U"../Resources/Textures/Stage.png");
}

void RDebugScene::Update()
{
}

void RDebugScene::Render()
{

	// ポリゴンの取得と描画
	m_tex->GetPolygon(U"Stage",true);

	// ステージを表示
	m_tex->Draw(U"Stage", m_pos);
}

void RDebugScene::Finalize()
{
}
