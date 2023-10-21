#pragma once

#include "MyScene.h"

namespace MyClass
{
	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager() = default;

		void Initialize();
		void Update();
		void Render();
		void Finalize();

		bool GetExitGame();

	private:
		//	シーンクラスの生成
		void CreateScene();
		//	シーンクラスの削除
		void DeleteScene();

	private:
		std::unique_ptr<MyClass::Scene> m_currentScene;
		MyClass::Scene* m_nextScene;

	};
}

