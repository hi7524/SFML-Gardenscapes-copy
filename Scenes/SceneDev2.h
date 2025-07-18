#pragma once
#include "Scene.h"

class Slot;
class Object;
class UiCanvas;

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
	sf::Vector2f zeroVector = { 0.f, 0.f };

	bool hasSwapped = false;
	bool isRevertingSwap = false;

	int swapCount = 3;
	int remainingTargetCount = 16;

	bool isMovingObjs = false; // 오브젝트 움직이고 있는중인지 저장할 bool변수
	bool isSpawning = false;

	float objectMoveSpeed = 550.f;

	GameState state = GameState::Idle;

	int frameCount = 0;

	sf::Vector2f dragStartPos = { 0.f, 0.f };

	UiCanvas* canvas;

public:
	SceneDev2();
	~SceneDev2() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void Exit() override;

	void UpdateIdle();
	void UpdateSwapping(float dt);
	void UpdateMatchedDiamonds(float dt);
	void PlayClearEffects();
	void UpdateCheckingMatch(float dt);
	void UpdateAnimating();
	void UpdateMoving(float dt);

	bool IsSwappable(const Object* a, const Object* b);
	void Move(float dt, Object* obj, sf::Vector2f targetPos, float speed, MoveType moveType);
	void MoveDown(float dt);
	void ResetSelectedObjects();
	void ProcessSwapping(float dt);
	void CreateSlots();
	void CreateObjs();
	void ChangeObj(Object* obj, int x, int y);
	void SpawnObj(int idx1, int idx2);
	void MouseOnObj();
	void CheckLineMatch();
	void DeleteMatchObjs();
	bool IsAllObjectsStopped();
	void DragObj();
};