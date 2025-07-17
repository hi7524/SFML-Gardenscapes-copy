#pragma once
#include "Scene.h"
#include "ButtonGo.h"

class SceneDev1 : public Scene
{
protected:
	SpriteGo* background = new SpriteGo("graphics/background.png");
	SpriteGo* title = new SpriteGo("graphics/title2.png");
	TextGo* subTitle = new TextGo("fonts/minecraft_font.ttf");
	ButtonGo* startBtn = new ButtonGo();
	ButtonGo* quitBtn = new ButtonGo();

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