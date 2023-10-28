/*
 *	@File	CraneBody_DownState.cpp
 *	@Brief	クレーンを規定位置まで下げるクラス
 *	@Date	2023-10-26
 *  @Author Nagase
 */

#include "../Parts/ICraneComponent.h"
#include "CraneBody_DownState.h"

#include "../Parts/ICraneComponent.h"
#include "../Parts/CraneBody.h"
#include "../Parts/CraneArm.h"

// 次のステート
#include "CraneBody_UpState.h"

// 最大下降値
#define MAX_DOWN 400.0f

// 加速度
#define ACCE_VAL 0.3f

// 最大加速度
#define MAX_ACCE_VAL 2.0f

CraneBody_DownState::CraneBody_DownState()
{
}

CraneBody_DownState::~CraneBody_DownState()
{
}

void CraneBody_DownState::Update()
{
	Vec2 bodyPos = m_craneComponent->GetPos();

	m_accelerator += m_craneComponent->GetAccelerator().x;

	if (bodyPos.y >= MAX_DOWN)
	{
		m_accelerator = 0.0f;
		is_moved = true;
	}

	// 閉じるように指示する
	CraneBody* bodyParts = dynamic_cast<CraneBody*>(m_craneComponent);
	bodyParts->SetOpenFlag(!is_moved);

	// 上限下限設定
	m_accelerator = std::min(std::max(m_accelerator, 0.0f), (float)m_craneComponent->GetMaxAccelerator().y);

	// ポジションに入れる
	bodyPos.y += m_accelerator;
	m_craneComponent->SetPos(bodyPos);

	// アームの開閉が終わったら上昇する
	if (dynamic_cast<CraneArm*>(bodyParts->GetChildren(U"Arm"))->GetClose())
	{
		// アップ状態に遷移する
		m_craneComponent->GetStateContext()->TransitionTo(new CraneBody_UpState);
	}

}
