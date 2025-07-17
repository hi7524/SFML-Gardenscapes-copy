#include "stdafx.h"
#include "SceneDev1.h"
#include "SpriteGo.h"

SceneDev1::SceneDev1() 
	: Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	// 창 설정
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	texIds.push_back("graphics/background.png");
	texIds.push_back("graphics/button.png");
	texIds.push_back("graphics/buttonHighlighted.png");
	fontIds.push_back("fonts/minecraft_font.ttf");

	Scene::Init();
}

void SceneDev1::Enter()
{
	Scene::Enter();

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	background->Init();
	background->sortingLayer = SortingLayers::UI;
	background->Reset();
	AddGameObject(background);


	startBtn->Init();
	startBtn->Reset();
	startBtn->SetPosition({ windowSize.x * 0.5f, 400.f });
	startBtn->SetText("Start Game");
	AddGameObject(startBtn);
	startBtn->SetOnClick([]() {
		SCENE_MGR.ChangeScene(SceneIds::Dev2);
		});

	buttons.push_back(startBtn);
}

void SceneDev1::Update(float dt)
{
	ClickButton();
	
	Scene::Update(dt);
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

// 버튼 클릭
void SceneDev1::ClickButton()
{
	sf::Vector2f mousePos = ScreenToUi(InputMgr::GetMousePosition());

	for (auto btn : buttons)
	{
		// 버튼 하이라이트 효과
		if ((btn->GetGlobalBounds().left <= mousePos.x && mousePos.x <= btn->GetGlobalBounds().left + btn->GetGlobalBounds().width)
			&& (btn->GetGlobalBounds().top <= mousePos.y && mousePos.y <= btn->GetGlobalBounds().top + btn->GetGlobalBounds().height))
		{
			btn->HighlighteSprite();
		}
		else
		{
			btn->OriginSprite();
		}
		
		// 버튼 클릭
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			btn->OnClick();
		}
	}
}