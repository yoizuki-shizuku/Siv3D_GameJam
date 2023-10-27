#include "TitleScene.h"

// テクスチャ情報
#include "../../Libraries/Nakamura/DrawTexture.hpp"

#include "../PlayScene/PlayScene.h"

TitleScene::TitleScene() :
	MyClass::Scene()
{
	m_textures = std::make_unique<DrawTexture>();
}

void TitleScene::Initialize()
{
	s3d::Scene::SetBackground(Palette::White);
}

void TitleScene::Update()
{
	if (KeySpace.down())
	{
		ChangeScene<PlayScene>();
	}
}

void TitleScene::Render()
{
	Print << U"TitleScene";
}

void TitleScene::Finalize()
{
}
