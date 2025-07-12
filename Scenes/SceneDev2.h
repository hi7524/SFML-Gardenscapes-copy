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

	Slot* slots[7][7] = {nullptr};
	Object* objectGrid[7][7] = { nullptr };

	Object* selectedObj1 = nullptr; // 교환할 두 오브젝트 1
	Object* selectedObj2 = nullptr; // 교환할 두 오브젝트 1

	sf::Vector2f selectedObj1Pos = { 0.f, 0.f };
	sf::Vector2f selectedObj2Pos = { 0.f, 0.f };
	sf::Vector2f vectorZero = { 0.f, 0.f };

public:
	SceneDev2();
	~SceneDev2() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	bool IsSwappable(const Object* a, const Object* b);
	void MoveObjPos(float dt);
	void CreateSlots();
	int To1D(int i, int j);
	void CreateObjs();
	void SpawnObject(sf::Vector2f spawnPos);
	void MouseOnObj();
	void CheckLineMatch();
	//void DragObj();
	//void SwapObjs(float dt);
};