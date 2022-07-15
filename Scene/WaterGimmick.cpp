#include "WaterGimmick.h"
#include "DxLib.h"

WaterGimmick::~WaterGimmick()
{
	delete floor_;

}

//初期化
void WaterGimmick::Initialize()
{
	srand(time(NULL));

	floor_ = new Floor();
	floor_->Initialize();
	//水流初期化
	InitWaterflow();
}

//水流初期化
void WaterGimmick::InitWaterflow() {

	//範囲
	this->waterFlowWidth = 200.0f;						//横幅
	this->waterFlowHeight = 10.0f;						//縦幅
	//水流初期化
	for (int i = 0; i < EMITTER_MAX; i++)
	{

		this->waterFlowTransform[i].x = WIN_WIDTH - waterFlowWidth;		//X座標
		this->waterFlowTransform[i].y = WIN_HEIGHT - floor_->getFloorpos() - waterFlowHeight;			//Y座標
		this->waterFlowTransform[i].radius = 5;		//水流泡の半径
		this->waterFlowSpeed[i] = 5;			//速度
		this->waterFlowBright[i] = 255;		//明るさ
		this->waterFlowIsActive[i] = false;		//生きてるか
	}
	//当たり判定用
	this->waterFlowHit.x = 0;
	this->waterFlowHit.y = 0;
	this->waterFlowHit.z = 0;

	this->isHitWaterFlow = false;
}
//更新
void WaterGimmick::Update()
{
	//水流
	UpdateWaterFlow();
}
//水流更新
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
//泡更新
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
//描画
void WaterGimmick::Draw()
{
	for (int i = 0; i < EMITTER_MAX; i++)
	{
		DrawWaterFlow(i);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//水流描画
void WaterGimmick::DrawWaterFlow(int num)
{
	if (waterFlowIsActive[num] == true)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, waterFlowBright[num]);
		DrawCircle(waterFlowTransform[num].x, waterFlowTransform[num].y, waterFlowTransform[num].radius, GetColor(255, 255, 255), false);
	}

}
