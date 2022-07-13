#include "Floor.h"
#include "Global.h"

#include <DxLib.h>

Floor::~Floor()
{
}

//èâä˙âª
void Floor::Initialize()
{
	this->floorPos = WIN_HEIGHT - 100.0f;
}
//è∞Çï`âÊ
void Floor::DrawFloor()
{
	//è∞Çï`âÊ
	DrawBox(0, floorPos, WIN_WIDTH, WIN_HEIGHT, GetColor(31, 30, 51), true);
}