#include "PlayScene.h"

#include "Crane/Parts/CraneBody.h"
#include "Effect/AcquisitionEffect.h"
#include "Field/Field.h"

PlayScene::PlayScene() :
	MyClass::Scene()
{
}

void PlayScene::Initialize()
{
	// 2D 物理演算のシミュレーションステップ（秒）
	constexpr double StepTime = (1.0 / 200.0);

	// 2D 物理演算のシミュレーション蓄積時間（秒）
	m_accumulatedTime = 0.0;

	// 2D 物理演算のワールド
	m_p2World = std::make_unique<P2World>();

	m_craneBody = std::make_unique<CraneBody>(Vec2(1100,70));
	m_craneBody->Initialize(*m_p2World.get());

	m_field = std::make_unique<Field>();
	m_field->Initialize(*m_p2World.get());

	m_effect = std::make_unique<AcquisitionEffect>(Vec2(1000,600));

}

void PlayScene::Update()
{
	constexpr double StepTime = (1.0 / 200.0);

	for (m_accumulatedTime += s3d::Scene::DeltaTime(); StepTime <= m_accumulatedTime;m_accumulatedTime -= StepTime)
	{
		// 2D 物理演算のワールドを更新する
		m_p2World->update(StepTime);
	}

	m_craneBody->Update(*m_p2World.get());

}

void PlayScene::Render()
{

	m_craneBody->Render();
	m_field->Render();
}

void PlayScene::Finalize()
{
}
