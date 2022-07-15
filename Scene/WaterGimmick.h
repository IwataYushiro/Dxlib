#pragma once
#include "Floor.h"
#include "Hit.h"
#include "Global.h"
#include <stdlib.h>
#include <time.h>
#include <Transform.h>

class WaterGimmick
{
public:
	~WaterGimmick();
	//初期化
	void Initialize();

	//水流初期化
	void InitWaterflow();
	//泡初期化
	void InitBubble();
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
	//泡描画
	void DrawBubble();
	//最大値

	static const int GetEmitMax() { return EMITTER_MAX; }
	//アクセッサ
	Transform* GetWaterFlowTransform() { return waterFlowTransform; }
	bool* GetIsActiveWaterFlow() { return waterFlowIsActive; }

private://水流
	//水流をパーティクル生成するための変数
	static const int EMITTER_MAX = 1500;			//最大個数
	//床の情報を取得
	Floor* floor_ = nullptr;

	float  waterFlowWidth;						//横幅
	float  waterFlowHeight;						//縦幅
	Transform waterFlowTransform[EMITTER_MAX];	//座標
	float  waterFlowSpeed[EMITTER_MAX];			//速度
	int    waterFlowBright[EMITTER_MAX];		//明るさ
	bool   waterFlowIsActive[EMITTER_MAX];		//生きてるか

	//水流の当たり判定用
	Hit waterFlowHit;
	

private://泡

	float  bubbleWidth;						//横幅
	float  bubbleHeight;						//縦幅
	Transform bubbleTransform;				//座標
	float  bubbleSpeed;						//速度
	bool   bubbleIsActive;					//生きてるか
		
	//泡の当たり判定用
	Hit bubbleHit;

	//泡が出るカウント
	float bubbleCount;

};

