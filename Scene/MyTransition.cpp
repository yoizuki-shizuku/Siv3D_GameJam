#include "MyTransition.h"

#include "Easing.h"

#define MAX_RATIO	(1.f)
#define MIN_RATIO	(0.f)

//	フェードに適応するLerp関数
#define LERP_FUNCTION	(MyEasing::InOutQuad)

//	フェードにかかる時間
#define FADE_TIME	(1.f)

MyClass::Transition::Transition() :
	m_ratio(0.f),
	m_processTimer(0.f),
	m_fadeIn(false),
	m_fadeOut(false)
{
}

void MyClass::Transition::Initialize()
{
	int width = s3d::Scene::Width();
	int height = s3d::Scene::Height();

	m_rect = Rect(0, 0, width, height);

	m_ruleTex = Texture{ U"../Resources/Textures/Rule.png" };
	m_ps = HLSL{ U"../Resources/Shader/TransitionPS.hlsl",U"main" };
}

void MyClass::Transition::Update()
{
	FadeInUpdate();
	FadeOutUpdate();
}

void MyClass::Transition::Render()
{
	int width = s3d::Scene::Width();
	int height = s3d::Scene::Height();
	m_cb->ratio = m_ratio;

	//	テクスチャを設定
	//Graphics2D::SetPSTexture(1, m_ruleTex);

	{
		// 定数バッファを設定
		Graphics2D::SetPSConstantBuffer(1, m_cb);

		//	シェーダを適用
		const ScopedCustomShader2D shader{ m_ps };
		m_ruleTex.resized(width, height).draw();
	}
}

void MyClass::Transition::Finalize()
{
}

void MyClass::Transition::StartFadeIn()
{
	//	実行中に処理できないようにする
	if (m_fadeIn || m_fadeOut) return;

	m_ratio = MAX_RATIO;
	m_processTimer = 0.f;
	m_fadeIn = true;
}

void MyClass::Transition::StartFadeOut()
{
	//	実行中に処理できないようにする
	if (m_fadeIn || m_fadeOut) return;

	m_ratio = MIN_RATIO;
	m_processTimer = 0.f;
	m_fadeOut = true;
}

void MyClass::Transition::FadeInUpdate()
{
	//	フェードイン実行中でなければ処理しない
	if (!m_fadeIn) return;

	//	タイマーを更新
	m_processTimer += static_cast<float>(s3d::Scene::DeltaTime());

	//	処理時間を過ぎたら、フェードインを終了
	if (m_processTimer > FADE_TIME)
	{
		m_processTimer = FADE_TIME;
		m_fadeIn = false;
	}

	//	処理時間による時間の割合
	float t = m_processTimer / FADE_TIME;

	//	easingを適用
	m_ratio = MyEasing::Lerp(MAX_RATIO, MIN_RATIO, t, LERP_FUNCTION);
}

void MyClass::Transition::FadeOutUpdate()
{
	//	フェードイン実行中でなければ処理しない
	if (!m_fadeOut) return;

	//	タイマーを更新
	m_processTimer += static_cast<float>(s3d::Scene::DeltaTime());

	//	処理時間を過ぎたら、フェードインを終了
	if (m_processTimer > FADE_TIME)
	{
		m_processTimer = FADE_TIME;
		m_fadeOut = false;
	}

	//	処理時間による時間の割合
	float t = m_processTimer / FADE_TIME;

	//	easingを適用
	m_ratio = MyEasing::Lerp(MIN_RATIO, MAX_RATIO, t, LERP_FUNCTION);
}
