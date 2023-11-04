#pragma once

#include "IPrizeFactory.h"

class BigPrizeProduct : public IPrizeProduct {
public:

	BigPrizeProduct(P2World world);
	~BigPrizeProduct();

	void Operation() const override {}
	void Update() override;
	void Render() override;
	const char32_t* GetName() override { return U"Big"; }
	int GetScore() override { return 30; }
};

class BigPrizeFactory : public IPrizeFactory
{
public:
	BigPrizeFactory() = default;
	~BigPrizeFactory() = default;

	// 生成する
	BigPrizeProduct* FactoryMethod(P2World world) const override
	{
		return new BigPrizeProduct(world);
	}

};
