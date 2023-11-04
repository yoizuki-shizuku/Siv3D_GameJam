/*
 *	@File	CraneBody_UPState.cpp
 *	@Brief	クレーンを規定値まで持ち上げる状態クラス
 *	@Date	2023-10-26
 *  @Author Nagase
 */

#include "../../../../stdafx.h"
#include "CraneBody_UPState.h"

#include "../Parts/CraneBody.h"
#include "../Parts/CraneArm.h"

// 次のステート
#include "CraneBody_ReturnState.h"

// Yの初期値
#define MAX_POS_Y 60.0f

// 加速度
#define ACCE_VAL 0.3f

// 最大加速度
#define MAX_ACCE_VAL 2.0f

CraneBody_UpState::CraneBody_UpState()
{
}

CraneBody_UpState::~CraneBody_UpState()
{
}

void CraneBody_UpState::Update()
{

	Vec2 bodyPos = m_craneComponent->GetPos();

	m_accelerator += (float)m_craneComponent->GetAccelerator().x;

	// 上限に来たら動き終わったフラグを建てる
	if (bodyPos.y <= MAX_POS_Y)
	{
		m_accelerator = MAX_POS_Y;
		is_moved = true;
	}
	// 上限下限設定
	m_accelerator = std::min(std::max(m_accelerator, 0.0f), (float)m_craneComponent->GetMaxAccelerator().y);

	// ポジションに入れる
	bodyPos.y -= m_accelerator;
	m_craneComponent->SetPos(bodyPos);

	if (is_moved)
	{
		// リターン状態に遷移する
		m_craneComponent->GetStateContext()->TransitionTo(new CraneBody_ReturnState);
	}
}
