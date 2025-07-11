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
	// â ����
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(windowSize);
	worldView.setCenter(windowSize * 0.5f);

	// ���ҽ�
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
	// ���ҽ� ����
	TEXTURE_MGR.Load("graphics/slot.png");
	TEXTURE_MGR.Load("graphics/diamond.png");
	TEXTURE_MGR.Load("graphics/cookie.png");
	TEXTURE_MGR.Load("graphics/redstone.png");
	TEXTURE_MGR.Load("graphics/lava.png");
	TEXTURE_MGR.Load("graphics/potato.png");

	// ���� ���� �� ��ġ
	objectPool.resize(49);
	

	// ������Ʈ ����
	//for (int i = 0; i < 49; ++i)
	//{
	//	Object* object = (Object*)AddGameObject(new Object());
	//	object->Init();
	//	object->Reset();
	//	object->SetActive(true);
	//	objectPool[i] = object;
	//}

	SlotSetting();

	//object = (Object*)AddGameObject(new Object());
	//object->SetPosition(slots[To1D(2, 3)]->GetPosition());
	//slots[17]->SetContainObj(true); // �� ��ġ�� ������ �ִٰ� �˸��� bool ���� ������ ��
	// �׸��� �ش� slot�� ��ȿ�� �������� �˻��ϰ� ������ ����

	Scene::Enter();
}

void SceneDev2::Update(float dt)
{
	//::cout << InputMgr::GetMousePosition().x << ", " << InputMgr::GetMousePosition().y << std::endl;
	//std::cout << objectPool[1]->GetGlobalBounds().left << std::endl;
	//std::cout << objectPool[1]->GetGlobalBounds().left + objectPool[1]->GetGlobalBounds().width << std::endl;
	//std::cout << InputMgr::GetMousePosition().x << std::endl;

	
	for (int i = 0; i < 49; i++)
	{
		if (objectPool[i] != nullptr)
		{
			if ((objectPool[i]->GetGlobalBounds().left <= InputMgr::GetMousePosition().x && InputMgr::GetMousePosition().x <= objectPool[i]->GetGlobalBounds().left + objectPool[i]->GetGlobalBounds().width)
				&& (objectPool[i]->GetGlobalBounds().top <= InputMgr::GetMousePosition().y && InputMgr::GetMousePosition().y <= objectPool[i]->GetGlobalBounds().top + objectPool[i]->GetGlobalBounds().height))
			{

				if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
				{
					selectedObj = objectPool[i];
				}

				if (InputMgr::GetMouseButtonUp(sf::Mouse::Left))
				{
					selectedObj = nullptr;
				}

				if ((InputMgr::GetMouseButton(sf::Mouse::Left) && selectedObj == objectPool[i]))
				{
					objectPool[i]->SetPosition((sf::Vector2f)InputMgr::GetMousePosition());
				}
			}
		}
	}

	Scene::Update(dt);
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

// �ʱ� ���� ����
void SceneDev2::SlotSetting()
{
	// ���� ��ġ�� ���� ũ�� ���
	sf::Vector2u slotSize = TEXTURE_MGR.Get("graphics/slot.png").getSize();

	sf::Vector2f totalSize;
	totalSize.x = 7 * slotSize.x;
	totalSize.y = 7 * slotSize.y;

	// ȭ�� �߾� ��ġ
	sf::Vector2f startPos = FRAMEWORK.GetWindowSizeF() * 0.5f - (totalSize * 0.5f);

	// ���� ����
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (mapList[i][j])
			{
				slots[To1D(i, j)] = (Slot*)AddGameObject(new Slot());
				slots[To1D(i, j)]->SetPosition({ startPos.x + j * slotSize.x, startPos.y + i * slotSize.y });
			}
		}
	}

	// Object ����
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
				objectPool[To1D(i, j)] = object;

				objectPool[To1D(i, j)]->SetPosition(slots[To1D(i, j)]->GetPosition());
			}
			else
			{
				objectPool[To1D(i, j)] = nullptr;
			}
		}
		std::cout << std::endl;
	}

	//for (int i = 0; i < 7; i++)
	//{
	//	for (int j = 0; j < 7; j++)
	//	{
	//		if (slots[To1D(i, j)] != nullptr)
	//		{
	//			std::cout << slots[To1D(i, j)]->GetPosition().x << std::endl;
	//		}
	//	}
	//}
}

// 2���� �迭 1���� �迭�� ����
int SceneDev2::To1D(int i, int j)
{
	return i * 7 + j;
}

// ������Ʈ ���� �� ���
void SceneDev2::SpawnObject(sf::Vector2f spawnPos)
{
	int activeObjCount = 0;

	for (Object* obj : objectPool)
	{
		//// ��Ȱ��ȭ �Ǿ��ִ� ������Ʈ ���
		//if (!obj->GetActive())
		//{
		//	obj->Reset();
		//	obj->SetActive(true);
		//	obj->SetPosition(spawnPos);
		//	return;
		//}
		//else
		//{
		//	activeObjCount++;
		//}

		
	}

	// ������Ʈ ���� ��� ��Ұ� ������� �� ���� ����� ���
	if (activeObjCount == objectPool.size())
	{
		Object* obj;
		obj = (Object*)AddGameObject(new Object());
		obj->Init();
		obj->Reset();
		objectPool.push_back(obj);
		obj->SetPosition(spawnPos);
	}
}