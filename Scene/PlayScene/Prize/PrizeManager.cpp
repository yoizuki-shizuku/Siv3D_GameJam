#include "../../../stdafx.h"
#include "PrizeManager.h"

#include "IPrizeFactory.h"
#include "SmallPrize.h"
#include "BigPrize.h"
#include "AimPrize.h"
#include "RescuePrize.h"
#include "../Effect/AcquisitionEffect.h"

PrizeManager::PrizeManager()
{
}

PrizeManager::~PrizeManager()
{
}

void PrizeManager::Initialize(P2World world)
{
	m_score = 0;

	// どうでもいい景品
	CreatePrize(new SmallPrizeFactory(), world, 100);

	// 狙い景品
	CreatePrize(new AimPrizeFactory(), world, 20);

	CreatePrize(new BigPrizeFactory(),world,10);

	CreatePrize(new RescuePrizeFactory(), world, 1);

}

void PrizeManager::Update()
{
	m_effect.update();

	for (auto& prizes : m_prizes)
	{
		// 上限設定
		if (prizes->GetPos().x >= 1190)
		{
			prizes->SetPos(Vec2(1190, prizes->GetPos().y));
		}

		// 規定値よりも下に行ったら消す
		if (prizes->GetPos().y >= 800)
		{
			prizes->SetPos(Vec2(100, 0));

			m_score += prizes->GetScore();

			m_effect.add<AcquisitionEffect>(Vec2(1050, 730));

		}

	}

}

void PrizeManager::Render()
{

	for (auto& prizes : m_prizes)
	{
		prizes->Render();
	}

}

void PrizeManager::CreatePrize(IPrizeFactory* prize, P2World world,int num)
{

	for (int i = 0; i < num; i++)
	{
		//IPrizeProduct* prizes = prize;

		IPrizeProduct* prizeObj = prize->FactoryMethod(world);

		constexpr RectF shape{ 100, 100, 700, 300 };
		prizeObj->SetPos(RandomVec2(shape));
		// 生成
		m_prizes.push_back(prizeObj);
	}

	delete prize;

}
