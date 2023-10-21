#pragma once

#include "../MyScene.h"

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

};
