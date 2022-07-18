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
	//�v���C���[���
	void InitPlayer();
	//����
	void InitWaterflow();
	//�A
	void InitBubble();

	//�X�V
	void Update(char* key, char* oldkey);

	//�}���I���j��
	void MarioSwim(char* key, char* oldkey);

	//����
	void WaterFlow();
	//�����蔻��p�֐�
	void IsHitWaterFlow(Transform& transform, int num);
	
	//�A
	void Bubble();
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
	//�����蔻��̃A�N�Z�b�T
	bool& GetIsHitBubble() { return isHitBubble; }
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
	int aliveCount;
	
	//����
	//����������
	bool isHitWaterflow;
	//�����蔻��p
	Hit waterFlowHit;

	//�A
	//����������
	bool isHitBubble;
	//�����蔻��p
	Hit bubbleHit;
};

