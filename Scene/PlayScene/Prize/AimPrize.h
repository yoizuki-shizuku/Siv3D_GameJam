#pragma once

#include "IPrizeFactory.h"

class AimPrizeProduct : public IPrizeProduct {
public:

	AimPrizeProduct(P2World world);
	~AimPrizeProduct();

	void Operation() const override {}
	void Update() override;
	void Render() override;
};

class AimPrizeFactory : public IPrizeFactory
{
public:
	AimPrizeFactory();
	~AimPrizeFactory();

	// 生成する
	AimPrizeProduct* FactoryMethod(P2World world) const override
	{
		return new AimPrizeProduct(world);
	}

};
