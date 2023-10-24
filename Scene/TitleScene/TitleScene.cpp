#include "TitleScene.h"

#include "../PlayScene/PlayScene.h"

TitleScene::TitleScene() :
	MyClass::Scene()
{
}

void TitleScene::Initialize()
{
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
}

void TitleScene::Finalize()
{
}
