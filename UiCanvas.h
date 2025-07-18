#pragma once
#include "GameObject.h"
#include "SpriteGo.h"
#include "ButtonGo.h"

class UiCanvas : public GameObject
{
private:
	sf::Text stageText;
	sf::Text objCountText;
	sf::Text swapCountText;
	SpriteGo diamondSprite;

	// 일시정지
	sf::RectangleShape background;
	ButtonGo* btnBackToGame = new ButtonGo();
	ButtonGo* btnQuitToTitle = new ButtonGo();

	// 스테이지 클리어
	sf::Text stageClearText;
	float size = 1;
	ButtonGo* btnBackToTitle2 = new ButtonGo();

	std::vector<ButtonGo*> buttons;

public:
	bool pauseUI = false;
	bool stageClearUI = false;

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