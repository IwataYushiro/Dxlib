#include "Floor.h"
#include "Global.h"

#include <DxLib.h>

Floor::~Floor()
{
}

//èâä˙âª
void Floor::Initialize()
{
	this->marioFloorPos = WIN_HEIGHT - 100.0f;

	this->sonicFloorPos = WIN_HEIGHT - 200.0f;
}
//è∞Çï`âÊ
void Floor::DrawMarioFloor()
{
	//è∞Çï`âÊ
	DrawBox(0, marioFloorPos, 400, WIN_HEIGHT, GetColor(31, 30, 51), true);

	DrawBox(800, marioFloorPos, WIN_WIDTH, WIN_HEIGHT, GetColor(31, 30, 51), true);
}

void Floor::DrawSonicFloor()
{
	DrawBox(0, sonicFloorPos, WIN_WIDTH, WIN_HEIGHT, GetColor(0, 8, 22), true);
}