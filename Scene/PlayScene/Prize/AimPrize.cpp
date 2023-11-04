#include "../../../stdafx.h"
#include "AimPrize.h"

AimPrizeProduct::AimPrizeProduct(P2World world)
{

	Rect::value_type scale = 30;

	m_polygonBody = world.createQuad(P2Dynamic, Vec2(), Quad(Rect(scale, scale, scale, scale)));
	m_polygonBody.setGravityScale(m_weight);

}

AimPrizeProduct::~AimPrizeProduct()
{
}

void AimPrizeProduct::Update()
{
}

void AimPrizeProduct::Render()
{

	m_polygonBody.draw(Palette::Royalblue);

}
