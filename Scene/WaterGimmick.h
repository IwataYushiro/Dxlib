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
	void MarioUpdate(bool& isHitBubble);
	void SonicUpdate(bool& isHitBubble);

	//水流更新
	void UpdateWaterFlow(float floorPos);
	//泡更新
	void UpdateMarioBubble(bool& isHit);
	void UpdateSonicBubble(bool& isHit);
	//リセット
	void Reset();
	//描画
	void DrawMario();
	void DrawSonic();

	//水流描画
	void DrawWaterFlow(int num);
	//泡描画
	void DrawMarioBubble();
	void DrawSonicBubble();
	//当たり判定
	void IsHitBubbleMario(Transform& transform, bool& isHit);
	void IsHitBubbleSonic(Transform& transform, bool& isHit);
	//最大値

	static const int GetEmitMax() { return EMITTER_MAX; }
	//アクセッサ(水流)
	Transform* GetWaterFlowTransform() { return waterFlowTransform; }
	bool* GetIsActiveWaterFlow() { return isActiveWaterFlow; }

	//アクセッサ(水流)
	Transform* GetBubbleTransform() { return bubbleTransform; }
	bool* GetIsActiveBubble() { return isActiveBubble; }

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
	bool   isActiveWaterFlow[EMITTER_MAX];		//生きてるか


private://泡

	float  bubbleWidth[jumpLength];						//横幅
	float  bubbleHeight[jumpLength];						//縦幅
	Transform bubbleTransform[jumpLength];				//座標
	float  bubbleSpeed[jumpLength];						//速度
	bool   isActiveBubble[jumpLength];					//生きてるか
		
	//泡の当たり判定用
	Hit bubbleHit[jumpLength];

	//泡が出るカウント
	int bubbleCount[jumpLength];

};

