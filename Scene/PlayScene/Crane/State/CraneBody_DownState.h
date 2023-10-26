/*
 *	@File	CraneBody_DownState.h
 *	@Brief	クレーンを規定位置まで下げるクラス
 *	@Date	2023-10-26
 *  @Author Nagase
 */

#pragma once
#include "ICraneState.h"

class CraneBody_DownState : public ICraneState
{
public:
	CraneBody_DownState();
	~CraneBody_DownState();

	void Update() override;

private:

	// 横移動加速度
	float m_accelerator;
	// 減速度
	float m_brake;
	// 動いているフラグ
	bool is_moved;

};
