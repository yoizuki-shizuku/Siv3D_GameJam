#include "../../../stdafx.h"
#include "SmallPrize.h"

SmallPrizeProduct::SmallPrizeProduct(P2World world)
{
	Rect::value_type scale = 10;
	m_polygonBody = world.createQuad(P2Dynamic, Vec2(), Quad(Rect(-12, -10, 26, 20)));
	m_polygonBody.setGravityScale(m_weight);

}

SmallPrizeProduct::~SmallPrizeProduct()
{
}

void SmallPrizeProduct::Update()
{
}

void SmallPrizeProduct::Render()
{
}
