#pragma once

class Gaming
{
public:
	Gaming();
	~Gaming() = default;

	//	色を変更するために更新処理を行う
	void Update();
	//	描画
	void Render();

	//	画像を読み込む
	void LoadTexture(const s3d::FilePath path);
	//	色相の変更速度(40がデフォルト)
	void SetChangeSpeed(const double& speed) { m_speed = speed; }
	//	彩度の変更(1.0で最大)
	void SetSaturation(const double& saturation) { m_hsv.s = saturation; }
	//	明度の変更(1.0で最大)
	void SetValue(const double& value) { m_hsv.v = value; }
	//	大きさ(1.0で等倍)
	void SetScale(const double& scale) { m_scale = scale; }
	//	位置
	void SetPosition(const s3d::Vec2& position) { m_position = position; }

private:
	Texture m_texture;

	HSV m_hsv;
	double m_speed;
	double m_scale;
	s3d::Vec2 m_position;

};
