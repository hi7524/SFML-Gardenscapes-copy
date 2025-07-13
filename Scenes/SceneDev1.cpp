#include "stdafx.h"
#include "SceneDev1.h"

SceneDev1::SceneDev1() 
	: Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	// Ã¢ ¼³Á¤
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(windowSize);
	worldView.setCenter(windowSize * 0.5f);

	texIds.push_back("graphics/background.png");

	Scene::Init();
}

void SceneDev1::Enter()
{
	Scene::Enter();

	SpriteGo* background = new SpriteGo("graphics/background.png");
	background->Init();
	background->Reset();
	AddGameObject(background);
}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}