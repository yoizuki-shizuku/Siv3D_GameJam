/*
 *	@File	CraneBody_StopState.cpp
 *	@Brief	クレーンの一旦停止を行う状態クラス
 *	@Date	2023-10-26
 *  @Author Nagase
 */

#include "../../../../stdafx.h"
#include "CraneBody_StopState.h"

#include "../Parts/ICraneComponent.h"
#include "../Parts/CraneBody.h"
#include "../Parts/CraneArm.h"

// 次のステート
#include "CraneBody_DownState.h"


CraneBody_StopState::CraneBody_StopState()
{
}

CraneBody_StopState::~CraneBody_StopState()
{
}

void CraneBody_StopState::Update()
{
	// 開けるように指示する
	CraneBody* bodyParts = dynamic_cast<CraneBody*>(m_craneComponent);
	bodyParts->SetOpenFlag(true);

	// アームの開閉が終わったら移行する
	if (dynamic_cast<CraneArm*>(bodyParts->GetChildren(U"Arm"))->GetOpen())
	{
		// ダウン状態に遷移する
		m_craneComponent->GetStateContext()->TransitionTo(new CraneBody_DownState);
	}

}
