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

// 初期位置
#define FIRST_POS Vec2(700,60)

// 加速度
#define ACCE_VAL 0.2f

// 最大加速度
#define MAX_ACCE_VAL 3.0f

// 停止力
#define BRAKE_VAL 0.8f

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

	// 初期位置まで移動 (到着時停止力を働かせる)
	if (bodyPos.x <= FIRST_POS.x)
	{
		m_accelerator += ACCE_VAL;
	}
	else
	{
		m_accelerator -= BRAKE_VAL;
	}

	// 上限下限設定
	m_accelerator = std::min(std::max(m_accelerator, 0.0f), MAX_ACCE_VAL);

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
				// アイドリング状態へ遷移
				m_craneComponent->GetStateContext()->TransitionTo(new CraneBody_IdlingState);
			}
		}

	}
}
