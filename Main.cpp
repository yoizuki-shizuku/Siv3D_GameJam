﻿# include <Siv3D.hpp> // OpenSiv3D v0.6.11

#include "Scene/MySceneManager.h"

void Main()
{
	// タイトルを変更
	Window::SetTitle(U"CraneResque");
	//	ウィンドウの大きさを変更
	Window::Resize(1280, 720);

	std::unique_ptr<MyClass::SceneManager> sceneManager = std::make_unique<MyClass::SceneManager>();
	sceneManager->Initialize();


	while (System::Update())
	{
		//	Printの出力をクリア
		ClearPrint();

		sceneManager->Update();
		sceneManager->Render();

		if (sceneManager->GetExitGame()) break;
	}

	sceneManager->Finalize();
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要な場合があります。
//
