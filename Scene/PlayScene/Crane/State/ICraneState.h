/*
 *	@File	ICraneState.h
 *	@Brief	クレーンクラスの状態インターフェース
 *	@Date	2023-10-26
 *  @Author Nagase
 */

#pragma once
// 前方宣言
class CraneStateContext;
class ICraneComponent;
class ICraneState
{
protected:
	// 現在の状態
	CraneStateContext* m_craneContext;
	// 動かすクラス
	ICraneComponent* m_craneComponent;

public:
	virtual ~ICraneState() {}

	// 状態をセットする
	void Set_Context(CraneStateContext* context) { this->m_craneContext = context; }
	// 部品をセットする
	void Set_Component(ICraneComponent* component) { this->m_craneComponent = component; }

	virtual void Update() = 0;
};

class CraneStateContext
{

private:
	ICraneState* m_Cranestate;

public:
	CraneStateContext(ICraneState* state) : m_Cranestate(nullptr) { this->TransitionTo(state); }
	~CraneStateContext() { delete m_Cranestate; }

	// 部品を登録する
	void SetComponent(ICraneComponent* component) { m_Cranestate->Set_Component(component); }

	// 次のステートに移行する
	void TransitionTo(ICraneState* state)
	{
		// 生成されている場合に限り行う
		if (this->m_Cranestate != nullptr)

			// 現在のステートを消去
			delete this->m_Cranestate;

		// 新しいステートに入れ替える
		this->m_Cranestate = state;
		this->m_Cranestate->Set_Context(this);
	}

	void Update() { this->m_Cranestate->Update(); }
};
