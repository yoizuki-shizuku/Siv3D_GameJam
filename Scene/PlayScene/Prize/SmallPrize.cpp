#include "../../../stdafx.h"
#include "SmallPrize.h"

SmallPrizeProduct::SmallPrizeProduct(P2World world)
{
	Rect::value_type scale = 20;
	m_polygonBody = world.createQuad(P2Dynamic, Vec2(),Quad(Rect(scale, scale, scale, scale)));
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
