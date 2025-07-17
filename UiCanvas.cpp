#include "stdafx.h"
#include "UiCanvas.h"

UiCanvas::UiCanvas(const std::string& name)
	:GameObject(name)
{
	sortingLayer = SortingLayers::UI;
}

void UiCanvas::Init()
{
}

void UiCanvas::Release()
{
}

void UiCanvas::Reset()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	swapCountText.setFont(FONT_MGR.Get("fonts/minecraft_font.ttf"));
	objCountText.setFont(FONT_MGR.Get("fonts/minecraft_font.ttf"));
	stageClearText.setFont(FONT_MGR.Get("fonts/minecraft_font.ttf"));

	diamondSprite.SetTextureId("graphics/diamond.png");
	diamondSprite.Reset();
	diamondSprite.SetPosition({ 100.f, 250.f });  // 원하는 좌표로 설정
	diamondSprite.SetOrigin(Origins::MC);

	sf::Vector2f diaSpritePos = diamondSprite.GetPosition();
	sf::Vector2f countTxtPos = { diaSpritePos.x + 20.f, diaSpritePos.y + 20.f };
	objCountText.setString("16");
	objCountText.setFillColor(sf::Color::White);
	objCountText.setCharacterSize(21);
	objCountText.setPosition(countTxtPos);
	Utils::SetOrigin(objCountText, Origins::MC);

	swapCountText.setString("22");
	swapCountText.setFillColor(sf::Color::White);
	swapCountText.setCharacterSize(25);
	swapCountText.setPosition({ 100.f, 400.f });
	Utils::SetOrigin(swapCountText, Origins::MC);

	stageClearText.setString("Stage1 Clear");
	stageClearText.setFillColor(sf::Color::Yellow);
	stageClearText.setCharacterSize(40);
	stageClearText.setPosition(windowSize * 0.5f);
	Utils::SetOrigin(stageClearText, Origins::MC);

	background.setSize(windowSize);
	background.setFillColor(sf::Color(0, 0, 0, 180));

	btnBackToGame->Init();
	btnBackToGame->Reset();
	btnBackToGame->SetPosition({ windowSize.x * 0.5f, 300.f });
	btnBackToGame->SetText("Back to Game");
	btnBackToGame->SetOnClick([this]() {
		pauseUI = false;
		});

	btnQuit->Init();
	btnQuit->Reset();
	btnQuit->SetPosition({ windowSize.x * 0.5f, 400.f });
	btnQuit->SetText("Quit to Title");
	btnQuit->SetOnClick([]() {
		SCENE_MGR.ChangeScene(SceneIds::Dev1);
		});

	buttons.push_back(btnBackToGame);
	buttons.push_back(btnQuit);
}

void UiCanvas::Update(float dt)
{
	if (pauseUI)
	{
		ClickButton();
	}
}

void UiCanvas::Draw(sf::RenderWindow& window)
{
	if (!pauseUI)
	{
		diamondSprite.Draw(window);
		window.draw(objCountText);
		window.draw(swapCountText);
	}
	else
	{
		window.draw(background);
		btnBackToGame->Draw(window);
		btnQuit->Draw(window);
	}

	
	//window.draw(stageClearText);
}

void UiCanvas::SetSwapCountText(int count)
{
	swapCountText.setString(std::to_string(count));
}

void UiCanvas::SetObjCountText(int count)
{
	objCountText.setString(std::to_string(count));
}

void UiCanvas::ClickButton()
{
	sf::Vector2f mousePos = SCENE_MGR.GetCurrentScene()->ScreenToUi(InputMgr::GetMousePosition());

	// 버튼 클릭
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		for (auto btn : buttons)
		{
			if ((btn->GetGlobalBounds().left <= mousePos.x && mousePos.x <= btn->GetGlobalBounds().left + btn->GetGlobalBounds().width)
				&& (btn->GetGlobalBounds().top <= mousePos.y && mousePos.y <= btn->GetGlobalBounds().top + btn->GetGlobalBounds().height))
			{
				btn->OnClick();
				break;
			}
		}
	}

	// 버튼 하이라이트
	for (auto btn : buttons)
	{
		if ((btn->GetGlobalBounds().left <= mousePos.x && mousePos.x <= btn->GetGlobalBounds().left + btn->GetGlobalBounds().width)
			&& (btn->GetGlobalBounds().top <= mousePos.y && mousePos.y <= btn->GetGlobalBounds().top + btn->GetGlobalBounds().height))
		{
			btn->HighlighteSprite();
		}
		else
		{
			btn->OriginSprite();
		}
	}
}