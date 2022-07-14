#pragma once
#include "Floor.h"
#include "Hit.h"
#include "Global.h"
#include "Player.h"
#include "Transform.h"

#include <stdlib.h>
#include <time.h>

class WaterGimmick
{
public:
	~WaterGimmick();
	//初期化
	void Initialize();

	//水流初期化
	void InitWaterflow();
	
	//更新
	void Update();

	//水流更新
	void UpdateWaterFlow();
	//泡更新
	void UpdateBubble();
	//描画
	void Draw();
	//水流描画
	void DrawWaterFlow(int num);

	//アクセッサ
	bool GetIsHitWaterflow() { return isHitWaterflow; }
private:

	//床の情報を取得
	Floor* floor_ = nullptr;

	//プレイヤー包含
	//Player* player_ = nullptr;

	//水流をパーティクル生成するための変数
	static const int EMITTER_MAX = 1500;			//最大個数

	float  waterFlowWidth;						//横幅
	float  waterFlowHeight;						//縦幅
	float  waterFlowPosX[EMITTER_MAX];			//X座標
	float  waterFlowPosY[EMITTER_MAX];			//Y座標
	float  waterFlowRadius[EMITTER_MAX];		//水流泡の半径
	float  waterFlowSpeed[EMITTER_MAX];			//速度
	int    waterFlowBright[EMITTER_MAX];		//明るさ
	bool   waterFlowIsActive[EMITTER_MAX];		//生きてるか

	//水流の当たり判定用
	Hit waterFlowHit;
	//当たったか
	bool isHitWaterflow;
};

