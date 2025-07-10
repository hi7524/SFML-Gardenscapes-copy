#include "stdafx.h"
#include "SceneDev1.h"

SceneDev1::SceneDev1() 
	: Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	Scene::Init();
}

void SceneDev1::Enter()
{
	Scene::Enter();
}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}