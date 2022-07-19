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
		this->waterFlowTransform[i].y = floor_->getMarioFloorpos() - waterFlowHeight;			//Y座標
		this->waterFlowTransform[i].radius = 5.0f;		//水流泡の半径
		this->waterFlowSpeed[i] = 5.0f;			//速度
		this->waterFlowBright[i] = 255;		//明るさ
		this->isActiveWaterFlow[i] = false;		//生きてるか
	}
}

//泡初期化
void WaterGimmick::InitBubble()
{
	//範囲
	this->bubbleWidth = 200.0f;														//横幅
	this->bubbleHeight = WIN_HEIGHT;						//縦幅
	//泡初期化

	this->bubbleTransform.x = bubbleWidth;		//X座標
	this->bubbleTransform.y = bubbleHeight;			//Y座標
	this->bubbleTransform.radius = 32.0f;		//水流泡の半径
	this->bubbleSpeed = 5.0f;			//速度
	this->isActiveBubble = false;		//生きてるか

	//水流の当たり判定用
	this->bubbleHit.x = 0.0f;
	this->bubbleHit.y = 0.0f;
	this->bubbleHit.z = 0.0f;

	//泡が出るタイミング
	this->bubbleCount = 60 * 4;
}

//更新
void WaterGimmick::MarioUpdate(bool& isHitBubble)
{
	//水流
	UpdateWaterFlow(floor_->getMarioFloorpos());
	//泡更新
	UpdateBubble(isHitBubble);

}
void WaterGimmick::SonicUpdate(bool& isHitBubble)
{
	//泡更新
	UpdateBubble(isHitBubble);

}

//水流更新
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

//泡更新
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
//当たり判定
//当たり判定用関数
void WaterGimmick::IsHitBubble(Transform& transform, bool& isHit)
{
	bubbleHit.x = transform.x - bubbleTransform.x;
	bubbleHit.y = transform.y - bubbleTransform.y;
	bubbleHit.z = bubbleHit.x * bubbleHit.x + bubbleHit.y * bubbleHit.y;
	//泡が出てるとき
	if (isActiveBubble == true && isHit == false)
	{
		//当たってるか
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

//描画
void WaterGimmick::MarioDraw()
{
	//水流描画
	for (int i = 0; i < EMITTER_MAX; i++)
	{
		DrawWaterFlow(i);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//泡描画

	DrawBubble();

	DrawFormatString(0, 60, GetColor(255, 255, 255), "bubble::%d", bubbleCount);
}
void WaterGimmick::SonicDraw()
{
	//泡描画

	DrawBubble();

	DrawFormatString(0, 60, GetColor(255, 255, 255), "bubble::%d", bubbleCount);
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
