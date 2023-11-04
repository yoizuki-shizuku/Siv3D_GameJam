#include "PlayScene.h"

#include "Crane/Parts/CraneBody.h"
#include "Effect/AcquisitionEffect.h"
#include "Field/Field.h"
#include "Prize/PrizeManager.h"
#include "../../Libraries/Yamamoto/Numeral.h"
#include "../../Libraries/Yamamoto/Gaming.h"

PlayScene::PlayScene() :
	MyClass::Scene()
{
}

void PlayScene::Initialize()
{

	s3d::Scene::SetBackground(Palette::Black);

	m_tex = std::make_unique<Gaming>();
	m_tex->LoadTexture(U"../Resources/Textures/GamingFlame.png");

	m_backTex = std::make_unique<Texture>(U"../Resources/Textures/PlayBack.png");

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

	m_effect = std::make_unique<AcquisitionEffect>(Vec2(1000,630));

	m_numeral = std::make_unique<Numeral>();
	m_numeral->LoadTexture(U"../Resources/Textures/number.png");
	m_numeral->SetPosition(Vec2(800, 630));
	m_numeral->SetSpace(5.0f);

	m_craneCount = std::make_unique<Numeral>();
	m_craneCount->LoadTexture(U"../Resources/Textures/number.png");
	m_craneCount->SetPosition(Vec2(80, 80));
	m_craneCount->SetSpace(5.0f);

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

	m_tex->Update();

	m_p2World->setSleepEnabled(false);

	m_craneBody->Update(*m_p2World.get());

	m_numeral->SetNumber(m_prizeManager->GetScore());
	m_craneCount->SetNumber(m_craneBody->MaxMoved() - m_craneBody->GetCount());

	m_prizeManager->Update();  

}

void PlayScene::Render()
{
	// 背景を描画する　(適応すると何故かエフェクトが消えてしまう)
	//m_backTex->draw();

	m_prizeManager->Render();

	m_craneBody->Render();

	m_field->Render();

	m_numeral->Render();
	m_tex->Render();
	m_craneCount->Render();

	m_effect->update(s3d::Scene::FrameCount());

}

void PlayScene::Finalize()
{
}
