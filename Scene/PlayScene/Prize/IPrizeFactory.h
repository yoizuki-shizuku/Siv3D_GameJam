#pragma once

// プロダクトクラス
class IPrizeProduct {
public:
	virtual ~IPrizeProduct() {};

	virtual void Operation() const = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual int GetScore() = 0;
	virtual const char32_t* GetName() = 0;

	void SetPos(Vec2 pos) { m_polygonBody.setPos(pos); }
	Vec2 GetPos()		  { return m_polygonBody.getPos();}
	P2Body GetP2Body()	  { return m_polygonBody;}

protected:

	// 物体の重さ
	float m_weight = 1.5f;

	// 物理物体
	P2Body m_polygonBody;
};

// 生成場
class IPrizeFactory {
public:
	virtual ~IPrizeFactory() {};
	virtual IPrizeProduct* FactoryMethod(P2World world) const = 0;

	void SomeOperation(P2World world) const {

		IPrizeProduct* product = this->FactoryMethod(world);

		product->Operation();

		delete product;
	}
};

//void ClientCode(const IPrizeFactory& creator,P2World world)
//{
//	
//	creator.SomeOperation(world);
//	
//}
