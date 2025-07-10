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
	// ���� ���� �� ��ġ
	SlotSetting();

	object = (Object*)AddGameObject(new Object());
	object->SetPosition(slots[13]->GetPosition());
	//slots[17]->SetContainObj(true); // �� ��ġ�� ������ �ִٰ� �˸��� bool ���� ������ ��
	// �׸��� �ش� slot�� ��ȿ�� �������� �˻��ϰ� ������ ����

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

// ���� ����
void SceneDev2::SlotSetting()
{
	// ���ҽ� ����
	TEXTURE_MGR.Load("graphics/slot.png");

	// ���� ��ġ�� ���� ũ�� ���
	sf::Vector2u slotSize = TEXTURE_MGR.Get("graphics/slot.png").getSize();

	sf::Vector2f totalSize;
	totalSize.x = 7 * slotSize.x;
	totalSize.y = 7 * slotSize.y;

	// ȭ�� �߾� ��ġ
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