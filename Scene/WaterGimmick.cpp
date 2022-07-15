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
	//泡初期化
	InitBubble();
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
		this->waterFlowTransform[i].y = floor_->getFloorpos() - waterFlowHeight;			//Y座標
		this->waterFlowTransform[i].radius = 5;		//水流泡の半径
		this->waterFlowSpeed[i] = 5;			//速度
		this->waterFlowBright[i] = 255;		//明るさ
		this->isActiveWaterFlow[i] = false;		//生きてるか
	}
}

//泡初期化
void WaterGimmick::InitBubble()
{
	//範囲
	this->bubbleWidth = 200.0f;														//横幅
	this->bubbleHeight = floor_->getFloorpos();						//縦幅
	//泡初期化

	this->bubbleTransform.x = waterFlowWidth;		//X座標
	this->bubbleTransform.y = waterFlowHeight;			//Y座標
	this->bubbleTransform.radius = 32;		//水流泡の半径
	this->bubbleSpeed = 5;			//速度
	this->isActiveBubble = false;		//生きてるか

	//水流の当たり判定用
	this->bubbleHit.x = 0;
	this->bubbleHit.y = 0;
	this->bubbleHit.z = 0;

	//泡が出るタイミング
	this->bubbleCount = 60.0f * 4.0f;
}





//更新
void WaterGimmick::Update(Transform player)
{
	//水流
	UpdateWaterFlow();
	//泡更新
	UpdateBubble(player);
	
}

//水流更新
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

//泡更新
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



//描画
void WaterGimmick::Draw()
{
	//水流描画
	for (int i = 0; i < EMITTER_MAX; i++)
	{
		DrawWaterFlow(i);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//泡描画
	DrawBubble();
	DrawFormatString(0, 60, GetColor(255, 255, 255), "bubble::%f", bubbleCount);
}

//水流描画
void WaterGimmick::DrawWaterFlow(int num)
{
	if (isActiveWaterFlow[num] == true)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, waterFlowBright[num]);
		DrawCircle(waterFlowTransform[num].x, waterFlowTransform[num].y, waterFlowTransform[num].radius, GetColor(255, 255, 255), false);
	}

}

//泡描画
void WaterGimmick::DrawBubble()
{
	if (isActiveBubble == true)
	{
		DrawCircle(bubbleTransform.x, bubbleTransform.y, bubbleTransform.radius, GetColor(255, 255, 255), false);
	}
	
}
