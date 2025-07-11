#pragma once
#include "Scene.h"

class Slot;
class Object;

class SceneDev2 : public Scene
{
protected:

	// 1스테이지 맵 모양
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

	std::vector<Object*> objectPool;

	Object* selectedObj = nullptr;
	//sf::Vector2f slotCenterPos[7][7];

public:
	SceneDev2();
	~SceneDev2() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SlotSetting();
	int To1D(int i, int j);
	void SpawnObject(sf::Vector2f spawnPos);
};