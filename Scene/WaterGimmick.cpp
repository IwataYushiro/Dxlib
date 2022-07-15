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
		this->waterFlowTransform[i].y = WIN_HEIGHT - floor_->getFloorpos() - waterFlowHeight;			//Y���W
		this->waterFlowTransform[i].radius = 5;		//�����A�̔��a
		this->waterFlowSpeed[i] = 5;			//���x
		this->waterFlowBright[i] = 255;		//���邳
		this->waterFlowIsActive[i] = false;		//�����Ă邩
	}
	//�����蔻��p
	this->waterFlowHit.x = 0;
	this->waterFlowHit.y = 0;
	this->waterFlowHit.z = 0;

	this->isHitWaterFlow = false;
}
//�X�V
void WaterGimmick::Update()
{
	//����
	UpdateWaterFlow();
}
//�����X�V
void WaterGimmick::UpdateWaterFlow()
{
	for (int i = 0; i < EMITTER_MAX; i++)
	{

		if (waterFlowIsActive[i] == false)
		{
			waterFlowIsActive[i] = true;
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

		if (waterFlowIsActive[i] == true)
		{
			waterFlowBright[i] -= 2;
			waterFlowTransform[i].x -= waterFlowSpeed[i];
			waterFlowTransform[i].y -= rand() % 5 - 2;


		}
		if (waterFlowBright[i] <= 0)
		{
			waterFlowIsActive[i] = false;
			waterFlowBright[i] = 255;
		}
	}


}
//�A�X�V
void WaterGimmick::UpdateBubble()
{

}

void WaterGimmick::IsHitWaterFlow(Transform transform, int num)
{
	if (waterFlowIsActive[num] == true)
	{
		waterFlowHit.x = transform.x - waterFlowTransform[num].x;
		waterFlowHit.y = transform.y - waterFlowTransform[num].y;
		waterFlowHit.z = waterFlowHit.x * waterFlowHit.x + waterFlowHit.y * waterFlowHit.y;
	}
	if (waterFlowHit.z <= (transform.radius + waterFlowTransform[num].radius) *
		(transform.radius + waterFlowTransform[num].radius))
	{
		isHitWaterFlow = true;
	}

}
//�`��
void WaterGimmick::Draw()
{
	for (int i = 0; i < EMITTER_MAX; i++)
	{
		DrawWaterFlow(i);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//�����`��
void WaterGimmick::DrawWaterFlow(int num)
{
	if (waterFlowIsActive[num] == true)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, waterFlowBright[num]);
		DrawCircle(waterFlowTransform[num].x, waterFlowTransform[num].y, waterFlowTransform[num].radius, GetColor(255, 255, 255), false);
	}

}
