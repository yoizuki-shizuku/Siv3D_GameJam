﻿/*
 *	@File	CraneBody_IdlingState.cpp
 *	@Brief	操作可能状態
 *	@Date	2023-10-26
 *  @Author Nagase
 */

#include "../../../../stdafx.h"

#include "CraneBody_IdlingState.h"

#include "../Parts/ICraneComponent.h"
#include "../Parts/CraneBody.h"

// 次のステート
#include "CraneBody_MoveState.h"

CraneBody_IdlingState::CraneBody_IdlingState()
{
}

CraneBody_IdlingState::~CraneBody_IdlingState()
{
}

void CraneBody_IdlingState::Update()
{

	// 閉じるように指示する
	CraneBody* bodyParts = dynamic_cast<CraneBody*>(m_craneComponent);
	bodyParts->SetOpenFlag(false);

	if (KeySpace.pressed())
	{
		// ムーブ状態に遷移する
		m_craneComponent->GetStateContext()->TransitionTo(new CraneBody_MoveState());
	}

}
