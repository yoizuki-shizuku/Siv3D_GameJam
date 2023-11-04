#include "Gaming.h"

Gaming::Gaming() :
	m_hsv(0.0, 1.0, 1.0),
	m_scale(1.0),
	m_speed(40.0),
	m_position{}
{
}

void Gaming::Update()
{
	m_hsv.h += s3d::Scene::DeltaTime() * m_speed;
}

void Gaming::Render()
{
	m_texture.draw(m_position, m_hsv);
}

void Gaming::LoadTexture(const s3d::FilePath path)
{
	m_texture = Texture{ path };
}
