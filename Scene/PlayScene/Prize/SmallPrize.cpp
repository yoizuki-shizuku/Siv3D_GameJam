#include "../../../stdafx.h"
#include "SmallPrize.h"

SmallPrizeFactory::SmallPrizeFactory()
{
}

SmallPrizeFactory::~SmallPrizeFactory()
{
}

SmallPrizeProduct::SmallPrizeProduct(P2World world)
{

	m_polygonBody = world.createQuad(P2Dynamic, Vec2(),Quad(Rect(20.0f,20.0f,20.0f,20.0)));
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

	m_polygonBody.draw(Palette::Gray);

}
