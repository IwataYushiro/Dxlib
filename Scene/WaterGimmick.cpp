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
		this->waterFlowTransform[i].y = floor_->getMarioFloorpos() - waterFlowHeight;			//Y���W
		this->waterFlowTransform[i].radius = 5.0f;		//�����A�̔��a
		this->waterFlowSpeed[i] = 5.0f;			//���x
		this->waterFlowBright[i] = 255;		//���邳
		this->isActiveWaterFlow[i] = false;		//�����Ă邩
	}
}

//�A������
void WaterGimmick::InitBubble()
{
	//�͈�
	this->bubbleWidth = 200.0f;														//����
	this->bubbleHeight = WIN_HEIGHT;						//�c��
	//�A������

	this->bubbleTransform.x = bubbleWidth;		//X���W
	this->bubbleTransform.y = bubbleHeight;			//Y���W
	this->bubbleTransform.radius = 32.0f;		//�����A�̔��a
	this->bubbleSpeed = 5.0f;			//���x
	this->isActiveBubble = false;		//�����Ă邩

	//�����̓����蔻��p
	this->bubbleHit.x = 0.0f;
	this->bubbleHit.y = 0.0f;
	this->bubbleHit.z = 0.0f;

	//�A���o��^�C�~���O
	this->bubbleCount = 60 * 4;
}

//�X�V
void WaterGimmick::MarioUpdate(bool& isHitBubble)
{
	//����
	UpdateWaterFlow(floor_->getMarioFloorpos());
	//�A�X�V
	UpdateBubble(isHitBubble);

}
void WaterGimmick::SonicUpdate(bool& isHitBubble)
{
	//�A�X�V
	UpdateBubble(isHitBubble);

}

//�����X�V
void WaterGimmick::UpdateWaterFlow(float floorPos)
{
	for (int i = 0; i < EMITTER_MAX; i++)
	{

		if (isActiveWaterFlow[i] == false)
		{
			isActiveWaterFlow[i] = true;
			waterFlowTransform[i].x = WIN_WIDTH;
			waterFlowTransform[i].y = floorPos - waterFlowHeight;
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
void WaterGimmick::UpdateBubble(bool& isHit)
{
	if (bubbleCount <= 0)
	{
		bubbleCount = 0;
		isActiveBubble = true;
	}
	if (isActiveBubble == true)
	{
		if (isHit == false)
		{
			bubbleTransform.y -= bubbleSpeed;
		}

		if (bubbleTransform.y <= 0.0f || isHit == true)
		{
			bubbleTransform.x = bubbleWidth;
			bubbleTransform.y = bubbleHeight;
			isActiveBubble = false;
			isHit = false;
		}
	}
	else
	{
		
		bubbleCount--;
	}


}
//�����蔻��
//�����蔻��p�֐�
void WaterGimmick::IsHitBubble(Transform& transform, bool& isHit)
{
	bubbleHit.x = transform.x - bubbleTransform.x;
	bubbleHit.y = transform.y - bubbleTransform.y;
	bubbleHit.z = bubbleHit.x * bubbleHit.x + bubbleHit.y * bubbleHit.y;
	//�A���o�Ă�Ƃ�
	if (isActiveBubble == true && isHit == false)
	{
		//�������Ă邩
		if (bubbleHit.z <= (bubbleTransform.radius + transform.radius) *
			(bubbleTransform.radius + transform.radius))
		{
			isHit = true;
		}

	}
	if (isHit == true)
	{
		isActiveBubble = false;
		
	}

	DrawFormatString(0, 90, GetColor(255, 255, 255), "bubble::%f,%f,%f", bubbleHit.x, bubbleHit.y, bubbleHit.z);
	DrawFormatString(0, 120, GetColor(255, 255, 255), "pt,bt::%f,%f", transform.y, bubbleTransform.y);
}

//�`��
void WaterGimmick::MarioDraw()
{
	//�����`��
	for (int i = 0; i < EMITTER_MAX; i++)
	{
		DrawWaterFlow(i);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�A�`��

	DrawBubble();

	DrawFormatString(0, 60, GetColor(255, 255, 255), "bubble::%d", bubbleCount);
}
void WaterGimmick::SonicDraw()
{
	//�A�`��

	DrawBubble();

	DrawFormatString(0, 60, GetColor(255, 255, 255), "bubble::%d", bubbleCount);
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
