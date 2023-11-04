#pragma once

#include "IPrizeFactory.h"

class AimPrizeProduct : public IPrizeProduct {
public:

	AimPrizeProduct(P2World world);
	~AimPrizeProduct();

	void Operation() const override {}
	void Update() override;
	void Render() override;
	int GetScore() override { return 50; }
};

class AimPrizeFactory : public IPrizeFactory
{
public:
	AimPrizeFactory() = default;
	~AimPrizeFactory() = default;

	// 生成する
	AimPrizeProduct* FactoryMethod(P2World world) const override
	{
		return new AimPrizeProduct(world);
	}

};
