#pragma once
#include "DxLib.h"
#include "Floor.h"
#include "Transform.h"
#include "WaterGimmick.h"

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
	//�����̓����蔻��
	void IsHitWaterFlow(Transform& transform, int num);
	//���񂾂���
	void Death(char* key, char* oldkey);
	//�`��
	void Draw();
	//�����Ă�Ƃ�
	void DrawAlive();
	//���������Ƃ�
	void DrawChoking();

	//�v���C���[���̃A�N�Z�b�T
	Transform GetPlayerTransform() { return playerTransform; }

private:
	//���Ƃ̓����蔻��𓾂邽�߂ɕ��
	Floor* floor_ = nullptr;

	//�v���C���[�̏��
	Transform playerTransform;
	float moveSpeed;

	//�d�|���̔��f�p
	WaterGimmick* waterGimmick_ = nullptr;

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
	//�����q�b�g
	bool isHitWaterflow;
	//�����蔻��p
	Hit playerWaterFlowHit;
};

