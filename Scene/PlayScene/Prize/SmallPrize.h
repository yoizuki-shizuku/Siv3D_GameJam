#pragma once

#include "IPrizeFactory.h"

class SmallPrizeProduct : public IPrizeProduct {
public:

	SmallPrizeProduct(P2World world);
	~SmallPrizeProduct();

	void Operation() const override {}
	void Update() override;
	void Render() override;
	int GetScore() override { return 10; }

};

class SmallPrizeFactory : public IPrizeFactory
{
public:
	SmallPrizeFactory() = default;
	~SmallPrizeFactory() = default;

	// 生成する
	SmallPrizeProduct* FactoryMethod(P2World world) const override
	{
		return new SmallPrizeProduct(world);
	}

};
