#include "WaterGimmick.h"

WaterGimmick::~WaterGimmick()
{
	delete floor_;
	delete player_;
}

//初期化
void WaterGimmick::Initialize()
{
	floor_ = new Floor();
	floor_->Initialize();

	player_ = new Player();
	player_->Initialize();
	srand(time(NULL));

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

		this->waterFlowPosX[i] = WIN_WIDTH - waterFlowWidth;;		//X座標
		this->waterFlowPosY[i] = WIN_HEIGHT - floor_->getFloorpos() - waterFlowHeight;			//Y座標
		this->waterFlowRadius[i] = 5;		//水流泡の半径
		this->waterFlowSpeed[i] = 5;			//速度
		this->waterFlowBright[i] = 255;		//明るさ
		this->waterFlowIsActive[i] = false;		//生きてるか
	}
	//当たり判定用
	this->waterFlowHit.x = 0;
	this->waterFlowHit.y = 0;
	this->waterFlowHit.z = 0;

	this->isHitWaterflow = false;
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
			waterFlowPosX[i] = WIN_WIDTH;
			waterFlowPosY[i] = floor_->getFloorpos() - waterFlowHeight;
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
			waterFlowPosX[i] -= waterFlowSpeed[i];
			waterFlowPosY[i] -= rand() % 5 - 2;

			if (waterFlowBright[i] <= 0)
			{
				waterFlowBright[i] = 255;
				waterFlowIsActive[i] = false;
			}
		}
	}
	for (int i = 0; i < EMITTER_MAX; i++)
	{
		if (waterFlowIsActive[i] == true)
		{
			waterFlowHit.x = player_->GetPlayerTransform().x - waterFlowPosX[i];
			waterFlowHit.y = player_->GetPlayerTransform().y - waterFlowPosY[i];
			waterFlowHit.z = waterFlowHit.x * waterFlowHit.x + waterFlowHit.y * waterFlowHit.y;
		}
		if (waterFlowHit.z <= (player_->GetPlayerTransform().radius +waterFlowRadius[i]) * 
			(player_->GetPlayerTransform().radius + waterFlowRadius[i]))
		{
			isHitWaterflow = true;
		}
	}

}
//泡更新
void WaterGimmick::UpdateBubble()
{

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
		DrawCircle(waterFlowPosX[num], waterFlowPosY[num], waterFlowRadius[num], GetColor(255, 255, 255), false);
	}

}
