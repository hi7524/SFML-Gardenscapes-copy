#pragma once
#include "SpriteGo.h"

class Slot : public GameObject
{
protected:
	sf::Sprite slotSprite;
	std::string texId = "graphics/slot.png";

	bool containsObject = false;

public:
	Slot(const std::string& name = "slot");
	~Slot() override = default;

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

	void SetContainObj(bool contain) { containsObject = contain; }
};