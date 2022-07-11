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
	
private:
	//���Ƃ̓����蔻��𓾂邽�߂ɕ��
	Floor* floor_ = nullptr;

	//�v���C���[�̏��
	Transform transform;
	float moveSpeed;
	
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
	
};

