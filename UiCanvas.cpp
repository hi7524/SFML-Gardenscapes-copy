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
	window.draw(swapCountText);
}

void UiCanvas::SetSwapCountTxt(int count)
{
	swapCountText.setString(std::to_string(count));
}