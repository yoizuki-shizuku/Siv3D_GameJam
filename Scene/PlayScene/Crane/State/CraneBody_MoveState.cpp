#include "../../../../stdafx.h"

#include "CraneBody_MoveState.h"

#include "../Parts/ICraneComponent.h"
#include "../Parts/CraneBody.h"

// 次に移行するステート
#include "CraneBody_StopState.h"

// 横移動最低値
#define MIN_POS_X 80

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
	CraneBody* bodyParts = dynamic_cast<CraneBody*>(m_craneComponent);
	Vec2 bodyPos = m_craneComponent->GetPos();

	if (KeySpace.pressed() && !is_moved)
	{

		m_accelerator += m_craneComponent->GetAccelerator().x;

	}
	else
	{
		m_accelerator -= m_craneComponent->GetBrake().x;

	}

	// 横移動最低値より超えており、スペースが離された瞬間
	if (bodyParts->GetFirstPos().x - MIN_POS_X >= bodyPos.x
		&& KeySpace.up() && !is_moved) 		is_moved = true;

	// 上限設定
	if(bodyPos.x <= 270) is_moved = true;

	// 上限下限設定
	m_accelerator = std::min(std::max(m_accelerator, 0.0f), (float)m_craneComponent->GetMaxAccelerator().x);

	// ポジションに入れる
	bodyPos.x -= m_accelerator;
	m_craneComponent->SetPos(bodyPos);

	// 動かした形跡があり、加速度が0ならばストップ状態に移行する
	if (m_accelerator <= 0.0f && is_moved) m_craneComponent->GetStateContext()->TransitionTo(new CraneBody_StopState);

}
