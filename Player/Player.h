#pragma once
#include "DxLib.h"
#include "Floor.h"
#include "PlayerTransform.h"

#include <stdlib.h>
#include <time.h>

class Player
{
public:
	Player();
	~Player();

	//初期化
	void Initialize();

	//更新
	void Update(char* key, char* oldkey);

	//マリオ風泳ぎ
	void MarioSwim(char* key, char* oldkey);
	//死んだあと
	void Death(char* key, char* oldkey);
	//描画
	void Draw();
	
private:
	//床との当たり判定を得るために包含
	Floor* floor_ = nullptr;

	//プレイヤーの情報
	Transform transform;
	float moveSpeed;
	
	//泳いだか
	bool isSwim;
	//浮力
	const float buoyancy = 6.0f;
	//重力
	float gravity;
	//生きてるか
	bool isAlive;
	//寿命
	float aliveCount;
	
};

