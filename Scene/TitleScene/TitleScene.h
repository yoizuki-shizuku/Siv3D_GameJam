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

	// テクスチャ
	std::unique_ptr<DrawTexture> m_textures;
};
