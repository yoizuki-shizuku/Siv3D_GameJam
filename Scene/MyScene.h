#pragma once

#include "MyTransition.h"

namespace MyClass
{
	class Scene
	{
	public:
		Scene() :
			m_exitGame(false),
			m_isChange(false),
			m_changingScene(false),
			m_nextScene(nullptr),
			m_transition(nullptr)
		{};
		virtual ~Scene() = default;

		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void Finalize() = 0;

		virtual void CommonUpdete() final
		{
			if (m_changingScene && !m_transition->ProcessCheckFadeOut())
			{
				m_isChange = true;
			}
		}

		virtual bool GetExitGame() final { return m_exitGame; }
		virtual bool GetChangeScene() final { return m_isChange; }
		virtual Scene* GetNextScene() final { return m_nextScene; }

		virtual void SetTransition(Transition* transition) final { m_transition = transition; }

	protected:
		virtual void ExitGame() final { m_exitGame = true; }

		template <class T, class... Args>
		inline void ChangeScene(Args&&... arg)
		{
			if (m_transition->ProcessCheckFadeIn() || m_transition->ProcessCheckFadeOut()) return;

			m_nextScene = new T(std::forward<Args>(arg)...);
			m_transition->StartFadeOut();
			m_changingScene = true;
		}

	private:
		bool m_exitGame;
		bool m_isChange;
		bool m_changingScene;
		Scene* m_nextScene;

		Transition* m_transition;
	};
}
