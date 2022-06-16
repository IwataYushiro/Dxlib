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
	//描画
	void Draw();
	

private:

	Transform transform;
	float moveSpeed;
	//泳いだか
	bool isSwim;
	//浮力
	float swimPower;
	//重力
	float gravity;
};

