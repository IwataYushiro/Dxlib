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

	//������
	void Initialize();

	//�X�V
	void Update(char* key, char* oldkey);

	//�}���I���j��
	void MarioSwim(char* key, char* oldkey);
	//���񂾂���
	void Death(char* key, char* oldkey);
	//�`��
	void Draw();
	//�A�N�Z�b�T
	float getFloorpos() { return floorPos; }
private:

	Transform transform;
	float moveSpeed;
	//���̈ʒu
	float floorPos;

	//�j������
	bool isSwim;
	//����
	const float buoyancy = 6.0f;
	//�d��
	float gravity;
	//�����Ă邩
	bool isAlive;
	//����
	float aliveCount;
	//�A���o��J�E���g
	float bublleCount;
};

