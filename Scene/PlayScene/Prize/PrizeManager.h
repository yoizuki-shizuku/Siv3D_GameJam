#pragma once

class IPrizeProduct;
class AcquisitionEffect;
class IPrizeFactory;
class DrawTexture;
class Numeral;

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
	// リザルト表示を行います
	void Render_Result();


	/// @brief 景品を生成します
	/// @param prize 景品の種類
	/// @param world 物理空間
	/// @param num 総数
	void CreatePrize(IPrizeFactory* prize, P2World world, int num,int pulsPosY = 0);

	bool GetPlayFin();

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

	// レスキュー完了したか否か
	bool m_rescueFlag;

	// クリア時アニメーション用の変数

	// 縦に矩形を伸ばす
	float m_animationTime_Vertical;

	// 横に矩形を伸ばす
	float m_animationTime_Beside;

	// 救出対象アニメーション
	float m_animationTime_Rescue;

	std::unique_ptr<Numeral>			m_scoreRender;

};
