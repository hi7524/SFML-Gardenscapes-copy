#include "stdafx.h"
#include "ButtonGo.h"

ButtonGo::ButtonGo(const std::string& name)
	:GameObject(name)
{
}

void ButtonGo::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
}

void ButtonGo::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	sprite.setRotation(rot);
}

void ButtonGo::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	sprite.setScale(s);
}

void ButtonGo::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	sprite.setOrigin(o);
}

void ButtonGo::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(sprite, preset);
	}
}

void ButtonGo::Init()
{
	sortingLayer = SortingLayers::UI;
}

void ButtonGo::Release()
{
}

void ButtonGo::Reset()
{
	OriginSprite();
}

void ButtonGo::Update(float dt)
{
}

void ButtonGo::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
	window.draw(text);
}

void ButtonGo::SetText(std::string s)
{
	text.setFont(FONT_MGR.Get("fonts/minecraft_font.ttf"));
	text.setString(s);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(20);
	Utils::SetOrigin(text, Origins::MC);
	text.setPosition(sprite.getPosition());
}

void ButtonGo::OriginSprite()
{
	sprite.setTexture(TEXTURE_MGR.Get(spriteId));
	Utils::SetOrigin(sprite, Origins::MC);
}

void ButtonGo::HighlighteSprite()
{
	sprite.setTexture(TEXTURE_MGR.Get(highlightedSpriteId));
	Utils::SetOrigin(sprite, Origins::MC);
}

void ButtonGo::SetOnClick(const std::function<void()>& callback)
{
	onClick = callback;
}

void ButtonGo::OnClick()
{
	if (onClick)
	{
		onClick();
	}
}