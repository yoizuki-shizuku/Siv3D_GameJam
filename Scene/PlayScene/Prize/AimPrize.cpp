#include "../../../stdafx.h"
#include "AimPrize.h"

AimPrizeProduct::AimPrizeProduct(P2World world)
{

	m_polygonBody = world.createQuad(P2Dynamic, Vec2(), Quad(Rect(30.0f, 30.0f, 30.0f, 30.0)));
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



AimPrizeFactory::AimPrizeFactory()
{
}

AimPrizeFactory::~AimPrizeFactory()
{
}
