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
	//浮遊水流初期化
	InitFloating();
}

//水流初期化
void WaterGimmick::InitWaterflow() {

	//範囲
	this->waterFlowWidth = WIN_WIDTH;						//横幅
	this->waterFlowHeight = 10.0f;						//縦幅
	//水流初期化
	for (int i = 0; i < WATERFLOW_MAX; i++)
	{

		this->waterFlowTransform[i].x = waterFlowWidth;		//X座標
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
	for (int i = 0; i < jumpLength; i++)
	{
		//範囲
		this->bubbleWidth[i] = 200.0f;														//横幅
		this->bubbleHeight[i] = WIN_HEIGHT;						//縦幅
		//泡初期化

		this->bubbleTransform[i].x = bubbleWidth[i];		//X座標
		this->bubbleTransform[i].y = bubbleHeight[i];			//Y座標
		this->bubbleTransform[i].radius = 32.0f;		//水流泡の半径
		this->bubbleSpeed[i] = 5.0f;			//速度
		this->isActiveBubble[i] = false;		//生きてるか

		//泡の当たり判定用
		this->bubbleHit[i].x = 0.0f;
		this->bubbleHit[i].y = 0.0f;
		this->bubbleHit[i].z = 0.0f;

		//泡が出るタイミング
		this->bubbleCount[i] = 60 * 4;
	}

}
//浮遊水流初期化
void WaterGimmick::InitFloating()
{
	this->floatingWidth = WIN_WIDTH;						//横幅
	this->floatingHeight = WIN_HEIGHT;						//縦幅

	for (int i = 0; i < FLOATING_MAX; i++)
	{
		this->floatingTransform[i].x = floatingWidth - floor_->getSonicFloorpos();	//座標
		this->floatingTransform[i].y = floatingHeight;
		this->floatingTransform[i].radius = 10.0;//線で描画するから使わない
		this->floatingSpeed[i] = 10.0f;			//速度
		this->floatingBright[i] = 255;		//明るさ
		this->isActiveFloating[i] = false;		//生きてるか
	}
}


//更新
void WaterGimmick::MarioUpdate(bool isHitBubble)
{
	//水流
	UpdateWaterFlow(floor_->getMarioFloorpos());
	//泡更新
	UpdateMarioBubble(isHitBubble);

}
void WaterGimmick::SonicUpdate(bool isHitBubble)
{
	//浮遊水流
	UpdateFloating();
	//泡更新
	UpdateSonicBubble(isHitBubble);

}

//水流更新
void WaterGimmick::UpdateWaterFlow(float floorPos)
{
	for (int i = 0; i < WATERFLOW_MAX; i++)
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
	for (int i = 0; i < WATERFLOW_MAX; i++)
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
void WaterGimmick::UpdateMarioBubble(bool& isHit)
{
	if (bubbleCount[mario] <= 0)
	{
		bubbleCount[mario] = 0;
		isActiveBubble[mario] = true;
	}
	if (isActiveBubble[mario] == true)
	{
		if (isHit == false)
		{
			bubbleTransform[mario].y -= bubbleSpeed[mario];
		}

		if (bubbleTransform[mario].y <= 0.0f || isHit == true)
		{
			bubbleTransform[mario].x = bubbleWidth[mario];
			bubbleTransform[mario].y = bubbleHeight[mario];
			isActiveBubble[mario] = false;
			bubbleCount[mario] = 60 * 4;
			isHit = false;
		}
	}
	else
	{

		bubbleCount[mario]--;
	}
}

void WaterGimmick::UpdateSonicBubble(bool& isHit)
{
	if (bubbleCount[sonic] <= 0)
	{
		bubbleCount[sonic] = 0;
		isActiveBubble[sonic] = true;
	}
	if (isActiveBubble[sonic] == true)
	{
		if (isHit == false)
		{
			bubbleTransform[sonic].y -= bubbleSpeed[sonic];
		}

		if (bubbleTransform[sonic].y <= 0.0f || isHit == true)
		{
			bubbleTransform[sonic].x = bubbleWidth[sonic];
			bubbleTransform[sonic].y = bubbleHeight[sonic];
			isActiveBubble[sonic] = false;
			bubbleCount[sonic] = 60 * 4;
			isHit = false;
		}
	}
	else
	{

		bubbleCount[sonic]--;
	}
}

// 浮遊水流更新
void WaterGimmick::UpdateFloating()
{
	for (int i = 0; i < WATERFLOW_MAX; i++)
	{

		if (isActiveFloating[i] == false)
		{
			isActiveFloating[i] = true;
			floatingTransform[i].x = floatingWidth - rand() % 300;
			floatingTransform[i].y = floatingHeight;
			if (i % 2 == 0)
			{
				break;
			}
		}
	}
	for (int i = 0; i < WATERFLOW_MAX; i++)
	{

		if (isActiveFloating[i] == true)
		{
			floatingBright[i] -= 2;
			floatingTransform[i].y -= floatingSpeed[i];
		}
		if (floatingBright[i] <= 0)
		{
			isActiveFloating[i] = false;
			floatingBright[i] = 255;
		}
	}
}

//リセット
void WaterGimmick::Reset()
{
	waterFlowWidth = WIN_WIDTH - 200.0f;
	waterFlowHeight = 10.0f;

	for (int i = 0; i < WATERFLOW_MAX; i++)
	{

		waterFlowTransform[i].x = waterFlowWidth;		//X座標
		waterFlowTransform[i].y = floor_->getMarioFloorpos() - waterFlowHeight;
		waterFlowTransform[i].radius = 5.0f;		//水流泡の半径
		waterFlowSpeed[i] = 5.0f;			//速度
		waterFlowBright[i] = 255;		//明るさ
		isActiveWaterFlow[i] = false;		//生きてるか
	}

	for (int i = 0; i < jumpLength; i++)
	{

		//範囲
		bubbleWidth[i] = 200.0f;														//横幅
		bubbleHeight[i] = WIN_HEIGHT;						//縦幅
		//泡初期化

		bubbleTransform[i].x = bubbleWidth[i];		//X座標
		bubbleTransform[i].y = bubbleHeight[i];			//Y座標
		bubbleTransform[i].radius = 32.0f;		//水流泡の半径
		bubbleSpeed[i] = 5.0f;			//速度
		isActiveBubble[i] = false;		//生きてるか

		//泡の当たり判定用
		bubbleHit[i].x = 0.0f;
		bubbleHit[i].y = 0.0f;
		bubbleHit[i].z = 0.0f;

		//泡が出るタイミング
		bubbleCount[i] = 60 * 4;
	}

	//浮遊水流
	this->floatingWidth = WIN_WIDTH;						//横幅
	this->floatingHeight = WIN_HEIGHT;						//縦幅

	for (int i = 0; i < FLOATING_MAX; i++)
	{
		this->floatingTransform[i].x = floatingWidth - floor_->getSonicFloorpos();	//座標
		this->floatingTransform[i].y = floatingHeight;
		this->floatingTransform[i].radius = 10.0f;//線の長さ
		this->floatingSpeed[i] = 10.0f;			//速度
		this->floatingBright[i] = 255;		//明るさ
		this->isActiveFloating[i] = false;		//生きてるか
	}
}


//描画
void WaterGimmick::DrawMario()
{
	//水流描画
	for (int i = 0; i < WATERFLOW_MAX; i++)
	{
		DrawWaterFlow(i);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//泡描画

	DrawMarioBubble();

	DrawFormatString(0, 60, GetColor(255, 255, 255), "bubble::%d", bubbleCount[mario]);
}
void WaterGimmick::DrawSonic()
{
	//浮遊水流描画
	for (int i = 0; i < FLOATING_MAX; i++)
	{
		DrawFloating(i);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//泡描画
	DrawSonicBubble();

	DrawFormatString(0, 60, GetColor(255, 255, 255), "bubble::%d", bubbleCount[sonic]);
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
void WaterGimmick::DrawMarioBubble()
{
	if (isActiveBubble[mario] == true)
	{
		DrawCircle(bubbleTransform[mario].x, bubbleTransform[mario].y, bubbleTransform[mario].radius, GetColor(255, 255, 255), false);
	}
}

void WaterGimmick::DrawSonicBubble()
{
	if (isActiveBubble[sonic] == true)
	{
		DrawCircle(bubbleTransform[sonic].x, bubbleTransform[sonic].y, bubbleTransform[sonic].radius, GetColor(255, 255, 255), false);
	}
}

//浮遊水流描画
void WaterGimmick::DrawFloating(int num)
{
	if (isActiveFloating[num] == true)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, floatingBright[num]);
		//DrawLine(floatingTransform[num].x, floatingTransform[num].y, floatingTransform[num].x, floatingTransform[num].y + floatingTransform[num].radius, GetColor(255, 255, 255), 2);
		DrawCircle(floatingTransform[num].x, floatingTransform[num].y, floatingTransform[num].radius, GetColor(255, 255, 255), false);
	}
}
//当たり判定
//当たり判定用関数
void WaterGimmick::IsHitBubbleMario(Transform& transform, bool& isHit)
{
	bubbleHit[mario].x = transform.x - bubbleTransform[mario].x;
	bubbleHit[mario].y = transform.y - bubbleTransform[mario].y;
	bubbleHit[mario].z = bubbleHit[mario].x * bubbleHit[mario].x + bubbleHit[mario].y * bubbleHit[mario].y;
	//泡が出てるとき
	if (isActiveBubble[mario] == true && isHit == false)
	{
		//当たってるか
		if (bubbleHit[mario].z <= (bubbleTransform[mario].radius + transform.radius) *
			(bubbleTransform[mario].radius + transform.radius))
		{
			isHit = true;
		}

	}
	if (isHit == true)
	{
		isActiveBubble[mario] = false;
	}
}

void WaterGimmick::IsHitBubbleSonic(Transform& transform, bool& isHit)
{
	bubbleHit[sonic].x = transform.x - bubbleTransform[sonic].x;
	bubbleHit[sonic].y = transform.y - bubbleTransform[sonic].y;
	bubbleHit[sonic].z = bubbleHit[sonic].x * bubbleHit[sonic].x + bubbleHit[sonic].y * bubbleHit[sonic].y;
	//泡が出てるとき
	if (isActiveBubble[sonic] == true && isHit == false)
	{
		//当たってるか
		if (bubbleHit[sonic].z <= (bubbleTransform[sonic].radius + transform.radius) *
			(bubbleTransform[sonic].radius + transform.radius))
		{
			isHit = true;
		}

	}
	if (isHit == true)
	{
		isActiveBubble[sonic] = false;

	}
}

