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

	//更新
	void Update();

	//水流更新
	void UpdateWaterFlow();
	//当たり判定
	void IsHitWaterFlow(Transform transform, int num);
	//泡更新
	void UpdateBubble();
	//描画
	void Draw();
	//水流描画
	void DrawWaterFlow(int num);

	//最大値

	static const int GetEmitMax() { return EMITTER_MAX; }
	//アクセッサ
	Transform* GetWaterFlowTransform() { return waterFlowTransform; }
	bool* GetIsActiveWaterFlow() { return waterFlowIsActive; }
	bool GetIsHitWaterFlow() { return isHitWaterFlow; }
private:
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
	//当たったか
	bool isHitWaterFlow;
};

