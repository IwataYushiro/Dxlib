#include "Floor.h"
#include "Global.h"

#include <DxLib.h>

Floor::~Floor()
{
}

//������
void Floor::Initialize()
{
	this->floorPos = WIN_HEIGHT - 100.0f;
}
//����`��
void Floor::DrawFloor()
{
	//����`��
	DrawBox(0, floorPos, WIN_WIDTH, WIN_HEIGHT, GetColor(31, 30, 51), true);
}