#pragma once

class IPrizeProduct;
class AcquisitionEffect;
class IPrizeFactory;
class DrawTexture;

class PrizeManager
{
public:
	PrizeManager();
	~PrizeManager();

	void Initialize(P2World world);

	void Update();

	void Render();

	// スコアを返します 
	int GetScore() { return m_score; }

	/// @brief 景品を生成します
	/// @param prize 景品の種類
	/// @param world 物理空間
	/// @param num 総数
	void CreatePrize(IPrizeFactory* prize, P2World world, int num,int pulsPosY = 0);


private:

	// プライズリスト
	Array<IPrizeProduct*> m_prizes;

	// テクスチャクラス
	std::unique_ptr<DrawTexture> m_drawTexture;

	// エフェクトクラス
	Effect	m_effect;

	double m_time;

	// スコア記録
	int m_score;

};
