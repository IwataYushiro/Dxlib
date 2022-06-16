#pragma once
#include "DxLib.h"
#include "PlayerTransform.h"

class Player
{
public:
	Player();
	~Player();
	
	//‰Šú‰»
	void Initialize();
	//XV
	void Update(char* key, char* oldkey);
	//•`‰æ
	void Draw();
	

private:

	Transform transform;
	float moveSpeed;
	//‰j‚¢‚¾‚©
	bool isSwim;
	//•‚—Í
	float swimPower;
	//d—Í
	float gravity;
};

