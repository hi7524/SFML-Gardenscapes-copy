#pragma once
#include "Scene.h"
#include "ButtonGo.h"

class SceneDev1 : public Scene
{
protected:
	SpriteGo* background = new SpriteGo("graphics/background.png");
	ButtonGo* startBtn = new ButtonGo();

	//ButtonGo* testBtn = new ButtonGo();

	std::vector<ButtonGo*> buttons;

public:
	SceneDev1();
	~SceneDev1() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void ClickButton();
};