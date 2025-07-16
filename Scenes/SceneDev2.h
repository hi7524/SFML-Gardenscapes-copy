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
	Object* objectArr[7][7] = { nullptr };
	std::set<Object*> matchObjs; // 매치된 오브젝트가 담길 배열

	Object* selectedObj1 = nullptr; // 교환할 두 오브젝트 1
	Object* selectedObj2 = nullptr; // 교환할 두 오브젝트 1

	sf::Vector2f selectedObj1Pos = { 0.f, 0.f };
	sf::Vector2f selectedObj2Pos = { 0.f, 0.f };
	sf::Vector2f vectorZero = { 0.f, 0.f };

	bool isSwapped = false;
	bool isReverting = false;

	int swapCount = 22;
	TextGo* swapCountTxt = new TextGo("fonts/minecraft_font.ttf"); // 나중에 canvas 추가하면 거기로 옮기기

	bool isMovingObjs = false; // 오브젝트 움직이고 있는중인지 저장할 bool변수
	bool isSpawning = false;

	float objectMoveSpeed = 350.f;

	GameState state = GameState::Idle;

	int frameCount = 0;

public:
	SceneDev2();
	~SceneDev2() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	bool IsSwappable(const Object* a, const Object* b);
	void Move(float dt, Object* obj, sf::Vector2f targetPos, float speed, MoveType moveType);
	//bool Test(const Object* obj);
	void MoveDown(float dt);
	void TryToSwap(float dt);
	void clearClickedInfo();
	void SwapObjs(float dt);
	void CreateSlots();
	int To1D(int i, int j);
	void CreateObjs();
	void ChangeObj(Object* obj, int x, int y);
	void SpawnObj(int idx1, int idx2);
	//void SpawnObject(sf::Vector2f spawnPos);
	void MouseOnObj();
	void CheckLineMatch();
	void DeleteMatchObjs();
	bool IsEmptyBelow(int c, int r);
	bool IsAllObjectsStopped();
	//void DragObj();
	//void SwapObjs(float dt);
};