#include "CraneArm.h"
#include "CraneBody.h"

// 位置調整用
#define ADJUSTMENT_POS Vec2(-10,60)

// 開閉時位置調整用
#define ADJUSTMENT_ROTATE Vec2(70,20)

CraneArm::CraneArm():
	m_openTime()
{
}

void CraneArm::Initialize(P2World& world)
{

	m_drawTexture = std::make_unique<DrawTexture>();
	// 使用する画像
	m_drawTexture->AddTexture(U"Arm", U"../Resources/Textures/CraneArm.png");

	//// アルファ値 1 以上の領域を Polygon 化する
	const Polygon polygon = m_drawTexture->GetImage(U"Arm").alphaToPolygonCentered(1, AllowHoles::No);

	// Polygon 単純化の許容距離（ピクセル）
	double maxDistance = 4.0;

	// 単純化した Polygon
	Polygon simplifiedPolygon = polygon.simplified(maxDistance);

	// ポリゴンに当たり判定を付ける
	m_polygonBody = world.createPolygon(P2Static, Vec2(), simplifiedPolygon);
}

void CraneArm::Update(P2World& world)
{
	// 警告対策
	world;

	// アーム位置を調整する
	m_pos = m_pos + ADJUSTMENT_POS;
	Vec2 polygonPos = Vec2(m_pos.x, m_pos.y);

	// 開閉時間遷移の上限下限設定
	m_openTime = std::min(std::max(m_openTime, 0.0f), 1.0f);

	// 親から開閉フラグを受け取り開閉を行う
	if (dynamic_cast<CraneBody*>(m_parent)->GetOpenFlag())m_openTime += (float)Scene::DeltaTime();
	else m_openTime -= (float)Scene::DeltaTime();

	// ポリゴンに角度を持たせる
	m_polygonBody = m_polygonBody.setAngle(m_openTime);

	// 角度を持たせるとずれるので位置を調整する
	m_polygonBody = m_polygonBody.setPos(Vec2(polygonPos.x - ADJUSTMENT_ROTATE.x * sinf(m_openTime),
											  polygonPos.y + ADJUSTMENT_ROTATE.y * cosf(m_openTime)));

	m_drawTexture->SetTexInfo(U"Arm", m_polygonBody.getPos(), 1.0f, m_polygonBody.getAngle());

}

void CraneArm::Render()
{
	// 描画
	m_drawTexture->Draw(U"Arm");
	m_polygonBody.drawWireframe();

}

void CraneArm::Finalize()
{
}

Vec2 CraneArm::GetAccelerator()
{
	return Vec2();
}

Vec2 CraneArm::GetMaxAccelerator()
{
	return Vec2();
}

Vec2 CraneArm::GetBrake()
{
	return Vec2();
}

bool CraneArm::GetOpen()
{
	return m_openTime >= 1.0f;
}

bool CraneArm::GetClose()
{
	return m_openTime <= 0.0f;
}
