#pragma once
#include "Scene.h"

class SceneDev1 : public Scene
{
protected:

public:
	SceneDev1();
	~SceneDev1() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};