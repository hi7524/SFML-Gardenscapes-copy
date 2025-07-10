#pragma once
#include "Scene.h"

class Slot;
class Object;

class SceneDev2 : public Scene
{
protected:

	// 1스테이지 맵 모양 (이 모양에 맞추어 슬롯이 그려짐)
	int mapList[7][7] =
	{
		{0, 1, 1, 1, 1, 1, 0},
		{1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1},
		{0, 1, 1, 1, 1, 1, 0},
	};

	Slot* slots[49];
	Object* object;


	sf::Vector2f slotCenterPos[7][7];

public:
	SceneDev2();
	~SceneDev2() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SlotSetting();
};