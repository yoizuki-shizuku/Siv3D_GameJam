#include "Numeral.h"

Numeral::Numeral() :
	m_number(0),
	m_digit(0),
	m_space(0.f),
	m_position()
{

}

void Numeral::Render()
{
	int forCalc = m_number;

	for (size_t i = 0; i < m_digit; i++)
	{
		int num = forCalc % 10;
		m_texture(m_texture.width() / 10 * num, 0, m_texture.width() / 10, m_texture.height()).
			draw(s3d::Vec2(m_position.x - (m_texture.width() / 10 * i) - (m_space * i), m_position.y), Palette::White);
		forCalc /= 10;
	}
}

void Numeral::SetNumber(int num)
{
	m_number = num;
	//m_digit = static_cast<int>(log10(m_number) + 1);
	m_digit = std::to_string(num).length();
}

void Numeral::LoadTexture(const s3d::FilePath path)
{
	m_texture = Texture{ path };
}
