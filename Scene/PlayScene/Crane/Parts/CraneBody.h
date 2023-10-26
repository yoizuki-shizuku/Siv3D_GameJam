/*
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

	CraneBody();

	// 初期化処理
	void Initialize(P2World& world) override;
	// 更新処理
	void Update(P2World& world) override;
	// 描画処理
	void Render() override;
	// 終了処理
	void Finalize() override;

	// アームの開閉を指示する
	bool GetOpenFlag() { return m_openFlag; }
	// 状況を変更する
	void SetOpenFlag(bool flag) { m_openFlag = flag; }

private:

	// アームパーツクラス
	std::unique_ptr<CraneArm> m_craneArm;
	// 開閉指示クラス
	bool m_openFlag;

};
