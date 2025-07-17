#pragma once
#include "GameObject.h"
#include "SpriteGo.h"
#include "ButtonGo.h"

class UiCanvas : public GameObject
{
private:
	sf::Text swapCountText;
	sf::Text objCountText;
	SpriteGo diamondSprite;

	sf::Text stageClearText;

	// 일시정지
	sf::RectangleShape background;
	ButtonGo* btnBackToGame = new ButtonGo();
	ButtonGo* btnQuit = new ButtonGo();

	std::vector<ButtonGo*> buttons;

public:
	bool pauseUI = false;

	UiCanvas(const std::string& name = "");
	~UiCanvas() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetSwapCountText(int count);
	void SetObjCountText(int count);
	void ClickButton();
	sf::Vector2f GetTargetSprPos() const { return diamondSprite.GetPosition(); }
};