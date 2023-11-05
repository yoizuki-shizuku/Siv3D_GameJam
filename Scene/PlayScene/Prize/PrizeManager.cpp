#include "../../../stdafx.h"
#include "PrizeManager.h"

#include "IPrizeFactory.h"
#include "SmallPrize.h"
#include "BigPrize.h"
#include "AimPrize.h"
#include "RescuePrize.h"
#include "../Effect/AcquisitionEffect.h"

#include "../../../Libraries/Nakamura/DrawTexture.hpp"
#include "../../../Libraries/Yamamoto/Numeral.h"

#define ANIM_VERTICAL	450
#define ANIM_BESIDE		750

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

	m_craneCount = std::make_unique<Numeral>();


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

	// for(auto& prizes : m_prizes)
	for (size_t i = 0; i < m_prizes.size(); ++i)
	{
		// 上限設定
		if (m_prizes[i]->GetPos().x >= 1190)
		{
			m_prizes[i]->SetPos(Vec2(1190, m_prizes[i]->GetPos().y));
		}

		// 規定値よりも下に行ったら消す
		if (m_prizes[i]->GetPos().y >= 800)
		{
			if (m_prizes[i]->GetName() == U"Rescue")
			{
				m_rescueFlag = true;
			}


			m_score += m_prizes[i]->GetScore();
			m_effect.add<AcquisitionEffect>(Vec2(1050, 730));

			m_prizes.remove(m_prizes[i]);

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

void PrizeManager::Render_Result()
{

	int sceneHalfSizeX = (Scene::Size() / 2).x;
	int sceneHalfSizeY = (Scene::Size() / 2).y;

	// 横に伸ばす
	m_animationTime_Beside += Scene::DeltaTime() * 0.7f;

	// 縦に伸ばす
	m_animationTime_Vertical += m_animationTime_Beside >= 1.0f ? Scene::DeltaTime() : 0;

	// アニメーション
	m_animationTime_Rescue += m_animationTime_Vertical >= 1.0f ? Scene::DeltaTime() : 0;

	//　上限下限値設定
	m_animationTime_Beside = Clamp(m_animationTime_Beside, 0.0f, 1.0f);
	m_animationTime_Vertical = Clamp(m_animationTime_Vertical, 0.0f, 1.0f);
	m_animationTime_Rescue = Clamp(m_animationTime_Rescue, 0.0f, 1.0f);

	double beside = Easing::Circ(m_animationTime_Beside) * ANIM_BESIDE;
	double vertical = Easing::Quad(m_animationTime_Vertical) * ANIM_VERTICAL;

	// 矩形描画
	Rect{ Arg::center(sceneHalfSizeX, sceneHalfSizeY) ,
		  2 + (int)beside,
		  2 + (int)vertical }.draw(Palette::Gray);

	// 数字描画
	if (m_animationTime_Vertical >= 1.0f)
	{
		m_craneCount->SetPosition(Vec2(sceneHalfSizeX, sceneHalfSizeY - 200));
		m_craneCount->SetNumber(m_score);
		m_craneCount->Render();
	}

	// レスキュー対象描画
	if (m_rescueFlag)
	{
		m_drawTexture->SetTexInfo(U"Rescue", Vec2(sceneHalfSizeX, sceneHalfSizeY + 100), m_animationTime_Rescue);
		m_drawTexture->Draw(U"Rescue");
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
