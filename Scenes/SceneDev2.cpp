#include "stdafx.h"
#include "SceneDev2.h"
#include "Slot.h"
#include "Object.h"
#include "UiCanvas.h"
#include "Animator.h"

SceneDev2::SceneDev2()
	: Scene(SceneIds::Dev2)
{
}

void SceneDev2::Init()
{
	// 창 설정
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(windowSize);
	worldView.setCenter(windowSize * 0.5f);
	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	// 리소스
	texIds.push_back("graphics/slot.png");
	texIds.push_back("graphics/diamond.png");
	texIds.push_back("graphics/cookie.png");
	texIds.push_back("graphics/redstone.png");
	texIds.push_back("graphics/lava.png");
	texIds.push_back("graphics/potato.png");
	texIds.push_back("graphics/background.png");
	texIds.push_back("graphics/sign.png");
	texIds.push_back("graphics/effects.png");
	texIds.push_back("graphics/button.png");
	texIds.push_back("graphics/buttonHighlighted.png");

	fontIds.push_back("fonts/minecraft_font.ttf");

	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; ++j)
		{
			slots[i][j] = nullptr;
			objectArr[i][j] = nullptr;
		}
	}
	matchObjs.clear();

	Scene::Init();
}

void SceneDev2::Enter()
{
	Scene::Enter();

	ANI_CLIP_MGR.Load("animations/effect.csv");

	SpriteGo* background = new SpriteGo("graphics/background.png");
	background->Init();
	background->Reset();
	AddGameObject(background);

	SpriteGo* sign = new SpriteGo("graphics/sign.png");
	sign->Init();
	sign->Reset();
	sign->SetPosition({ 100.f, 360.f });
	sign->SetOrigin(Origins::MC);
	AddGameObject(sign);

	canvas = (UiCanvas*)AddGameObject(new UiCanvas());
	canvas->Init();
	canvas->Reset();
	canvas->pauseUI = false;

	CreateSlots(); // 초기 슬롯 생성
	CreateObjs(); // 초기 오브젝트 생성
}

void SceneDev2::Update(float dt)
{
	// 대기 및 입력
	if (state == GameState::Idle)
	{
		UpdateIdle();
	}
	else if (state == GameState::Swapping)
	{
		UpdateSwapping(dt);
	}
	else if (state == GameState::CheckMatch)
	{
		UpdateCheckingMatch(dt);
	}
	else if (state == GameState::CheckObj)
	{
		Test(dt);
	}
	else if (state == GameState::Animation)
	{
		UpdateAnimating();
	}
	else if (state == GameState::Moving)
	{
		UpdateMoving(dt);
	}
	else if (state == GameState::End)
	{
		
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		canvas->pauseUI = !canvas->pauseUI;
		FRAMEWORK.GetTimeScale() ? FRAMEWORK.SetTimeScale(0) : FRAMEWORK.SetTimeScale(1);
	}

	Scene::Update(dt);
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneDev2::UpdateIdle()
{
	if (!isMovingObjs)
	{
		MouseOnObj();
		DragObj();
	}

	// 두개 모두 선택한 경우
	if (selectedObj1 != nullptr && selectedObj2 != nullptr)
	{
		if (IsSwappable(selectedObj1, selectedObj2))
		{
			state = GameState::Swapping;
		}
		else
		{
			selectedObj1 = nullptr;
			selectedObj2 = nullptr;
		}
	}
}

void SceneDev2::UpdateSwapping(float dt)
{
	SwapObjs(dt);
}

void SceneDev2::UpdateCheckingMatch(float dt)
{
	CheckLineMatch();
	state = GameState::CheckObj;
}

void SceneDev2::Test(float dt)
{
	bool isAllDiaObjMoved = true;

	for (auto obj : matchObjs)
	{
		if (obj->GetType() == ObjectType::Diamond)
		{
			sf::Vector2f targetPos = canvas->GetTargetSprPos();
			Move(dt, obj, targetPos, 800.f, MoveType::Default);

			if (Utils::Distance(obj->GetPosition(), targetPos) > 0.5f)
			{
				isAllDiaObjMoved = false;
			}
		}
	}

	if (isAllDiaObjMoved)
	{
		StartAnim();
	}
}

void SceneDev2::StartAnim()
{
	for (auto obj : matchObjs)
	{
		if (obj->GetType() != ObjectType::Diamond && obj != nullptr)
		{
			obj->PlayClearEffect();
		}
	}

	state = GameState::Animation;
}

void SceneDev2::UpdateAnimating()
{
	if (matchObjs.empty())
	{
		CheckLineMatch();
	}

	if (matchObjs.empty())
	{
		state = GameState::Idle;
		return;
	}

	bool animAllStop = true;
	for (auto obj : matchObjs)
	{
		if (obj->IsPlaying())
		{
			animAllStop = false;
			break;
		}
	}

	if (animAllStop)
	{
		DeleteMatchObjs();
		state = GameState::Moving;
	}
}

void SceneDev2::UpdateMoving(float dt)
{
	MoveDown(dt);

	// 대각선 이동
	if (objectArr[0][1] != nullptr
		&& Utils::Distance(objectArr[0][1]->GetPosition(), slots[0][1]->GetPosition()) < 0.5f
		&& objectArr[1][0] == nullptr)
	{
		ChangeObj(objectArr[0][1], 1, 0);

		sf::Vector2f targetPos = slots[1][0]->GetPosition();
		Move(dt, objectArr[1][0], targetPos, 10.f, MoveType::Lerp);
	}

	if (objectArr[0][5] != nullptr
		&& Utils::Distance(objectArr[0][5]->GetPosition(), slots[0][5]->GetPosition()) < 0.5f
		&& objectArr[1][6] == nullptr)
	{
		ChangeObj(objectArr[0][5], 1, 6);

		sf::Vector2f targetPos = slots[1][6]->GetPosition();
		Move(dt, objectArr[1][6], targetPos, 10.f, MoveType::Lerp);
	}

	for (int i = 0; i < 7; i++)
	{
		if (mapList[0][i] == 0 || slots[0][i] == nullptr)
			continue;

		if (objectArr[0][i] != nullptr)
		{
			if (objectArr[0][i]->GetIsMove())
				continue;
		}

		if (slots[0][i] != nullptr && objectArr[0][i] == nullptr)
		{
			Object* object = (Object*)AddGameObject(new Object());
			object->Init();
			object->Reset();
			object->SetActive(true);
			object->SetPosition({ slots[0][i]->GetPosition().x, slots[0][i]->GetPosition().y - 64 });
			object->SetIndex(sf::Vector2i(0, i));
			objectArr[0][i] = object;
			isSpawning = true;
		}
	}

	if (isSpawning)
	{
		bool allReached = true;

		for (int i = 0; i < 7; i++)
		{
			if (objectArr[0][i] == nullptr)
				continue;

			sf::Vector2f targetPos = slots[objectArr[0][i]->GetIndex().x][objectArr[0][i]->GetIndex().y]->GetPosition();
			if (Utils::Distance(objectArr[0][i]->GetPosition(), targetPos) >= 0.5f)
			{
				Move(dt, objectArr[0][i], targetPos, 15.f, MoveType::Default);
				allReached = false;
			}
			else
			{
				objectArr[0][i]->SetPosition(targetPos);
				objectArr[0][i]->SetIsMove(false);
			}
		}

		if (allReached)
		{
			isSpawning = false;
		}
	}

	if (IsAllObjectsStopped())
	{
		frameCount++;
	}
	else
	{
		frameCount = 0;
	}

	if (frameCount >= 3)
	{
		state = GameState::CheckMatch;
	}
}

// 두 오브젝트 스왑 조건 확인
bool SceneDev2::IsSwappable(const Object* a, const Object* b)
{
	if (a == nullptr || b == nullptr)
	{
		return false;
	}

	int dx = std::abs(a->GetIndex().x - b->GetIndex().x);
	int dy = std::abs(a->GetIndex().y - b->GetIndex().y);

	return dx + dy == 1;
}

void SceneDev2::Move(float dt, Object* obj, sf::Vector2f targetPos, float speed, MoveType moveType)
{
	obj->SetIsMove(true);

	if (Utils::Distance(targetPos, obj->GetPosition()) <= 0.5f)
	{
		obj->SetPosition(targetPos);
		obj->SetIsMove(false);
		return;
	}

	sf::Vector2f dir = Utils::GetNormal(targetPos - obj->GetPosition());
	sf::Vector2f pos;

	if (moveType == MoveType::Default)
	{
		pos = obj->GetPosition() + dir * speed * dt;
	}
	else if (moveType == MoveType::Lerp)
	{
		pos = Utils::Lerp(obj->GetPosition(), targetPos, dt * speed);
	}

	obj->SetPosition(pos);
}

// 아래가 비어있는지 체크 후 아래로 내려가도록 함
void SceneDev2::MoveDown(float dt)
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 6; j >= 0; j--)
		{
			if (mapList[j][i] == 0)
				continue;

			if (objectArr[j][i] == nullptr || !objectArr[j][i]->GetActive())
				continue;

			if (objectArr[j][i]->GetIsMove())
			{
				sf::Vector2i idx = objectArr[j][i]->GetIndex();
				sf::Vector2f targetPos = slots[idx.x][idx.y]->GetPosition();
				Move(dt, objectArr[j][i], targetPos, objectMoveSpeed, MoveType::Default);

				if (Utils::Distance(objectArr[j][i]->GetPosition(), targetPos) <= 0.1f)
				{
					objectArr[j][i]->SetPosition(targetPos);
					objectArr[j][i]->SetIsMove(false);
				}
				continue;
			}

			// 바로 아래 칸 체크
			int belowRow = j + 1;
			if (belowRow < 7 && mapList[belowRow][i] != 0 && objectArr[belowRow][i] == nullptr)
			{
				ChangeObj(objectArr[j][i], belowRow, i);
				objectArr[belowRow][i]->SetIsMove(true);
			}
		}
	}
}

void SceneDev2::clearClickedInfo()
{
	// 초기화
	selectedObj1 = nullptr;
	selectedObj2 = nullptr;
	selectedObj1Pos = vectorZero;
	selectedObj2Pos = vectorZero;
	isSwapped = false;
	isReverting = false;

	state = GameState::CheckMatch;
}

// 오브젝트 스왑
void SceneDev2::SwapObjs(float dt)
{
	if (swapCount <= 0 || selectedObj1 == nullptr || selectedObj2 == nullptr)
		return;

	if (selectedObj1Pos == vectorZero && selectedObj2Pos == vectorZero)
	{
		selectedObj1Pos = selectedObj1->GetPosition();
		selectedObj2Pos = selectedObj2->GetPosition();
	}

	// 스왑 완료 전
	if (!isSwapped)
	{
		sf::Vector2f nextPos1 = Utils::Lerp(selectedObj1->GetPosition(), selectedObj2Pos, dt * 14.f);
		sf::Vector2f nextPos2 = Utils::Lerp(selectedObj2->GetPosition(), selectedObj1Pos, dt * 14.f);

		selectedObj1->SetPosition(nextPos1);
		selectedObj2->SetPosition(nextPos2);

		if (Utils::Distance(nextPos1, selectedObj2Pos) <= 0.5f && Utils::Distance(nextPos2, selectedObj1Pos) <= 0.5f)
		{
			// 위치 설정
			selectedObj1->SetPosition(selectedObj2Pos);
			selectedObj2->SetPosition(selectedObj1Pos);

			// 오브젝트 내부의 인덱스 설정
			sf::Vector2i index1 = selectedObj1->GetIndex();
			sf::Vector2i index2 = selectedObj2->GetIndex();
			selectedObj1->SetIndex(index2);
			selectedObj2->SetIndex(index1);
			std::swap(objectArr[index1.x][index1.y], objectArr[index2.x][index2.y]);

			// 매치 체크
			CheckLineMatch();
			isSwapped = true;

			// 매치가 없으면 복구
			if (matchObjs.size() > 0)
			{
				clearClickedInfo();
				swapCount--;
				canvas->SetSwapCountText(swapCount);
			}
			else
			{
				isReverting = true;
			}
		}
	}
	// 복구
	else if (isReverting)
	{
		sf::Vector2f nextPos1 = Utils::Lerp(selectedObj1->GetPosition(), selectedObj1Pos, dt * 14.f);
		sf::Vector2f nextPos2 = Utils::Lerp(selectedObj2->GetPosition(), selectedObj2Pos, dt * 14.f);

		selectedObj1->SetPosition(nextPos1);
		selectedObj2->SetPosition(nextPos2);

		if (Utils::Distance(nextPos1, selectedObj1Pos) <= 0.5f && Utils::Distance(nextPos2, selectedObj2Pos) <= 0.5f)
		{
			selectedObj1->SetPosition(selectedObj1Pos);
			selectedObj2->SetPosition(selectedObj2Pos);

			sf::Vector2i index1 = selectedObj1->GetIndex();
			sf::Vector2i index2 = selectedObj2->GetIndex();
			selectedObj1->SetIndex(index2);
			selectedObj2->SetIndex(index1);
			std::swap(objectArr[index1.x][index1.y], objectArr[index2.x][index2.y]);

			clearClickedInfo();
		}
	}
}

// 초기 슬롯 생성
void SceneDev2::CreateSlots()
{
	// 슬롯 배치를 위한 크기 계산
	sf::Vector2u slotSize = TEXTURE_MGR.Get("graphics/slot.png").getSize();

	sf::Vector2f totalSize;
	totalSize.x = 7 * slotSize.x;
	totalSize.y = 7 * slotSize.y;

	// 화면 중앙 위치
	sf::Vector2f startPos = FRAMEWORK.GetWindowSizeF() * 0.5f - (totalSize * 0.5f);

	// 슬롯 생성
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (mapList[i][j])
			{
				slots[i][j] = (Slot*)AddGameObject(new Slot());
				slots[i][j]->Init();
				slots[i][j]->Reset();
				slots[i][j]->SetPosition({ startPos.x + j * slotSize.x, startPos.y + i * slotSize.y });
			}
		}
	}
}

// 오브젝트 생성
void SceneDev2::CreateObjs()
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (mapList[i][j])
			{
				SpawnObj(i, j);

				if (j > 1 && objectArr[i][j - 1] != nullptr)
				{
					while (objectArr[i][j - 1]->GetType() == objectArr[i][j]->GetType())
					{
						objectArr[i][j]->Reset();
					}
				}

				if (i > 1 && objectArr[i - 1][j] != nullptr)
				{
					while (objectArr[i - 1][j]->GetType() == objectArr[i][j]->GetType())
					{
						objectArr[i][j]->Reset();
					}
				}
			}
		}
	}
}

// 오브젝트 정보 변경 (obj[i][j] to obj[x][y])
void SceneDev2::ChangeObj(Object* obj, int x, int y)
{
	// 오브젝트가 들어있는 배열의 값 교환
	sf::Vector2i index = obj->GetIndex();

	if (index.x == x && index.y == y)
		return;

	objectArr[x][y] = objectArr[index.x][index.y];

	// 오브젝트 내부의 인덱스 변경
	obj->SetIndex(sf::Vector2i(x, y));

	// 기존 오브젝트 정보 제거
	objectArr[index.x][index.y] = nullptr;
}

// 오브젝트 1개 생성
void SceneDev2::SpawnObj(int idx1, int idx2)
{
	Object* object = (Object*)AddGameObject(new Object());
	object->Init();
	object->Reset();
	object->SetActive(true);
	object->SetPosition(slots[idx1][idx2]->GetPosition());
	// 정보 수정
	object->SetIndex(sf::Vector2i(idx1, idx2));
	objectArr[idx1][idx2] = object;
}

// 오브젝트 선택
void SceneDev2::MouseOnObj()
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (objectArr[i][j] != nullptr)
			{
				if ((objectArr[i][j]->GetGlobalBounds().left <= InputMgr::GetMousePosition().x && InputMgr::GetMousePosition().x <= objectArr[i][j]->GetGlobalBounds().left + objectArr[i][j]->GetGlobalBounds().width)
					&& (objectArr[i][j]->GetGlobalBounds().top <= InputMgr::GetMousePosition().y && InputMgr::GetMousePosition().y <= objectArr[i][j]->GetGlobalBounds().top + objectArr[i][j]->GetGlobalBounds().height))
				{
					if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
					{
						if (selectedObj1 == nullptr)
						{
							selectedObj1 = objectArr[i][j];
							return;
						}
					}
				}
			}
		}
	}
}

// 라인 매치 검사
void SceneDev2::CheckLineMatch()
{
	// 행 검사
	for (int i = 0; i < 7; i++)
	{
		int countRow = 0;

		for (int j = 0; j < 6; j++)
		{
			if (objectArr[i][j] == nullptr || objectArr[i][j + 1] == nullptr)
			{
				if (countRow >= 2)
				{
					int matchStart = j - countRow;
					for (int k = matchStart; k <= j; k++)
					{
						if (objectArr[i][k] != nullptr)
						{
							matchObjs.insert(objectArr[i][k]);
						}
					}
				}
				countRow = 0;
				continue;
			}

			if (objectArr[i][j]->GetType() == objectArr[i][j + 1]->GetType())
			{
				countRow++;
			}
			else
			{
				if (countRow >= 2)
				{
					int matchStart = j - countRow;
					for (int k = matchStart; k <= j; k++)
					{
						if (objectArr[i][k] != nullptr)
						{
							matchObjs.insert(objectArr[i][k]);
						}
					}
				}
				countRow = 0;
			}
		}

		if (countRow >= 2)
		{
			int matchStart = 6 - countRow;
			for (int k = matchStart; k <= 6; k++)
			{
				if (objectArr[i][k] != nullptr)
					matchObjs.insert(objectArr[i][k]);
			}
		}
	}

	// 열 검사
	for (int j = 0; j < 7; j++)
	{
		int countCol = 0;

		for (int i = 0; i < 6; i++)
		{
			if (objectArr[i][j] == nullptr || objectArr[i + 1][j] == nullptr)
			{
				if (countCol >= 2)
				{
					int matchStart = i - countCol;
					for (int k = matchStart; k <= i; k++)
					{
						if (objectArr[k][j] != nullptr)
						{
							matchObjs.insert(objectArr[k][j]);
						}
					}
				}
				countCol = 0;
				continue;
			}

			if (objectArr[i][j]->GetType() == objectArr[i + 1][j]->GetType())
			{
				countCol++;
			}
			else
			{
				if (countCol >= 2)
				{
					int matchStart = i - countCol;
					for (int k = matchStart; k <= i; k++)
					{
						if (objectArr[k][j] != nullptr)
						{
							matchObjs.insert(objectArr[k][j]);
						}
					}
				}
				countCol = 0;
			}
		}

		if (countCol >= 2)
		{
			int matchStart = 6 - countCol;
			for (int k = matchStart; k <= 6; k++)
			{
				if (objectArr[k][j] != nullptr)
					matchObjs.insert(objectArr[k][j]);
			}
		}
	}
}

// 매치된 오브젝트 삭제
void SceneDev2::DeleteMatchObjs()
{
	// 매치된 요소 존재하지 않을 경우 건너 뛰기
	if (matchObjs.size() <= 0)
	{
		return;
	}

	for (auto obj : matchObjs)
	{
		if (obj->GetType() == ObjectType::Diamond)
		{
			remainingTargetCount--;
			if (remainingTargetCount < 0)
			{
				remainingTargetCount = 0;
				canvas->stageClearUI = true;
				state == GameState::End;
			}
			canvas->SetObjCountText(remainingTargetCount);
		}

		if (obj != nullptr)
		{
			obj->SetActive(false);
			sf::Vector2i index = obj->GetIndex();
			objectArr[index.x][index.y] = nullptr;
		}
	}

	matchObjs.clear();
}

// 아래 슬롯이 비어있는지 여부 확인
bool SceneDev2::IsEmptyBelow(int c, int r)
{
	if (objectArr[c][r])
	{
		// 마지막이므로 아래에 더이상 내려갈 수 없음
		if (c == 6)
		{
			return false;
		}

		if (objectArr[c + 1][r] == nullptr)
		{
			return true;
		}

		if (!objectArr[c + 1][r]->GetActive())
		{
			return true;
		}

		return false;
	}
	return false;
}

bool SceneDev2::IsAllObjectsStopped()
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (objectArr[i][j] != nullptr && objectArr[i][j]->GetIsMove())
				return false;
		}
	}
	return true;
}

// 오브젝트 드래그
void SceneDev2::DragObj()
{
	// selectedObj1이 정해진 경우
	if (selectedObj1 != nullptr)
	{
		sf::Vector2f curObjPos = selectedObj1->GetPosition();
		sf::Vector2i obj1Index = selectedObj1->GetIndex();

		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			dragStartPos = (sf::Vector2f)InputMgr::GetMousePosition();
		}

		if (InputMgr::GetMouseButtonUp(sf::Mouse::Left))
		{
			sf::Vector2f curMousePos = (sf::Vector2f)InputMgr::GetMousePosition();
			sf::Vector2f dragVec = curMousePos - dragStartPos;

			if (Utils::Magnitude(dragVec) > 15.f)
			{
				// 더 큰 방향이 축
				if (std::abs(dragVec.x) < std::abs(dragVec.y))
				{
					if (dragVec.y < 0 && obj1Index.x > 0)
					{
						selectedObj2 = objectArr[obj1Index.x - 1][obj1Index.y]; // 상
					}
					else if (dragVec.y > 0 && obj1Index.x < 6)
					{
						selectedObj2 = objectArr[obj1Index.x + 1][obj1Index.y]; // 하
					}
				}
				else
				{
					if (dragVec.x < 0 && obj1Index.y > 0)
					{
						selectedObj2 = objectArr[obj1Index.x][obj1Index.y - 1]; // 좌
					}
					else if (dragVec.x > 0 && obj1Index.y < 6)
					{
						selectedObj2 = objectArr[obj1Index.x][obj1Index.y + 1]; // 우
					}
				}
			}
		}

		if (InputMgr::GetMouseButtonUp(sf::Mouse::Left) && selectedObj2 == nullptr)
		{
			selectedObj1 = nullptr;
		}
	}
}

void SceneDev2::Exit()
{
	Scene::Exit();

	for (auto obj : gameObjects)
	{
		obj->Release();
		delete obj;
	}
	gameObjects.clear();

	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; ++j)
		{
			slots[i][j] = nullptr;
			objectArr[i][j] = nullptr;
		}
	}

	matchObjs.clear();
	selectedObj1 = nullptr;
	selectedObj2 = nullptr;
	selectedObj1Pos = vectorZero;
	selectedObj2Pos = vectorZero;
	isSwapped = false;
	isReverting = false;
	isMovingObjs = false;
	isSpawning = false;
	frameCount = 0;
	swapCount = 22;
	remainingTargetCount = 16;
	state = GameState::Idle;
}