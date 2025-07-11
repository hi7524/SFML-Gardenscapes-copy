#include "stdafx.h"
#include "Slot.h"

Slot::Slot(const std::string& name)
	:GameObject(name)
{
}

void Slot::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	slotSprite.setPosition(pos);
}

void Slot::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	slotSprite.setRotation(rot);
}

void Slot::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	slotSprite.setScale(s);
}

void Slot::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	slotSprite.setOrigin(o);
}

void Slot::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(slotSprite, preset);
	}
}

void Slot::Init()
{
    sortingLayer = SortingLayers::Background;
	sortingOrder = 0;
}

void Slot::Release()
{

}

void Slot::Reset()
{
	slotSprite.setTexture(TEXTURE_MGR.Get(texId));
	Utils::SetOrigin(slotSprite, Origins::MC);
}

void Slot::Update(float dt)
{

}

void Slot::Draw(sf::RenderWindow& window)
{
	window.draw(slotSprite);
}