/*
 *	@File	CraneBody_ReturnState.cpp
 *	@Brief	クレーンを初期位置まで戻す状態クラス
 *	@Date	2023-10-26
 *  @Author Nagase
 */

#include "../../../../stdafx.h"
#include "CraneBody_ReturnState.h"

#include "../Parts/ICraneComponent.h"
#include "../Parts/CraneBody.h"
#include "../Parts/CraneArm.h"

// 次のステート
#include "CraneBody_IdlingState.h"

// ステート間の入れ替えに使用
#define TRANSITION_TIME 1.0f


CraneBody_ReturnState::CraneBody_ReturnState():
	m_openTime()
{
}

CraneBody_ReturnState::~CraneBody_ReturnState()
{
}

void CraneBody_ReturnState::Update()
{
	Vec2 bodyPos = m_craneComponent->GetPos();
	CraneBody* bodyParts = dynamic_cast<CraneBody*>(m_craneComponent);

	// 初期位置まで移動 (到着時停止力を働かせる)
	if (bodyPos.x <= bodyParts->GetFirstPos().x - 80)
	{
		m_accelerator += (float)bodyParts->GetAccelerator().x * 0.4;
	}
	else
	{
		m_accelerator -= (float)bodyParts->GetBrake().x;
	}

	// 上限下限設定
	m_accelerator = std::min(std::max(m_accelerator, 0.0f), (float)bodyParts->GetMaxAccelerator().x * 0.7f);

	// ポジションに入れる
	bodyPos.x += m_accelerator;
	m_craneComponent->SetPos(bodyPos);

	// 動かした形跡があり、加速度が0ならば次の状態に移行する
	if (m_accelerator <= 0.0f)
	{
		// アームを開けるように指示する
		CraneBody* bodyParts = dynamic_cast<CraneBody*>(m_craneComponent);
		bodyParts->SetOpenFlag(true);

		// アームが開き終わったら移行する
		if (dynamic_cast<CraneArm*>(bodyParts->GetChildren(U"Arm"))->GetOpen())
		{

			m_openTime += (float)Scene::DeltaTime();

			if (m_openTime >= TRANSITION_TIME)
			{

				bodyParts->CountPuls();

				// アイドリング状態へ遷移
				m_craneComponent->GetStateContext()->TransitionTo(new CraneBody_IdlingState);
			}
		}

	}
}
