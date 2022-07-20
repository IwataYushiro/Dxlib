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

//更新
void WaterGimmick::MarioUpdate(bool& isHitBubble)
{
	//水流
	UpdateWaterFlow(floor_->getMarioFloorpos());
	//泡更新
	UpdateMarioBubble(isHitBubble);

}
void WaterGimmick::SonicUpdate(bool& isHitBubble)
{
	//泡更新
	UpdateSonicBubble(isHitBubble);

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
void WaterGimmick::UpdateMarioBubble(bool& isHit)
{
	if (bubbleCount[0] <= 0)
	{
		bubbleCount[0] = 0;
		isActiveBubble[0] = true;
	}
	if (isActiveBubble[0] == true)
	{
		if (isHit == false)
		{
			bubbleTransform[0].y -= bubbleSpeed[0];
		}

		if (bubbleTransform[0].y <= 0.0f || isHit == true)
		{
			bubbleTransform[0].x = bubbleWidth[0];
			bubbleTransform[0].y = bubbleHeight[0];
			isActiveBubble[0] = false;
			bubbleCount[0] = 60 * 4;
			isHit = false;
		}
	}
	else
	{

		bubbleCount[0]--;
	}
}

void WaterGimmick::UpdateSonicBubble(bool& isHit)
{
	if (bubbleCount[1] <= 0)
	{
		bubbleCount[1] = 0;
		isActiveBubble[1] = true;
	}
	if (isActiveBubble[1] == true)
	{
		if (isHit == false)
		{
			bubbleTransform[1].y -= bubbleSpeed[1];
		}

		if (bubbleTransform[1].y <= 0.0f || isHit == true)
		{
			bubbleTransform[1].x = bubbleWidth[1];
			bubbleTransform[1].y = bubbleHeight[1];
			isActiveBubble[1] = false;
			bubbleCount[1] = 60 * 4;
			isHit = false;
		}
	}
	else
	{

		bubbleCount[1]--;
	}
}
//当たり判定
//当たり判定用関数
void WaterGimmick::IsHitBubbleMario(Transform& transform, bool& isHit)
{
	bubbleHit[0].x = transform.x - bubbleTransform[0].x;
	bubbleHit[0].y = transform.y - bubbleTransform[0].y;
	bubbleHit[0].z = bubbleHit[0].x * bubbleHit[0].x + bubbleHit[0].y * bubbleHit[0].y;
	//泡が出てるとき
	if (isActiveBubble[0] == true && isHit == false)
	{
		//当たってるか
		if (bubbleHit[0].z <= (bubbleTransform[0].radius + transform.radius) *
			(bubbleTransform[0].radius + transform.radius))
		{
			isHit = true;
		}

	}
	if (isHit == true)
	{
		isActiveBubble[0] = false;

	}
}

void WaterGimmick::IsHitBubbleSonic(Transform& transform, bool& isHit)
{
	bubbleHit[1].x = transform.x - bubbleTransform[1].x;
	bubbleHit[1].y = transform.y - bubbleTransform[1].y;
	bubbleHit[1].z = bubbleHit[1].x * bubbleHit[1].x + bubbleHit[1].y * bubbleHit[1].y;
	//泡が出てるとき
	if (isActiveBubble[1] == true && isHit == false)
	{
		//当たってるか
		if (bubbleHit[1].z <= (bubbleTransform[1].radius + transform.radius) *
			(bubbleTransform[1].radius + transform.radius))
		{
			isHit = true;
		}

	}
	if (isHit == true)
	{
		isActiveBubble[1] = false;

	}
}
//リセット
void WaterGimmick::Reset()
{
	waterFlowWidth = 200.0f;
	waterFlowHeight = 10.0f;

	for (int i = 0; i < jumpLength; i++)
	{
		waterFlowTransform[i].x = WIN_WIDTH - waterFlowWidth;		//X座標
		waterFlowTransform[i].y = floor_->getMarioFloorpos() - waterFlowHeight;
		waterFlowTransform[i].radius = 5.0f;		//水流泡の半径
		waterFlowSpeed[i] = 5.0f;			//速度
		waterFlowBright[i] = 255;		//明るさ
		isActiveWaterFlow[i] = false;		//生きてるか


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
}
//描画
void WaterGimmick::DrawMario()
{
	//水流描画
	for (int i = 0; i < EMITTER_MAX; i++)
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

