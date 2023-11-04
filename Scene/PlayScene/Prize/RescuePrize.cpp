#include "../../../stdafx.h"
#include "RescuePrize.h"

RescuePrizeProduct::RescuePrizeProduct(P2World world)
{

	Rect::value_type scale = 25;
	m_polygonBody = world.createQuad(P2Dynamic, Vec2(),Quad(Rect(-20, -30, 40, 70)));
	m_polygonBody.setGravityScale(m_weight);


}

RescuePrizeProduct::~RescuePrizeProduct()
{
}

void RescuePrizeProduct::Update()
{
}

void RescuePrizeProduct::Render()
{
}
