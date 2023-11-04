#include "PlayScene.h"

#include "Crane/Parts/CraneBody.h"
#include "Effect/AcquisitionEffect.h"
#include "Field/Field.h"
#include "Prize/PrizeManager.h"
#include "../../Libraries/Yamamoto/Numeral.h"

PlayScene::PlayScene() :
	MyClass::Scene()
{
}

void PlayScene::Initialize()
{

	s3d::Scene::SetBackground(Palette::Black);
		
	// 2D 物理演算のシミュレーションステップ（秒）
	constexpr double StepTime = (1.0 / 200.0);
	StepTime;

	// 2D 物理演算のシミュレーション蓄積時間（秒）
	m_accumulatedTime = 0.0;

	// 2D 物理演算のワールド
	m_p2World = std::make_unique<P2World>();

	m_craneBody = std::make_unique<CraneBody>(Vec2(1130,70));
	m_craneBody->Initialize(*m_p2World.get());

	m_field = std::make_unique<Field>();
	m_field->Initialize(*m_p2World.get());

	m_effect = std::make_unique<AcquisitionEffect>(Vec2(1000,600));

	m_numeral = std::make_unique<Numeral>();
	m_numeral->LoadTexture(U"../Resources/Textures/number.png");
	m_numeral->SetPosition(Vec2(800, 600));
	m_numeral->SetSpace(5.0f);

	m_prizeManager = std::make_unique<PrizeManager>();
	m_prizeManager->Initialize(*m_p2World.get());

}

void PlayScene::Update()
{
	constexpr double StepTime = (1.0 / 200.0);

	for (m_accumulatedTime += s3d::Scene::DeltaTime(); StepTime <= m_accumulatedTime;m_accumulatedTime -= StepTime)
	{
		// 2D 物理演算のワールドを更新する
		m_p2World->update(StepTime);
	}

	m_p2World->setSleepEnabled(false);

	m_prizeManager->Update();
	m_craneBody->Update(*m_p2World.get());

	m_numeral->SetNumber(m_prizeManager->GetScore());

}

void PlayScene::Render()
{
	m_prizeManager->Render();

	m_craneBody->Render();

	m_field->Render();



	m_numeral->Render();

	m_effect->update(s3d::Scene::FrameCount());

}

void PlayScene::Finalize()
{
}
