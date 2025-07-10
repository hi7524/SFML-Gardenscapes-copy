#include "stdafx.h"
#include "SceneDev2.h"
#include "Slot.h"
#include "Object.h"

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

	Scene::Init();
}

void SceneDev2::Enter()
{
	// 슬롯 생성 및 배치
	SlotSetting();

	object = (Object*)AddGameObject(new Object());
	object->SetPosition(slots[13]->GetPosition());
	//slots[17]->SetContainObj(true); // 그 위치에 아이템 있다고 알리는 bool 변수 세팅할 것
	// 그리고 해당 slot이 유효한 슬롯인지 검사하고 아이템 놓기

	Scene::Enter();
}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);
}

void SceneDev2::Draw(sf::RenderWindow& window)
{

	Scene::Draw(window);
}

// 슬롯 생성
void SceneDev2::SlotSetting()
{
	// 리소스 설정
	TEXTURE_MGR.Load("graphics/slot.png");

	// 슬롯 배치를 위한 크기 계산
	sf::Vector2u slotSize = TEXTURE_MGR.Get("graphics/slot.png").getSize();

	sf::Vector2f totalSize;
	totalSize.x = 7 * slotSize.x;
	totalSize.y = 7 * slotSize.y;

	// 화면 중앙 위치
	sf::Vector2f startPos = FRAMEWORK.GetWindowSizeF() * 0.5f - (totalSize * 0.5f);

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (mapList[i][j])
			{
				slots[i * 7 + j] = (Slot*)AddGameObject(new Slot());
				slots[i * 7 + j]->SetPosition({ startPos.x + j * slotSize.x, startPos.y + i * slotSize.y });
				slotCenterPos[i][j] = { startPos.x + j * slotSize.x, startPos.y + i * slotSize.y };
			}
			else
			{
				slotCenterPos[i][j] = { 0.f, 0.f };
			}
		}
	}
}