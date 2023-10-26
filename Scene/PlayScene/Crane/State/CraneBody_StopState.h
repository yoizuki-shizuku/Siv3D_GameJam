/*
 *	@File	CraneBody_StopState.h
 *	@Brief	クレーンの一旦停止を行う状態クラス
 *	@Date	2023-10-26
 *  @Author Nagase
 */

#pragma once
#include "ICraneState.h"

class CraneBody_StopState : public ICraneState
{
public:

	CraneBody_StopState();
	~CraneBody_StopState();

	void Update() override;

private:

};
