#pragma once

namespace MyClass
{
	class Transition
	{
	public:
		//	定数バッファ
		struct CBuffer
		{
			float ratio;
		};

	public:
		Transition();
		~Transition() = default;

		void Initialize();
		void Update();
		void Render();
		void Finalize();

		void StartFadeIn();
		void StartFadeOut();

		bool ProcessCheckFadeIn() const { return m_fadeIn; }
		bool ProcessCheckFadeOut() const { return m_fadeOut; }

	private:
		void FadeInUpdate();
		void FadeOutUpdate();

	private:
		//	進行度
		float m_ratio;
		//	処理時間を計測
		float m_processTimer;

		//	実行中のフェード処理
		bool m_fadeIn, m_fadeOut;

		//	フェードに使う四角形
		Rect m_rect;
		//	ルール画像
		Texture m_ruleTex;
		//	ピクセルシェーダー
		PixelShader m_ps;
		//	受け渡し用の定数バッファー
		ConstantBuffer<CBuffer> m_cb;

	};
}
