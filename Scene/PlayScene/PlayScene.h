﻿#pragma once

#include "../MyScene.h"

class CraneBody;
class AcquisitionEffect;
class Field;
class PrizeManager;
class Numeral;
class Gaming;

class PlayScene : public MyClass::Scene
{
public:
	PlayScene();
	~PlayScene() = default;

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Finalize() override;

private:

	std::unique_ptr<CraneBody>			m_craneBody;

	std::unique_ptr<AcquisitionEffect>	m_effect;

	std::unique_ptr<P2World>			m_p2World;

	// 足場（仮）
	std::unique_ptr<Field>				m_field;

	std::unique_ptr<PrizeManager>		m_prizeManager;

	std::unique_ptr<Numeral>			m_numeral;

	std::unique_ptr<Numeral>			m_craneCount;

	std::unique_ptr<Gaming>				m_tex;

	std::unique_ptr<Texture>			m_backTex;

	// 2D 物理演算のシミュレーション蓄積時間（秒）
	double m_accumulatedTime = 0.0;

	//	BGM
	Audio m_bgm;

};
