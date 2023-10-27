#include "TitleScene.h"

// テクスチャ情報
#include "../../Libraries/Nakamura/DrawTexture.hpp"

#include "../PlayScene/PlayScene.h"

TitleScene::TitleScene()
	: MyClass::Scene()
	, is_selectFlag{ false }		// 選択フラグ（TrueでStart）
	, m_logoInfo{}					// ロゴの情報
	, m_logoBez{}					// 紐を再現
{
}

void TitleScene::Initialize()
{
	s3d::Scene::SetBackground(Palette::White);

	// 最初はスタート
	is_selectFlag = true;

	// テクスチャクラスを作成
	m_textures = std::make_unique<DrawTexture>();

	// 画像を追加
	m_logoInfo = TexInfo({ 1280 / 2, 720 / 2 - 100 }, 1.5, 0.0, 0.0);
	m_textures->AddTexture(U"Logo", U"../Resources/Textures/Logo.png");
	m_textures->SetTexInfo(U"Logo", m_logoInfo.POS, m_logoInfo.SCALE);

	// 紐情報を初期化
	m_bezMiddlePos = { m_logoInfo.POS.x, m_logoInfo.POS.y / 2 };
	m_logoBez = { FULCRUM_POS ,m_bezMiddlePos ,Vec2{ m_logoInfo.POS.x , m_logoInfo.POS.y - 50} };
}

void TitleScene::Update()
{
	// 横揺れ処理
	m_logoInfo.TIMER += s3d::Scene::DeltaTime();
	m_logoInfo.POS.x += cos(m_logoInfo.TIMER) * SWAYING_WIDTH;
	m_logoInfo.ROTATE += sin(m_logoInfo.TIMER) * LOGO_ROTATION;

	// テクスチャに情報をセット
	m_textures->SetTexInfo(U"Logo", m_logoInfo.POS, m_logoInfo.SCALE,m_logoInfo.ROTATE);

	// 紐の動き
	m_bezMiddlePos.x = (m_bezMiddlePos.lerp(m_logoInfo.POS, BEZ_SPEED)).x;
	m_logoBez = { FULCRUM_POS, m_bezMiddlePos ,Vec2{ m_logoInfo.POS.x , m_logoInfo.POS.y - 50} };

	// シーン遷移切り替え
	if (KeyRight.down() || KeyLeft.down())
	{
		is_selectFlag = !is_selectFlag;
	}
	if (KeySpace.down())
	{
		is_selectFlag ? ChangeScene<PlayScene>() : ExitGame();
	}
}

void TitleScene::Render()
{
	Print << U"TitleScene";

	is_selectFlag ? Print << U"Play" : Print << U"Exit";

	// 紐の描画
	m_logoBez.draw(BEZ_WIDTH, Palette::Orangered);

	// タイトルロゴの描画
	m_textures->Draw(U"Logo");
}

void TitleScene::Finalize()
{
}
