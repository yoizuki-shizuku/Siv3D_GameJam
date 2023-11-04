#include "../../../stdafx.h"
#include "PrizeManager.h"

#include "IPrizeFactory.h"
#include "SmallPrize.h"
#include "BigPrize.h"
#include "AimPrize.h"
#include "RescuePrize.h"
#include "../Effect/AcquisitionEffect.h"

#include "../../../Libraries/Nakamura/DrawTexture.hpp"

PrizeManager::PrizeManager()
{
}

PrizeManager::~PrizeManager()
{
}

void PrizeManager::Initialize(P2World world)
{
	m_score = 0;

	m_drawTexture = std::make_unique<DrawTexture>();

	//U"../Resources/Textures/CraneBody.png"
	m_drawTexture->AddTexture(U"Small",U"../Resources/Textures/SmallPrize.png");
	m_drawTexture->AddTexture(U"Aim", U"../Resources/Textures/AimPrize.png");
	m_drawTexture->AddTexture(U"Big", U"../Resources/Textures/BigPrize.png");
	m_drawTexture->AddTexture(U"Rescue", U"../Resources/Textures/RescuePrize.png");

	// どうでもいい景品
	CreatePrize(new SmallPrizeFactory(), world, 100,-100);

	// 狙い景品
	CreatePrize(new AimPrizeFactory(), world, 50);

	// でかくて丸い景品
	CreatePrize(new BigPrizeFactory(),world,10);

	// 救う景品
	CreatePrize(new RescuePrizeFactory(), world, 1,100);

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
			//constexpr RectF shape{ 100, -100, 700, 0 };
			//prizes->SetPos(RandomVec2(shape));

			m_score += prizes->GetScore();
			m_effect.add<AcquisitionEffect>(Vec2(1050, 730));

			m_prizes.remove(prizes);

		}

	}




}

void PrizeManager::Render()
{

	for (auto& prizes : m_prizes)
	{
		prizes->Render();

		m_drawTexture->SetTexInfo(prizes->GetName(), prizes->GetP2Body().getPos(), 1.0, prizes->GetP2Body().getAngle());
		m_drawTexture->Draw(prizes->GetName());
	}

}

void PrizeManager::CreatePrize(IPrizeFactory* prize, P2World world,int num, int pulsPosY)
{

	for (int i = 0; i < num; i++)
	{
		//IPrizeProduct* prizes = prize;

		IPrizeProduct* prizeObj = prize->FactoryMethod(world);

		RectF shape{ 100, 100 + pulsPosY, 700, 300 + pulsPosY};
		prizeObj->SetPos(RandomVec2(shape));
		// 生成
		m_prizes.push_back(prizeObj);
	}

	delete prize;

}
