#pragma once
#include "DxLib.h"
#include <stdlib.h>
#include <time.h>
#include "PlayerTransform.h"


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
	//アクセッサ
	float getFloorpos() { return floorPos; }
private:

	Transform transform;
	float moveSpeed;
	//床の位置
	float floorPos;

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
	//泡が出るカウント
	float bublleCount;
};

