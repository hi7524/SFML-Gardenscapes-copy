#pragma once
#include "Scene.h"

class SceneDev2 : public Scene
{
protected:

public:
	SceneDev2();
	~SceneDev2() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};