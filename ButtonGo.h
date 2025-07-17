#pragma once
#include "GameObject.h"

class ButtonGo : public GameObject
{
protected:
	sf::Sprite sprite;
	std::string spriteId = "graphics/button.png";
	std::string highlightedSpriteId = "graphics/buttonHighlighted.png";
	sf::Text text;

	std::function<void()> onClick;

public:
	ButtonGo(const std::string& name = "");
	virtual ~ButtonGo() = default;

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

	void SetText(std::string s);
	void OriginSprite();
	void HighlighteSprite();

	void SetOnClick(const std::function<void()>& callback);
	void OnClick();

	sf::FloatRect GetGlobalBounds() const override
	{
		return sprite.getGlobalBounds();
	}
};