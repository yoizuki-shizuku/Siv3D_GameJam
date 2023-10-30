#include "../../../stdafx.h"
#include "PrizeManager.h"

#include "IPrizeFactory.h"
#include "SmallPrize.h"
#include "AimPrize.h"
#include "../Effect/AcquisitionEffect.h"

PrizeManager::PrizeManager()
{
}

PrizeManager::~PrizeManager()
{
}

void PrizeManager::Initialize(P2World world)
{

	//m_effect = std::make_unique<AcquisitionEffect>(Vec2(1050, 730));

	SmallPrizeFactory* smallPrizeFac = new SmallPrizeFactory();

	// どうでもよい景品
	for (int i = 0; i < 30; i++)
	{
		SmallPrizeProduct* smallPrizeObj = smallPrizeFac->FactoryMethod(world);

		smallPrizeObj->SetPos(Vec2(40.0f + (20 * i) , 200.0f));

		// 生成
		m_prizes.push_back(smallPrizeObj);

		//delete smallPrizeObj;

	}
	delete smallPrizeFac;

	// 狙い景品
	AimPrizeFactory* aimPrizeFac = new AimPrizeFactory();
	AimPrizeProduct* aimPrizeObj = aimPrizeFac->FactoryMethod(world);

	aimPrizeObj->SetPos(Vec2(360.0f, 400.0f));

	m_prizes.push_back(aimPrizeObj);

	//delete aimPrizeObj;
	delete aimPrizeFac;

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
