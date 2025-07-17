#pragma once

#define DEF_DEV

enum class SortingLayers
{
	Background,
	Foreground,
	Default,
	UI,
};

enum class Origins
{
	TL, TC, TR,	// 0 1 2
	ML, MC, MR,	// 3 4 5
	BL, BC, BR, // 6 7 8
	Custom
};

enum class SceneIds
{
	None = -1,
	Dev1,
	Dev2,
	Count,
};

enum class Sides
{
	Left,
	Right,
	None,
};

enum class ObjectType
{
	None = -1,
	Diamond, // 0
	Cookie,  // 1
	Redstone, // 2
	Lava, // 3
	Potato, // 4 
	Count
};

enum class MoveType
{
	Default,
	Lerp,
};

enum class GameState
{
	Idle, // 대기 (기본 상황)
	Swapping, // 변경 (이동, 변경 가능 여부 검사, 정보 변경까지 포함)
	CheckMatch, // 매치 체크 (한 번 호출)
	CheckObj,  // 매치된 오브젝트의 타입 검사 및 애니메이션 재생
	StartAnim, // clearEffect 재생 (한 번 호출)
	Animation, //  
	Moving,
};