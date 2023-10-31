#pragma once

class Numeral
{
public:
	Numeral();
	~Numeral() = default;

	void Render();

	//	表示する数字を設定する
	void SetNumber(int num);
	//	表示する位置を設定する(一桁目の左上が基準)
	void SetPosition(s3d::Vec2 pos) { m_position = pos; }
	//	数字の各桁の間隔を設定する
	void SetSpace(float space) { m_space = space; }

	//	画像を読み込む
	//	等間隔で切り取るようにされているため
	//	横方向に一列かつ同じ間隔で配置された画像にする
	void LoadTexture(const s3d::FilePath path);
	
private:
	Texture m_texture;

	int m_number;
	int m_digit;
	float m_space;
	s3d::Vec2 m_position;
};
