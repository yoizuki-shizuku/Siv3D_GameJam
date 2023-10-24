/*
 *	@File	RDebugScene.cpp
 *	@Brief	中村のデバッグシーン(最終的に消す)。
 *	@Date	2023-10-23
 *  @Author NakamuraRyo
 */

#include "RDebugScene.h"
#include "../../Libraries/Nakamura/DrawTexture.hpp"

RDebugScene::RDebugScene() :
	MyClass::Scene(),
	m_polygons{}
{
	m_polygons.clear();
}

void RDebugScene::Initialize()
{
	// 画像設定
	m_tex = std::make_unique<DrawTexture>();

	// かえるの情報
	m_tex->AddTexture(U"Test", U"../Resources/Textures/Test.png");
	m_tex->SetTexInfo(U"Test", { 740,240 }, 1.0, 30.0, false, false);
	m_polygons.push_back(m_tex->GetPolygon(U"Test", m_tex->GetTexInfo(U"Test").POS));

	// ステージの情報
	m_tex->AddTexture(U"Stage", U"../Resources/Textures/Stage.png");
	m_tex->SetTexInfo(U"Stage", { 0,0 }, 1.0, 0.0, false, false);
	m_polygons.push_back(m_tex->GetPolygon(U"Stage", m_tex->GetTexInfo(U"Stage").POS));

	// 対応キーに登録
	m_keys.push_back(U"Test");
	m_keys.push_back(U"Stage");
}

void RDebugScene::Update()
{
}

void RDebugScene::Render()
{
	// 画像を表示
	for (auto& i : m_keys)
	{
		m_tex->Draw(i, m_tex->GetTexInfo(i).POS);
		m_tex->GetPolygon(i, m_tex->GetTexInfo(i).POS, true);
	}
}

void RDebugScene::Finalize()
{
}
