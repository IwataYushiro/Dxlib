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
	//水流
	void InitWaterflow();
	//泡
	void InitBubble();

	//更新
	void Update(char* key, char* oldkey);

	//マリオ風泳ぎ
	void MarioSwim(char* key, char* oldkey);

	//水流
	void WaterFlow();
	//当たり判定用関数
	void IsHitWaterFlow(Transform& transform, int num);
	
	//泡
	void Bubble();
	//死んだあと
	void Death(char* key, char* oldkey);

	//描画
	void Draw();
	
	//生きてるとき
	void DrawAlive();
	//窒息したとき
	void DrawChoking();

	//プレイヤー情報のアクセッサ
	Transform GetPlayerTransform() { return playerTransform; }
	//当たり判定のアクセッサ
	bool& GetIsHitBubble() { return isHitBubble; }
private:
	//床との当たり判定を得るために包含
	Floor* floor_ = nullptr;

	//プレイヤーの情報
	Transform playerTransform;
	float moveSpeed;

	//仕掛けの反映用
	WaterGimmick* waterGimmick_ = nullptr;

	//泳いだか
	bool isSwim = true;
	//浮力
	const float buoyancy = 6.0f;
	//重力
	float gravity;
	//生きてるか
	bool isAlive;
	//寿命
	int aliveCount;
	
	//水流
	//当たったか
	bool isHitWaterflow;
	//当たり判定用
	Hit waterFlowHit;

	//泡
	//当たったか
	bool isHitBubble;
	//当たり判定用
	Hit bubbleHit;
};

