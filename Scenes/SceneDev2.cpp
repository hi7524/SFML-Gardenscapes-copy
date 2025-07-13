#include "stdafx.h"
#include "SceneDev2.h"
#include "Slot.h"
#include "Object.h"

sf::Vector2f originVec = { 0.f, 0.f };

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

	// 리소스
	texIds.push_back("graphics/slot.png");
	texIds.push_back("graphics/diamond.png");
	texIds.push_back("graphics/cookie.png");
	texIds.push_back("graphics/redstone.png");
	texIds.push_back("graphics/lava.png");
	texIds.push_back("graphics/potato.png");
	texIds.push_back("graphics/background.png");

	Scene::Init();
}

void SceneDev2::Enter()
{
	Scene::Enter();

	SpriteGo* background = new SpriteGo("graphics/background.png");
	background->Init();
	background->Reset();
	AddGameObject(background);
	
	CreateSlots(); // 초기 슬롯 생성
	CreateObjs(); // 초기 오브젝트 생성
}

void SceneDev2::Update(float dt)
{
	//DragObj();
	//SwapObjs(dt);
	MouseOnObj();

	// 두개 모두 선택한 경우
	if (selectedObj1 != nullptr && selectedObj2 != nullptr)
	{
		if (IsSwappable(selectedObj1, selectedObj2))
		{
			MoveObjPos(dt);
		}
		else
		{
			selectedObj1 = nullptr;
			selectedObj2 = nullptr;
		}
	}

	for (int i = 0; i < 7; i++)
	{
		int fallCount = 0;

		for (int j = 6; j >= 0; j--)
		{
			if (mapList[j][i] == 0)
				continue;

			if (objectArr[j][i] == nullptr || !objectArr[j][i]->GetActive())
			{
				fallCount++;
				continue;
			}

			if (objectArr[j][i]->GetIsMove())
			{
				int newRow = j + fallCount;
				sf::Vector2f targetPos = slots[newRow][i]->GetPosition();

				Move(dt, objectArr[j][i], targetPos, 10.f, MoveType::Lerp);

				if (Utils::Distance(objectArr[j][i]->GetPosition(), targetPos) <= 0.1f)
				{
					objectArr[j][i]->SetIndex({ newRow, i });
					objectArr[newRow][i] = objectArr[j][i];
					objectArr[j][i] = nullptr;
					objectArr[newRow][i]->SetIsMove(false);
				}
				continue;
			}
			else if (fallCount > 0)
			{
				int newRow = j + fallCount;
				sf::Vector2f targetPos = slots[newRow][i]->GetPosition();

				Move(dt, objectArr[j][i], targetPos, 10.f, MoveType::Lerp);
				objectArr[j][i]->SetIsMove(true);
			}
		}
	}
	CheckLineMatch();

	for (int i = 0; i < 7; i++)
	{
		for (int j = 6; j >= 0; j--)
		{
			
		}
	}

	Scene::Update(dt);
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
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
	if (Utils::Distance(targetPos, obj->GetPosition()) <= 0.5f)
	{
		obj->SetPosition(targetPos);
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

// 오브젝트 이동
void SceneDev2::MoveObjPos(float dt)
{
    if (selectedObj1Pos == vectorZero && selectedObj2Pos == vectorZero)
    {
        selectedObj1Pos = selectedObj1->GetPosition();
        selectedObj2Pos = selectedObj2->GetPosition();
    }

    // 이동
    sf::Vector2f nextPos1 = Utils::Lerp(selectedObj1->GetPosition(), selectedObj2Pos, dt * 9.f);
    sf::Vector2f nextPos2 = Utils::Lerp(selectedObj2->GetPosition(), selectedObj1Pos, dt * 9.f);

    selectedObj1->SetPosition(nextPos1);
    selectedObj2->SetPosition(nextPos2);

	// 근사치에 도달했을 경우 정보 변경
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

		// 오브젝트가 들어있는 배열의 값 교환
		std::swap(objectArr[index1.x][index1.y], objectArr[index2.x][index2.y]);

		// 초기화
        selectedObj1 = nullptr;
        selectedObj2 = nullptr;
        selectedObj1Pos = vectorZero;
        selectedObj2Pos = vectorZero;

		// 매치 여부 검사
		CheckLineMatch();
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
				Object* object = (Object*)AddGameObject(new Object());
				object->Init();
				object->Reset();
				object->SetActive(true);
				object->SetPosition(slots[i][j]->GetPosition());
				object->SetIndex(sf::Vector2i(i, j));
				objectArr[i][j] = object;
			}
		}
	}
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

						if (selectedObj1 != nullptr && selectedObj2 == nullptr)
						{
							selectedObj2 = objectArr[i][j];
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
	std::set<Object*> matchObjs;

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
					for (Object* obj : matchObjs)
					{
						if (obj)
						{
							obj->SetActive(false);
						}
					}
				}
				countRow = 0;
				matchObjs.clear();
				continue;
			}

			if (objectArr[i][j]->GetType() == objectArr[i][j + 1]->GetType())
			{
				countRow++;
				matchObjs.insert(objectArr[i][j]);
				matchObjs.insert(objectArr[i][j + 1]);
			}
			else
			{
				if (countRow >= 2)
				{
					for (Object* obj : matchObjs)
					{
						if (obj)
						{
							obj->SetActive(false);
						}
					}
				}
				countRow = 0;
				matchObjs.clear();
			}
		}

		if (countRow >= 2)
		{
			for (Object* obj : matchObjs)
			{
				if (obj)
				{
					obj->SetActive(false);
				}
			}
			matchObjs.clear();
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
					for (Object* obj : matchObjs)
					{
						if (obj)
						{
							obj->SetActive(false);
						}
					}
				}
				countCol = 0;
				matchObjs.clear();
				continue;
			}

			if (objectArr[i][j]->GetType() == objectArr[i + 1][j]->GetType())
			{
				countCol++;
				matchObjs.insert(objectArr[i][j]);
				matchObjs.insert(objectArr[i + 1][j]);
			}
			else
			{
				if (countCol >= 2)
				{
					for (Object* obj : matchObjs)
					{
						if (obj)
						{
							obj->SetActive(false);
						}
					}
				}
				countCol = 0;
				matchObjs.clear();
			}
		}

		if (countCol >= 2)
		{
			for (Object* obj : matchObjs)
			{
				if (obj)
				{
					obj->SetActive(false);
				}
			}
		}
	}
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

// 오브젝트 드래그
//void SceneDev2::DragObj()
//{
//	sf::Vector2f originalPos = { 0.f, 0.f };
//
//	for (int i = 0; i < 49; i++)
//	{
//		if (objectPool[i] != nullptr)
//		{
//			if ((objectPool[i]->GetGlobalBounds().left <= InputMgr::GetMousePosition().x && InputMgr::GetMousePosition().x <= objectPool[i]->GetGlobalBounds().left + objectPool[i]->GetGlobalBounds().width)
//				&& (objectPool[i]->GetGlobalBounds().top <= InputMgr::GetMousePosition().y && InputMgr::GetMousePosition().y <= objectPool[i]->GetGlobalBounds().top + objectPool[i]->GetGlobalBounds().height))
//			{
//
//				if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
//				{
//					selectedObj = objectPool[i];
//					originalPos = selectedObj->GetPosition();
//				}
//
//				if (InputMgr::GetMouseButtonUp(sf::Mouse::Left))
//				{
//					selectedObj = nullptr;
//				}
//
//				if ((InputMgr::GetMouseButton(sf::Mouse::Left) && selectedObj == objectPool[i]))
//				{
//
//					//if (originalPos )
//
//					objectPool[i]->SetPosition({ (float)InputMgr::GetMousePosition().x, objectPool[i]->GetPosition().y });
//				}
//			}
//		}
//	}
//}

// 변경
//void SceneDev2::SwapObjs(float dt)
//{
//	bool isMove = false;
//
//	if (originVec.x == 0.f && originVec.y == 0.f)
//	{
//		originVec = objectPool[1]->GetPosition();
//		std::cout << "저장함: " << std::to_string(originVec.x) << ", " << std::to_string(originVec.y) << std::endl;
//	}
//
//	//std::cout << std::to_string(originVec.x) << std::endl;
//	if (objectPool[1]->GetPosition().x >= originVec.x + 32 && objectPool[2]->GetPosition().x != objectPool[1]->GetPosition().x)
//	{
//		sf::Vector2f vec = objectPool[1]->GetPosition();
//		
//		objectPool[1]->SetPosition({ objectPool[1]->GetPosition().x + 1.f * 80 * dt, originVec.y });
//
//		if ((float)Utils::Distance(objectPool[1]->GetPosition(), objectPool[2]->GetPosition()) <= 1.f)
//		{
//			objectPool[1]->SetPosition(objectPool[2]->GetPosition());
//		}
//		//objectPool[1]->SetPosition(slots[2]->GetPosition());
//	}
//	
//	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left) && objectPool[1]->GetPosition().x <= originVec.x + 20)
//	{
//		objectPool[1]->SetPosition(originVec);
//	}
//}

// 2차원 배열 1차원 배열로 변경
int SceneDev2::To1D(int i, int j)
{
	return i * 7 + j;
}