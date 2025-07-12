#pragma once
#include "Scene.h"

class Slot;
class Object;

class SceneDev2 : public Scene
{
protected:

	// 1�������� �� ���
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
	Object* object;

	//std::vector<Object*> objectPool = { nullptr };
	Object* objectGrid[7][7] = { nullptr };
	//Object* selectedObj = nullptr;
	//sf::Vector2f slotCenterPos[7][7];

	Object* selectedObj1 = nullptr; // ��ȯ�� �� ������Ʈ 1
	Object* selectedObj2 = nullptr; // ��ȯ�� �� ������Ʈ 1

public:
	SceneDev2();
	~SceneDev2() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void CreateSlots();
	int To1D(int i, int j);
	void CreateObjs();
	void SpawnObject(sf::Vector2f spawnPos);
	void MouseOnObj();
	//void DragObj();
	//void SwapObjs(float dt);
};