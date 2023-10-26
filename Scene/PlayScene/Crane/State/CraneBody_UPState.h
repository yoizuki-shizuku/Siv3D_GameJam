/*
 *	@File	CraneBody_UPState.h
 *	@Brief	クレーンを規定値まで持ち上げる状態クラス
 *	@Date	2023-10-26
 *  @Author Nagase
 */

#pragma once
#include "ICraneState.h"

class CraneBody_UpState : public ICraneState
{
public:
	CraneBody_UpState();
	~CraneBody_UpState();

	void Update() override;

private:

	// 横移動加速度
	float m_accelerator;
	// 減速度
	float m_brake;
	// 動いているフラグ
	bool is_moved;

};
