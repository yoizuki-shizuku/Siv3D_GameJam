/*
 *	@File	RDebugScene.cpp
 *	@Brief	中村のデバッグシーン(最終的に消す)。
 *	@Date	2023-10-23
 *  @Author NakamuraRyo
 */

#include "RDebugScene.h"
#include "../../Libraries/Nakamura/DrawTexture.hpp"

RDebugScene::RDebugScene() :
	MyClass::Scene()
	, m_polygons{}
	, m_tribulation{ 0.0 }
	, m_stepTimer{ 0.0 }
{
	m_polygons.clear();
}

void RDebugScene::Initialize()
{
	const Texture textureWindmill{ U"../Resources/Textures/Test.png" };
	m_textures.push_back(textureWindmill);

	Image img{ U"../Resources/Textures/Test.png" };
	m_polygons  << img.alphaToPolygonsCentered().simplified(2.0);


	//// 画像設定
	//m_tex = std::make_unique<DrawTexture>();

	//// かえるの情報
	//m_tex->AddTexture(U"Test", U"../Resources/Textures/Test.png");
	//m_tex->SetTexInfo(U"Test", { 500,240 }, 1.0, 0.0, false, false);
	//m_polygons.push_back(m_tex->GetPolygon(U"Test"));

	//// ステージの情報
	//m_tex->AddTexture(U"Stage", U"../Resources/Textures/Stage.png");
	//m_tex->SetTexInfo(U"Stage", { 640,360 }, 1.0, 0.0, false, false);
	//m_polygons.push_back(m_tex->GetPolygon(U"Stage"));

	//// 対応キーに登録
	//m_keys.push_back(U"Test");
	//m_keys.push_back(U"Stage");
}

void RDebugScene::Update()
{
	// 物理仮想ワールドを更新
	for (m_tribulation += s3d::Scene::DeltaTime(); m_stepTimer <= m_tribulation; m_tribulation -= m_stepTimer)
	{
		m_world.update(m_stepTimer);
	}
}

void RDebugScene::Render()
{
	//m_tex->SetTexInfo(U"Test", { 500,240 }, 1.0, m_tex->GetTexInfo(U"Test").ROTATE + 1, false, false);

	//// 画像を表示
	//for (auto& i : m_keys)
	//{
	//	m_tex->Draw(i);
	//	m_tex->GetPolygon(i, true, Palette::Greenyellow);
	//}
}

void RDebugScene::Finalize()
{
}
