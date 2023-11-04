#pragma once

#include "IPrizeFactory.h"

class RescuePrizeProduct : public IPrizeProduct {
public:

	RescuePrizeProduct(P2World world);
	~RescuePrizeProduct();

	void Operation() const override {}
	void Update() override;
	void Render() override;
	const char32_t* GetName() override { return U"Rescue"; }
	int GetScore() override { return 100; }

};

class RescuePrizeFactory : public IPrizeFactory
{
public:
	RescuePrizeFactory() = default;
	~RescuePrizeFactory() = default;

	// 生成する
	RescuePrizeProduct* FactoryMethod(P2World world) const override
	{
		return new RescuePrizeProduct(world);
	}

};
