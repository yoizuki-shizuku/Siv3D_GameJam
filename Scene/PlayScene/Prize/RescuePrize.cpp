#include "../../../stdafx.h"
#include "RescuePrize.h"

RescuePrizeProduct::RescuePrizeProduct(P2World world)
{

	Rect::value_type scale = 25;
	m_polygonBody = world.createQuad(P2Dynamic, Vec2(),Quad(Rect(scale, scale, scale, scale)));
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

	m_polygonBody.draw(Palette::Chocolate);

}
