#include "../../../../stdafx.h"

#include "CraneBody_MoveState.h"

#include "../Parts/ICraneComponent.h"

// 次に移行するステート
#include "CraneBody_StopState.h"

// 加速度
#define ACCE_VAL 0.2f

// 最大加速度
#define MAX_ACCE_VAL 3.5f

// 停止力
#define BRAKE_VAL 0.8f

// 横移動最低値
#define MIN_POS_X 500

CraneBody_MoveState::CraneBody_MoveState():
	m_accelerator(),
	m_brake(),
	is_moved(false)
{
}

CraneBody_MoveState::~CraneBody_MoveState()
{
}

void CraneBody_MoveState::Update()
{
	Vec2 bodyPos = m_craneComponent->GetPos();

	if (KeySpace.pressed() && !is_moved)
	{
		m_accelerator += ACCE_VAL;

	}
	else
	{
		m_accelerator -= BRAKE_VAL;
	}

	// 横移動最低値より超えており、スペースが離された瞬間
	if (MIN_POS_X >= bodyPos.x && KeySpace.up() && !is_moved) 		is_moved = true;

	// 上限下限設定
	m_accelerator = std::min(std::max(m_accelerator, 0.0f), MAX_ACCE_VAL);

	// ポジションに入れる
	bodyPos.x -= m_accelerator;
	m_craneComponent->SetPos(bodyPos);

	// 動かした形跡があり、加速度が0ならばストップ状態に移行する
	if (m_accelerator <= 0.0f && is_moved) m_craneComponent->GetStateContext()->TransitionTo(new CraneBody_StopState);

}
