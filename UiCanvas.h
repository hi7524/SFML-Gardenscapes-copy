#pragma once
#include "GameObject.h"

class UiCanvas : public GameObject
{
private:
	sf::Text swapCountText;

public:
	UiCanvas(const std::string& name = "");
	~UiCanvas() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetSwapCountTxt(int count);
};