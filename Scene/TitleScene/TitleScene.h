#pragma once

#include "../MyScene.h"

class DrawTexture;
class TitleScene : public MyClass::Scene
{
public:
	TitleScene();
	~TitleScene() = default;

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Finalize() override;

private:

	// ロゴの更新
	void UpdateLogo();

	// 紐の更新
	void UpdateBez();

	// StartExitの更新
	void UpdateFonts();

	// 背景色をゲーミング風に更新
	void UpdateGaming();

private:
	struct TexInfo
	{
		Vec2 POS;
		double SCALE;
		double ROTATE;
		double TIMER;
	};

	// テクスチャ
	std::unique_ptr<DrawTexture> m_tex;

	// 選択フラグ
	bool is_selectFlag;

	// ロゴのテクスチャ情報
	TexInfo m_logoInfo;
	const double SWAYING_WIDTH = 1.5;
	const double LOGO_ROTATION = 0.001;

	// StartExit
	double m_startRate;
	double m_exitRate;
	const double SELECT_RATE = 1.2;
	const double DEFAULT_RATE = 1.0;

	// 紐の情報
	Bezier2 m_bez;
	Vec2 m_bezStartPos;
	Vec2 m_bezMiddlePos;
	const int BEZ_WIDTH = 4;
	const double BEZ_SPEED = 0.0005;
};
