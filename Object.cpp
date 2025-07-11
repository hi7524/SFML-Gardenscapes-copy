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
	sortingLayer = SortingLayers::Default;
	sortingOrder = 0;

	//std::cout << (int)sortingLayer << std::endl;
	object.setTexture(TEXTURE_MGR.Get(texId));
}

void Object::Release()
{
}

void Object::Reset()
{

	SetRandomType();
	object.setTexture(TEXTURE_MGR.Get(texId));
	std::cout << (int)objectType << std::endl;


	Utils::SetOrigin(object, Origins::MC);
}

void Object::Update(float dt)
{
}

void Object::Draw(sf::RenderWindow& window)
{
	if (isActive)
	{
		window.draw(object);
	}
}

// 아이템 타입 랜덤 설정
void Object::SetRandomType()
{
	int random = Utils::RandomRange(0, (int)ObjectType::Count);

	switch ((ObjectType)random)
	{
	case ObjectType::Diamond:
		objectType = ObjectType::Diamond;
		texId = "graphics/diamond.png";
		break;

	case ObjectType::Cookie:
		objectType = ObjectType::Cookie;
		texId = "graphics/cookie.png";
		break;

	case ObjectType::Redstone:
		objectType = ObjectType::Redstone;
		texId = "graphics/redstone.png";
		break;

	case ObjectType::Lava:
		objectType = ObjectType::Lava;
		texId = "graphics/lava.png";
		break;

	case ObjectType::Potato:
		objectType = ObjectType::Potato;
		texId = "graphics/potato.png";
		break;

	default:
		objectType = ObjectType::None;
		break;
	}
}