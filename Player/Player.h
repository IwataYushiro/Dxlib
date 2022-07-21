#pragma once
#include "DxLib.h"
#include "Floor.h"
#include "Transform.h"
#include "WaterGimmick.h"

class Player
{
public:
	~Player();

	//初期化
	void Initialize();

	//プレイヤー情報
	void InitPlayer();
	//乗り物
	void InitVehicle();
	
	//水流
	void InitWaterflow();
	//泡
	void InitBubble();
	//浮遊水流
	void InitFloating();

	//更新
	void MarioUpdate(char* key, char* oldkey);
	
	void SonicUpdate(char* key, char* oldkey);

	//マリオ風泳ぎ
	void MarioSwim(char* key, char* oldkey);
	//乗り物更新
	void MarioVehicle(char* key, char* oldkey);
	//乗り物の当たり判定
	// 
	//ソニック風
	void SonicSwim(char* key, char* oldkey);

	//水流
	void WaterFlow();
	//当たり判定用関数
	void IsHitWaterFlow(Transform& transform, int num);

	//泡
	void BubbleMario();
	void BubbleSonic();
	//浮遊水流
	void Floating();
	//当たり判定用関数
	void IsHitFloating(Transform& transform, int num);

	//死んだあと
	void DeathMario(char* key, char* oldkey);
	void DeathSonic(char* key, char* oldkey);

	//ジャンプチェンジ時のリセット
	void Reset();

	//描画
	void DrawMario();
	void DrawSonic();

	//生きてるとき
	void DrawMarioAlive();
	//乗り物
	void DrawVehicle();

	void DrawSonicAlive();

	//窒息したとき
	void DrawMarioChoking();
	void DrawSonicChoking();
	//プレイヤー情報のアクセッサ
	Transform* GetPlayerTransform() { return playerTransform; }
	//当たり判定のアクセッサ
	bool GetIsHitMarioBubble() { return isHitBubble[mario]; }
	bool GetIsHitSonicBubble() { return isHitBubble[sonic]; }

private:
	//床との当たり判定を得るために包含
	Floor* floor_ = nullptr;

	//プレイヤーの情報

	Transform playerTransform[jumpLength];
	float moveSpeed[jumpLength];

	//仕掛けの反映用
	WaterGimmick* waterGimmick_ = nullptr;

	//泳いだか
	bool isSwim[jumpLength];
	//浮力(変わらない)
	const float buoyancy[jumpLength] = { 6.0f,10.0f };
	//重力
	float gravity[jumpLength];
	//生きてるか
	bool isAlive[jumpLength];
	//寿命
	int aliveCount[jumpLength];
	
	//乗り物
	bool isBoardingVehicle;//乗ってるか
	Transform vehicleTransform;

	//水流(マリオ風)
	//当たったか
	bool isHitWaterflow;
	//当たり判定用
	Hit waterFlowHit;

	//泡(共通)
	//当たったか
	bool isHitBubble[jumpLength];
	//当たり判定用
	Hit bubbleHit[jumpLength];

	//浮遊水流
	//当たったか
	bool isHitFloating;
	//当たり判定用
	Hit floatingHit;
};
