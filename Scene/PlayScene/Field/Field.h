#pragma once

class DrawTexture;
class Field
{
public:
	Field();
	~Field();

	void Initialize(P2World world);

	void Update(P2World world);

	void Render();

private:

	P2Body m_polygonBody;
	std::unique_ptr<DrawTexture> m_drawTexture;

};
