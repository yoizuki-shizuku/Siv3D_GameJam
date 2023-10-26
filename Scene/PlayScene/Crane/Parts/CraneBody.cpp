#include "CraneBody.h"

// 最初のステート
#include "../State/CraneBody_IdlingState.h"

// 初期位置
#define FIRST_POS Vec2(700,60)

// 加速度
#define ACCE_VAL Vec2(0.2f,0.3f)

// 最大加速度
#define MAX_ACCE_VAL Vec2(3.0f,2.0f)

// 停止力
#define BRAKE_VAL Vec2(0.3,1.2f)

CraneBody::CraneBody():
	m_openFlag()
{
}

void CraneBody::Initialize(P2World& world)
{

	m_drawTexture = std::make_unique<DrawTexture>();
	// 使用する画像
	m_drawTexture->AddTexture(U"Body",U"../Resource/KariCrane.png");

	// テクスチャの表示位置
	constexpr Vec2 BasePos{ 40, 80 };

	//// アルファ値 1 以上の領域を Polygon 化する
	const Polygon polygon = m_drawTexture->GetImage(U"Body").alphaToPolygonCentered(1, AllowHoles::No);

	// Polygon 単純化の許容距離（ピクセル）
	double maxDistance = 4.0;

	// 単純化した Polygon
	Polygon simplifiedPolygon = polygon.simplified(maxDistance);

	// ポリゴンに当たり判定を付ける
	m_polygonBody = world.createPolygon(P2Static, Vec2(), simplifiedPolygon);

	//　初期位置設定
	m_pos = FIRST_POS;

	// 子の生成
	m_craneArm = std::make_unique<CraneArm>();

	// 子を追加する
	this->Add(U"Arm",m_craneArm.get());

	m_craneArm->SetPos(m_pos);

	// 範囲for文　子の初期化処理
	for (auto itr = m_children.begin(); itr != m_children.end(); ++itr)
	{
		itr->second->Initialize(world);
	}

	// ステートを登録する
	m_state = new CraneStateContext(new CraneBody_IdlingState());
	m_state->SetComponent(this);

	m_openFlag = false;
}

void CraneBody::Update(P2World& world)
{
	// 本部品をステートに登録する
	m_state->SetComponent(this);
	// 現状態のステートを回す
	m_state->Update();

	m_drawTexture->SetTexInfo(U"Body",m_pos);

	// 範囲for文　子の更新処理
	for (auto itr = m_children.begin(); itr != m_children.end(); ++itr)
	{
		itr->second->SetPos(m_pos);
		itr->second->Update(world);
	}

	m_polygonBody.setPos(m_pos);

}

void CraneBody::Render()
{
	// 範囲for文　子の描画処理を回す
	for (auto itr = m_children.begin(); itr != m_children.end(); ++itr)
	{
		itr->second->Render();
	}

	m_polygonBody.draw();
	m_drawTexture->Draw(U"Body");

}

void CraneBody::Finalize()
{

	// 範囲for文　子の終了処理を回す
	for (auto itr = m_children.begin(); itr != m_children.end(); ++itr)
	{
		itr->second->Finalize();
	}
}
