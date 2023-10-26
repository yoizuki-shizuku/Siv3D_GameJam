/*
 *	@File	CraneBody_IdlingState.h
 *	@Brief	操作可能状態
 *	@Date	2023-10-26
 *  @Author Nagase
 */

#pragma once
#include "ICraneState.h"

class CraneBody_IdlingState : public ICraneState
{
public:
	CraneBody_IdlingState();
	~CraneBody_IdlingState();

	void Update() override;

private:

};
