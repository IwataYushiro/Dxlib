#pragma once
#include "DxLib.h"
#include "PlayerTransform.h"

class Player
{
public:
	Player();
	~Player();
	
	//������
	void Initialize();
	//�X�V
	void Update(char* key);
	//�`��
	void Draw();

private:

	Transform transform;
	float moveSpeed;
};

