#pragma once
#include "GameObject.h"
#include "SpriteGo.h"

class UiCanvas : public GameObject
{
private:
	sf::Text swapCountText;
	sf::Text objCountText;
	SpriteGo diamondSprite;

public:
	UiCanvas(const std::string& name = "");
	~UiCanvas() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetSwapCountText(int count);
	void SetObjCountText(int count);
};