#include "../../../stdafx.h"
#include "BigPrize.h"

BigPrizeProduct::BigPrizeProduct(P2World world)
{

	Rect::value_type scale = 20;

	m_polygonBody = world.createCircle(P2Dynamic, Vec2(), Circle(scale));
	m_polygonBody.setGravityScale(m_weight);

}

BigPrizeProduct::~BigPrizeProduct()
{
}

void BigPrizeProduct::Update()
{
}

void BigPrizeProduct::Render()
{

	m_polygonBody.draw(Palette::Red);

}
