#include "TitleScene.h"

// テクスチャ情報
#include "../../Libraries/Nakamura/DrawTexture.hpp"

#include "../PlayScene/PlayScene.h"

TitleScene::TitleScene()
	: MyClass::Scene()
	, is_selectFlag{ false }		// 選択フラグ（TrueでStart）
	, m_logoInfo{}					// ロゴの情報
	, m_bez{}						// 紐を再現
	, m_startRate{1.0}				// スタートの拡大率
	, m_exitRate{1.0}				// イグジットの拡大率
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

	m_textures->AddTexture(U"Start", U"../Resources/Textures/Title_Start.png");
	m_textures->SetTexInfo(U"Start", Vec2{ 900,650 }, m_startRate);

	m_textures->AddTexture(U"Exit", U"../Resources/Textures/Title_Exit.png");
	m_textures->SetTexInfo(U"Exit", Vec2{ 1100,650 }, m_exitRate);


	// 紐情報を初期化
	m_bezStartPos = { 1280 / 2, 0 };
	m_bezMiddlePos = { m_logoInfo.POS.x, m_logoInfo.POS.y / 2 };
	m_bez = { m_bezStartPos ,m_bezMiddlePos ,Vec2{ m_logoInfo.POS.x , m_logoInfo.POS.y - 50} };

}

void TitleScene::Update()
{
	// ロゴの更新
	UpdateLogo();

	// 紐の更新
	UpdateBez();

	// フォントの更新
	UpdateFonts();

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
	m_bez.draw(BEZ_WIDTH, Palette::Orangered);

	// タイトルロゴの描画
	m_textures->Draw(U"Logo");

	// スタートイグジットの描画
	m_textures->Draw(U"Start");
	m_textures->Draw(U"Exit");
}

void TitleScene::Finalize()
{
}

void TitleScene::UpdateLogo()
{
	// 横揺れ処理
	m_logoInfo.TIMER += s3d::Scene::DeltaTime();
	m_logoInfo.POS.x += cos(m_logoInfo.TIMER) * SWAYING_WIDTH;
	m_logoInfo.ROTATE += sin(m_logoInfo.TIMER) * LOGO_ROTATION;

	// テクスチャに情報をセット
	m_textures->SetTexInfo(U"Logo", m_logoInfo.POS, m_logoInfo.SCALE, m_logoInfo.ROTATE);
}

void TitleScene::UpdateBez()
{
	// ロゴを吊るした挙動
	m_bezStartPos.x += cos(m_logoInfo.TIMER) * 1.5;
	m_bezMiddlePos.x = (m_bezMiddlePos.lerp(m_logoInfo.POS, BEZ_SPEED)).x;
	m_bez = { m_bezStartPos, m_bezMiddlePos ,Vec2{ m_logoInfo.POS.x , m_logoInfo.POS.y - 50} };
}

void TitleScene::UpdateFonts()
{
	// シーン遷移切り替え
	if (KeyRight.down() || KeyLeft.down())
	{
		is_selectFlag = !is_selectFlag;
	}

	// ラープ
	auto lerp = [](double a, double b, double t) {return a + t * (b - a); };

	// スタートを拡大
	if (is_selectFlag)
	{
		m_startRate = lerp(m_startRate, SELECT_RATE,  0.5);
		m_exitRate  = lerp(m_exitRate,  DEFAULT_RATE, 0.5);
	}
	else
	{
		m_startRate = lerp(m_startRate, DEFAULT_RATE, 0.5);
		m_exitRate  = lerp(m_exitRate,  SELECT_RATE,  0.5);
	}

	// 拡大率をセット
	m_textures->SetTexInfo(U"Start", m_textures->GetTexInfo(U"Start").POS, m_startRate);
	m_textures->SetTexInfo(U"Exit", m_textures->GetTexInfo(U"Exit").POS, m_exitRate);
}
