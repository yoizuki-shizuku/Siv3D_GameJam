#include "../../../stdafx.h"
#include "AimPrize.h"

AimPrizeProduct::AimPrizeProduct(P2World world)
{

	Rect::value_type scale = 20;

	m_polygonBody = world.createQuad(P2Dynamic, Vec2(), Quad(Rect(-10, -10, 20, 20)));
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
}
