#pragma once
#include "GameObject.h"

class Object : public GameObject
{
protected:
	enum class ItemType
	{
		None = -1,
		Diamond,
		Cookie,
		Redstone,
		Lava,
		Potato,
		Count
	};

	sf::Sprite object;
	std::string texId;
	ItemType itemType = ItemType::None;

public:
	Object(const std::string& name = "");
	virtual ~Object() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetItemType();
};