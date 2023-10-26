#pragma once
#include "../../../../Libraries/Nakamura/DrawTexture.hpp"
#include "../State/ICraneState.h"

class ICraneComponent
{
public:

	enum CreaneMoveType
	{
		MOVE_TO,
		STOP,
		MOVE_BACK
	};

protected:

	ICraneComponent* m_parent = nullptr;
	CraneStateContext* m_state = nullptr;

	Vec2 m_pos = Vec2();

	P2Body m_polygonBody;

	std::unique_ptr<DrawTexture> m_drawTexture;


public:

	virtual ~ICraneComponent() {};

	void SetParent(ICraneComponent* parent)
	{
		this->m_parent = parent;
	}


	ICraneComponent* GetParent() const
	{
		return this->m_parent;
	}

	virtual void Add(const char32_t* name, ICraneComponent* component) { name; component; }
	virtual void Remove(const char32_t* name, ICraneComponent* component) { name; component; }

	virtual void Initialize(P2World& world) = 0;

	virtual void Update(P2World& world) = 0;

	virtual void Render() = 0;

	virtual void Finalize() = 0;

	void SetPos(Vec2 pos) { m_pos = pos;}
	Vec2 GetPos() { return m_pos; }

	CraneStateContext* GetStateContext() { return m_state; }

	P2Body GetBody() { return m_polygonBody;}

};
