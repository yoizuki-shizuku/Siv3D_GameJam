#include "MySceneManager.h"

#include "TitleScene/TitleScene.h"

MyClass::SceneManager::SceneManager() :
	m_currentScene(nullptr),
	m_nextScene(nullptr)
{
}

void MyClass::SceneManager::Initialize()
{
	m_nextScene = new TitleScene();

	CreateScene();
}

void MyClass::SceneManager::Update()
{
	bool changeSceneFlag = false;

	if (m_currentScene)
	{
		m_currentScene->Update();
		changeSceneFlag = m_currentScene->GetChangeScene();
	}

	if (!changeSceneFlag) return;

	DeleteScene();
	CreateScene();
}

void MyClass::SceneManager::Render()
{
	if (m_currentScene) m_currentScene->Render();
}

void MyClass::SceneManager::Finalize()
{
	DeleteScene();
}

bool MyClass::SceneManager::GetExitGame()
{
	return m_currentScene ? m_currentScene->GetExitGame() : true;
}

void MyClass::SceneManager::CreateScene()
{
	if (m_currentScene) return;

	m_currentScene.reset(m_nextScene);

	m_nextScene = nullptr;

	m_currentScene->Initialize();
}

void MyClass::SceneManager::DeleteScene()
{
	if (!m_currentScene) return;

	m_nextScene = m_currentScene->GetNextScene();

	m_currentScene->Finalize();

	m_currentScene.reset();
}
