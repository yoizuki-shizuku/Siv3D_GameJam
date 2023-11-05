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
	s3d::Scene::SetBackground(Palette::Black);

	// 最初はスタート
	is_selectFlag = true;

	// テクスチャクラスを作成
	m_tex = std::make_unique<DrawTexture>();

	// 画像を追加
	m_logoInfo = TexInfo({ 1280 / 2, 720 / 2 - 100 }, 1.5, 0.0, 0.0);
	m_tex->AddTexture(U"Logo", U"../Resources/Textures/Logo.png");
	m_tex->SetTexInfo(U"Logo", m_logoInfo.POS, m_logoInfo.SCALE);

	m_tex->AddTexture(U"Play", U"../Resources/Textures/Title_Start.png");
	m_tex->SetTexInfo(U"Play", Vec2{ 900,650 }, m_startRate);

	m_tex->AddTexture(U"Exit", U"../Resources/Textures/Title_Exit.png");
	m_tex->SetTexInfo(U"Exit", Vec2{ 1100,650 }, m_exitRate);

	m_tex->AddTexture(U"Back", U"../Resources/Textures/TitleBack.png");
	m_tex->SetTexInfo(U"Back", Vec2{ 1280 / 2, 720 / 2 },1.0);


	// 紐情報を初期化
	m_bezStartPos = { 1280 / 2, 0 };
	m_bezMiddlePos = { m_logoInfo.POS.x, m_logoInfo.POS.y / 2 };
	m_bez = { m_bezStartPos ,m_bezMiddlePos ,Vec2{ m_logoInfo.POS.x , m_logoInfo.POS.y - 50} };

	//	BGMの読み込みと再生
	m_bgm = Audio{ U"../Resources/Audio/Amusement-Arcade.mp3", Loop::Yes };
	m_bgm.play(1s);
}

void TitleScene::Update()
{
	// ロゴの更新
	UpdateLogo();

	// 紐の更新
	UpdateBez();

	// フォントの更新
	UpdateFonts();

	// ゲーミング背景の更新
	UpdateGaming();

	if (KeySpace.down())
	{
		is_selectFlag ? ChangeScene<PlayScene>() : ExitGame();
		m_bgm.stop(1s);
	}
}

void TitleScene::Render()
{
	// 紐の描画
	m_bez.draw(BEZ_WIDTH, HSV(360.0 - (s3d::Scene::Time() * 60.0),0.5,0.8));

	// 背景の描画
	m_tex->Draw(U"Back");

	// タイトルロゴの描画
	m_tex->Draw(U"Logo");

	// スタートイグジットの描画
	m_tex->Draw(U"Play");
	m_tex->Draw(U"Exit");
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
	m_tex->SetTexInfo(U"Logo", m_logoInfo.POS, m_logoInfo.SCALE, m_logoInfo.ROTATE);
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
	m_tex->SetTexInfo(U"Play", m_tex->GetTexInfo(U"Play").POS, m_startRate);
	m_tex->SetTexInfo(U"Exit", m_tex->GetTexInfo(U"Exit").POS, m_exitRate);
}

void TitleScene::UpdateGaming()
{
	const double hue = (s3d::Scene::Time() * 60.0);

	m_tex->SetTexInfo(U"Back", m_tex->GetTexInfo(U"Back").POS, m_tex->GetTexInfo(U"Back").SCALE,
		m_tex->GetTexInfo(U"Back").ROTATE, m_tex->GetTexInfo(U"Back").MIRRORED, m_tex->GetTexInfo(U"Back").FLIPPED,
		HSV{ hue ,0.5,1.0 });
}
