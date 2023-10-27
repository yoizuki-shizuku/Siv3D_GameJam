/*
 *	@File	CraneArm.h
 *	@Brief	クレーンのアームパーツ
 *	@Date	2023-10-26
 *  @Author Nagase
 */

#pragma once
#include "ICraneComponent.h"

class CraneArm : public ICraneComponent
{
protected:

	// マップで子オブジェクトを管理
	std::map<const char32_t*, ICraneComponent*> m_children;

public:

	// 子を追加
	void Add(const char32_t* name, ICraneComponent* component) override {
		// 子情報を追加
		this->m_children.emplace(name, component);
		// 自身が親となる
		component->SetParent(this);
	}

	// 子を削除
	void Remove(const char32_t* name, ICraneComponent* component) override {
		m_children.erase(name);
		component->SetParent(nullptr);
	}
	CraneArm();

	// 初期化
	void Initialize(P2World& world) override;
	// 更新処理
	void Update(P2World& world) override;
	// 描画
	void Render() override;
	// 初期化処理
	void Finalize() override;

	// 加速度を返す
	Vec2 GetAccelerator() override;
	// 最大加速度を返す
	Vec2 GetMaxAccelerator() override;
	// 停止力を返す
	Vec2 GetBrake() override;

	// 開閉状態を受け取る
	bool GetOpen();
	// 閉じている状態か否か
	bool GetClose();


private:

	// 開ける際の時間変数
	float m_openTime;

};
