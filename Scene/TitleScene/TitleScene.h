#pragma once

#include "../MyScene.h"

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

};
