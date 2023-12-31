﻿/*
 *	@File	CraneBody.h
 *	@Brief	クレーンのボディパーツ
 *	@Date	2023-10-26
 *  @Author Nagase
 */


#pragma once
#include "ICraneComponent.h"
#include "CraneArm.h"
#include <map>

class CraneBody : public ICraneComponent
{
protected:

	// マップで子オブジェクトを管理
	std::map<const char32_t*, ICraneComponent*> m_children;

public:

	// 子を追加
	void Add(const char32_t* name,ICraneComponent* component) override {
		// 子情報を追加
		this->m_children.emplace(name,component);
		// 自身が親となる
		component->SetParent(this);
	}

	// 子を削除
	void Remove(const char32_t* name, ICraneComponent* component) override {
		m_children.erase(name);
		component->SetParent(nullptr);
	}

	// 子を一つ渡す
	ICraneComponent* GetChildren(const char32_t* name)
	{
		return m_children.find(name)->second;
	}

	CraneBody(Vec2 pos);

	// 初期化処理
	void Initialize(P2World& world) override;
	// 更新処理
	void Update(P2World& world) override;
	// 描画処理
	void Render() override;
	// 終了処理
	void Finalize() override;

	// アームの開閉を指示する
	bool GetOpenFlag()		{ return m_openFlag; }
	// 初期位置を返す
	Vec2 GetFirstPos()		{ return m_firstPos; }

	// 加速度を返す
	Vec2 GetAccelerator() override;
	// 最大加速度を返す
	Vec2 GetMaxAccelerator() override;
	// 停止力を返す
	Vec2 GetBrake() override;

	// アーム開閉状況を変更する
	void SetOpenFlag(bool flag) { m_openFlag = flag; }

	// アーム可動回数
	int GetCount() {return m_count;}

	// 可動回数加算
	void CountPuls() { m_count++; }

	// 可動回数リセット
	void CountReset() { m_count = 0; }

	// 最大稼働量
	int MaxMoved();

private:

	// アームパーツクラス
	std::unique_ptr<CraneArm> m_craneArm;
	// 開閉指示クラス
	bool m_openFlag;

	// 初期位置
	Vec2 m_firstPos;

	// 可動回数
	int m_count;

	//// 加速度
	//Vec2 m_accelerator;
	//// 最大加速度
	//Vec2 m_maxAccelerator;
	//// 停止力
	//Vec2 m_brake;
};
