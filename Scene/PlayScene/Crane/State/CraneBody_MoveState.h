/*
 *	@File	CraneBody_MoveState.h
 *	@Brief	クレーンを横移動させる状態クラス
 *	@Date	2023-10-26
 *  @Author Nagase
 */


#pragma once
#include "ICraneState.h"

class CraneBody_MoveState : public ICraneState
{
public:
	CraneBody_MoveState();
	~CraneBody_MoveState();

	void Update() override;

private:

	// 横移動加速度
	float m_accelerator;
	// 減速度
	float m_brake;
	// 動いているフラグ
	bool is_moved;

};
