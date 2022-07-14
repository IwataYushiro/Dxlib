#pragma once
#include "DxLib.h"
#include "Floor.h"
#include "Transform.h"
#include "WaterGimmick.h"

#include <stdlib.h>
#include <time.h>

class Player
{
public:

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
	//�����Ă�Ƃ�
	void DrawAlive();
	//���������Ƃ�
	void DrawChoking();

	//�v���C���[���̃A�N�Z�b�T
	Transform GetPlayerTransform() { return transform; }

private:
	//���Ƃ̓����蔻��𓾂邽�߂ɕ��
	Floor* floor_ = nullptr;

	//�v���C���[�̏��
	Transform transform;
	float moveSpeed;

	//�d�|���̔��f�p
	//WaterGimmick* waterGimmick_ = nullptr;

	//�j������
	bool isSwim = true;
	//����
	const float buoyancy = 6.0f;
	//�d��
	float gravity;
	//�����Ă邩
	bool isAlive;
	//����
	float aliveCount;

};

