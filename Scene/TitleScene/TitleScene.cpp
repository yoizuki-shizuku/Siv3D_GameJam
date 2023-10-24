#include "TitleScene.h"

#include "../PlayScene/PlayScene.h"

TitleScene::TitleScene() :
	MyClass::Scene()
{
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
