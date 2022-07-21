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
	//浮遊渦巻初期化
	void InitFloating();

	//更新
	void MarioUpdate(bool isHitBubble);
	void SonicUpdate(bool isHitBubble);

	//水流更新
	void UpdateWaterFlow(float floorPos);
	//泡更新
	void UpdateMarioBubble(bool& isHit);
	void UpdateSonicBubble(bool& isHit);
	//浮遊渦巻更新
	void UpdateFloating();

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
	//浮遊水流描画
	void DrawFloating(int num);

	//当たり判定
	void IsHitBubbleMario(Transform& transform, bool& isHit);
	void IsHitBubbleSonic(Transform& transform, bool& isHit);

	//最大値
	static const int GetWaterFlowEmitMax() { return WATERFLOW_MAX; }
	static const int GetFloatingEmitMax() { return FLOATING_MAX; }

	//アクセッサ(水流)
	Transform* GetWaterFlowTransform() { return waterFlowTransform; }
	bool* GetIsActiveWaterFlow() { return isActiveWaterFlow; }

	//アクセッサ(泡)
	Transform GetMarioBubbleTransform() { return bubbleTransform[mario]; }
	bool GetMarioIsActiveBubble() { return isActiveBubble[mario]; }

	Transform GetSonicBubbleTransform() { return bubbleTransform[sonic]; }
	bool GetSonicIsActiveBubble() { return isActiveBubble[sonic]; }

	//アクセッサ(浮遊渦巻)
	Transform* GetFloatingTransform() { return floatingTransform; }
	bool* GetIsActiveFloating() { return isActiveFloating; }

private:
	//床の情報を取得
	Floor* floor_ = nullptr;

	//水流
		//水流をパーティクル生成するための変数
	static const int WATERFLOW_MAX = 1500;			//最大個数

	float  waterFlowWidth;						//横幅
	float  waterFlowHeight;						//縦幅
	Transform waterFlowTransform[WATERFLOW_MAX];	//座標
	float  waterFlowSpeed[WATERFLOW_MAX];			//速度
	int    waterFlowBright[WATERFLOW_MAX];		//明るさ
	bool   isActiveWaterFlow[WATERFLOW_MAX];		//生きてるか


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
private://浮遊渦巻

	//水流をパーティクル生成するための変数
	static const int FLOATING_MAX = 1500;			//最大個数

	float  floatingWidth;						//横幅
	float  floatingHeight;						//縦幅
	Transform floatingTransform[FLOATING_MAX];	//座標
	float  floatingSpeed[FLOATING_MAX];			//速度
	int    floatingBright[FLOATING_MAX];		//明るさ
	bool   isActiveFloating[FLOATING_MAX];		//生きてるか

};

