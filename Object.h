#pragma once
#include "GameObject.h"

class Object : public GameObject
{
protected:
	sf::Sprite object;
	std::string texId = "graphics/diamond.png";
	ObjectType objectType = ObjectType::None;
	bool isActive = true;

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

	void SetRandomType();
	void SetType(ObjectType objType) { objectType = objType; }
	ObjectType GetItemType() const { return objectType; }
	void SetActive(bool active) { isActive = active; }
	bool GetActive() { return isActive; }

	sf::FloatRect GetGlobalBounds() const override
	{
		return object.getGlobalBounds();
	}
};