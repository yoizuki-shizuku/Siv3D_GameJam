#pragma once

namespace MyClass
{
	class Scene
	{
	public:
		Scene() : m_exitGame(false), m_isChange(false), m_nextScene(nullptr) {};
		virtual ~Scene() = default;

		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void Finalize() = 0;

		virtual bool GetExitGame() final { return m_exitGame; }
		virtual bool GetChangeScene() final { return m_isChange; }
		virtual Scene* GetNextScene() final { return m_nextScene; }

	protected:
		virtual void ExitGame() final { m_exitGame = true; }

		template <class T, class... Args>
		inline void ChangeScene(Args&&... arg)
		{
			if (m_isChange) return;

			m_nextScene = new T(std::forward<Args>(arg)...);
			m_isChange = true;
		}

	private:
		bool m_exitGame;
		bool m_isChange;
		Scene* m_nextScene;

	};
}
