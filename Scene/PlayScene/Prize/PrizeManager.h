#pragma once

class IPrizeProduct;
class AcquisitionEffect;

class PrizeManager
{
public:
	PrizeManager();
	~PrizeManager();

	void Initialize(P2World world);

	void Update();

	void Render();

private:

	// プライズリスト
	Array<IPrizeProduct*> m_prizes;

	// エフェクトクラス
	Effect	m_effect;

	double m_time;

};
