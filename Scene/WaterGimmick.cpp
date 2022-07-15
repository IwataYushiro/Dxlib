#include "WaterGimmick.h"
#include "DxLib.h"

WaterGimmick::~WaterGimmick()
{
	delete floor_;

}

//������
void WaterGimmick::Initialize()
{
	srand(time(NULL));

	floor_ = new Floor();
	floor_->Initialize();
	//����������
	InitWaterflow();
	//�A������
	InitBubble();
}

//����������
void WaterGimmick::InitWaterflow() {

	//�͈�
	this->waterFlowWidth = 200.0f;						//����
	this->waterFlowHeight = 10.0f;						//�c��
	//����������
	for (int i = 0; i < EMITTER_MAX; i++)
	{

		this->waterFlowTransform[i].x = WIN_WIDTH - waterFlowWidth;		//X���W
		this->waterFlowTransform[i].y = floor_->getFloorpos() - waterFlowHeight;			//Y���W
		this->waterFlowTransform[i].radius = 5;		//�����A�̔��a
		this->waterFlowSpeed[i] = 5;			//���x
		this->waterFlowBright[i] = 255;		//���邳
		this->isActiveWaterFlow[i] = false;		//�����Ă邩
	}
}

//�A������
void WaterGimmick::InitBubble()
{
	//�͈�
	this->bubbleWidth = 200.0f;														//����
	this->bubbleHeight = floor_->getFloorpos();						//�c��
	//�A������

	this->bubbleTransform.x = waterFlowWidth;		//X���W
	this->bubbleTransform.y = waterFlowHeight;			//Y���W
	this->bubbleTransform.radius = 32;		//�����A�̔��a
	this->bubbleSpeed = 5;			//���x
	this->isActiveBubble = false;		//�����Ă邩

	//�����̓����蔻��p
	this->bubbleHit.x = 0;
	this->bubbleHit.y = 0;
	this->bubbleHit.z = 0;

	//�A���o��^�C�~���O
	this->bubbleCount = 60.0f * 4.0f;
}





//�X�V
void WaterGimmick::Update(Transform player)
{
	//����
	UpdateWaterFlow();
	//�A�X�V
	UpdateBubble(player);
	
}

//�����X�V
void WaterGimmick::UpdateWaterFlow()
{
	for (int i = 0; i < EMITTER_MAX; i++)
	{

		if (isActiveWaterFlow[i] == false)
		{
			isActiveWaterFlow[i] = true;
			waterFlowTransform[i].x = WIN_WIDTH;
			waterFlowTransform[i].y = floor_->getFloorpos() - waterFlowHeight;
			if (i % 2 == 0)
			{
				break;
			}
		}
	}
	for (int i = 0; i < EMITTER_MAX; i++)
	{

		if (isActiveWaterFlow[i] == true)
		{
			waterFlowBright[i] -= 2;
			waterFlowTransform[i].x -= waterFlowSpeed[i];
			waterFlowTransform[i].y -= rand() % 5 - 2;
		}
		if (waterFlowBright[i] <= 0)
		{
			isActiveWaterFlow[i] = false;
			waterFlowBright[i] = 255;
		}
	}
}

//�A�X�V
void WaterGimmick::UpdateBubble(Transform player)
{
	if (isActiveBubble == false)
	{
		isActiveBubble = true;
		bubbleTransform.x = bubbleWidth;
		bubbleTransform.y = bubbleHeight;
	}

	if (isActiveBubble == true)
	{
		bubbleTransform.y -= bubbleSpeed;

	}
	if (bubbleTransform.y < 0.0f && bubbleCount < 0.0f||player)
	{
		bubbleTransform.x = bubbleWidth;
		bubbleTransform.y = bubbleHeight;
		isActiveBubble = false;
		bubbleCount = rand() % 150 + 50;
	}

	bubbleCount--;

}



//�`��
void WaterGimmick::Draw()
{
	//�����`��
	for (int i = 0; i < EMITTER_MAX; i++)
	{
		DrawWaterFlow(i);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�A�`��
	DrawBubble();
	DrawFormatString(0, 60, GetColor(255, 255, 255), "bubble::%f", bubbleCount);
}

//�����`��
void WaterGimmick::DrawWaterFlow(int num)
{
	if (isActiveWaterFlow[num] == true)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, waterFlowBright[num]);
		DrawCircle(waterFlowTransform[num].x, waterFlowTransform[num].y, waterFlowTransform[num].radius, GetColor(255, 255, 255), false);
	}

}

//�A�`��
void WaterGimmick::DrawBubble()
{
	if (isActiveBubble == true)
	{
		DrawCircle(bubbleTransform.x, bubbleTransform.y, bubbleTransform.radius, GetColor(255, 255, 255), false);
	}
	
}
