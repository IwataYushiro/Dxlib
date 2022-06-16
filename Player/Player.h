#pragma once
#include "DxLib.h"
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
	
	//描画
	void Draw();
	

private:

	Transform transform;
	float moveSpeed;
	//泳いだか
	bool isSwim;
	//浮力
	const float buoyancy = 6.0f;
	//重力
	float gravity;
};

