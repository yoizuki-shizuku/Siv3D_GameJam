#include "../../../stdafx.h"
#include "Field.h"

#include "../../../Libraries/Nakamura/DrawTexture.hpp"

Field::Field()
{
}

Field::~Field()
{
}

void Field::Initialize(P2World world)
{
	m_drawTexture = std::make_unique<DrawTexture>();
	// 使用する画像
	m_drawTexture->AddTexture(U"Field", U"../Resources/Textures/Stage.png");

	m_drawTexture->SetTexInfo(U"Field", Vec2(1280 / 2, 760 / 2),1.0f);

	// アルファ値 1 以上の領域を Polygon 化する
	const Polygon polygon = m_drawTexture->GetImage(U"Field").alphaToPolygonCentered(1, AllowHoles::No);

	// Polygon 単純化の許容距離（ピクセル）
	double maxDistance = 4.0;

	// 単純化した Polygon
	Polygon simplifiedPolygon = polygon.simplified(maxDistance);

	// ポリゴンに当たり判定を付ける
	m_polygonBody = world.createPolygon(P2Static, Vec2(), simplifiedPolygon);

}

void Field::Update(P2World world)
{
}

void Field::Render()
{

	m_drawTexture->Draw(U"Field");
	m_polygonBody.drawWireframe();
}


