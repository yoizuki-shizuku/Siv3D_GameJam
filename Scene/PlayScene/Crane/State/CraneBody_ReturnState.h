/*
 *	@File	CraneBody_ReturnState.h
 *	@Brief	クレーンを初期位置まで戻す状態クラス
 *	@Date	2023-10-26
 *  @Author Nagase
 */

#pragma once
#include "ICraneState.h"

class CraneBody_ReturnState : public ICraneState
{
public:
	CraneBody_ReturnState();
	~CraneBody_ReturnState();

	void Update() override;

private:

	// 横移動加速度
	float m_accelerator;
	// 減速度
	float m_brake;
	// 動いているフラグ
	bool is_moved;
	// 開けている間の時間
	float m_openTime;

};
