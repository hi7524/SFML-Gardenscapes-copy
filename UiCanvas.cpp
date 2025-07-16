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
	swapCountText.setFont(FONT_MGR.Get("fonts/minecraft_font.ttf"));
	objCountText.setFont(FONT_MGR.Get("fonts/minecraft_font.ttf"));

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
}

void UiCanvas::Update(float dt)
{

}

void UiCanvas::Draw(sf::RenderWindow& window)
{
	diamondSprite.Draw(window);
	window.draw(objCountText);
	window.draw(swapCountText);
}

void UiCanvas::SetSwapCountText(int count)
{
	swapCountText.setString(std::to_string(count));
}

void UiCanvas::SetObjCountText(int count)
{
	objCountText.setString(std::to_string(count));
}
