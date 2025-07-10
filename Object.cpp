#include "stdafx.h"
#include "Object.h"

Object::Object(const std::string& name)
	: GameObject(name)
{
}

void Object::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	object.setPosition(pos);
}

void Object::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	object.setRotation(rot);
}

void Object::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	object.setScale(s);
}

void Object::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	object.setOrigin(o);
}

void Object::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(object, preset);
	}
}

void Object::Init()
{
}

void Object::Release()
{
}

void Object::Reset()
{
	SetItemType();
	object.setTexture(TEXTURE_MGR.Get(texId));

	Utils::SetOrigin(object, Origins::MC);
}

void Object::Update(float dt)
{
}

void Object::Draw(sf::RenderWindow& window)
{
	window.draw(object);
}

// 아이템 타입 랜덤 설정
void Object::SetItemType()
{
	int random = Utils::RandomRange(1, (int)ItemType::Count);

	switch ((ItemType)random)
	{
	case ItemType::Diamond:
		itemType = ItemType::Diamond;
		texId = "graphics/diamond.png";
		break;

	case ItemType::Cookie:
		itemType = ItemType::Cookie;
		texId = "graphics/cookie.png";
		break;

	case ItemType::Redstone:
		itemType = ItemType::Redstone;
		texId = "graphics/redstone.png";
		break;

	case ItemType::Lava:
		itemType = ItemType::Lava;
		texId = "graphics/lava.png";
		break;

	case ItemType::Potato:
		itemType = ItemType::Potato;
		texId = "graphics/potato.png";
		break;

	default:
		itemType = ItemType::None;
		break;
	}
}