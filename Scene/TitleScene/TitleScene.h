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
	struct TexInfo
	{
		Vec2 POS;
		double SCALE;
		double ROTATE;
		double TIMER;
	};

	// テクスチャ
	std::unique_ptr<DrawTexture> m_textures;

	// 選択フラグ
	bool is_selectFlag;

	// ロゴのテクスチャ情報
	TexInfo m_logoInfo;
	const double SWAYING_WIDTH = 1.5;
	const double LOGO_ROTATION = 0.001;

	// 紐の情報
	Bezier2 m_logoBez;
	const Vec2 FULCRUM_POS = { 1280 / 2, 0 };
	Vec2 m_bezMiddlePos;
	const int BEZ_WIDTH = 4;
	const double BEZ_SPEED = 0.0005;
};
