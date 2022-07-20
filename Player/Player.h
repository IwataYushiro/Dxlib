#pragma once
#include "DxLib.h"
#include "Floor.h"
#include "Transform.h"
#include "WaterGimmick.h"

class Player
{
public:
	Player();
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
	void MarioUpdate(char* key, char* oldkey);
	void SonicUpdate(char* key, char* oldkey);

	//�}���I���j��
	void MarioSwim(char* key, char* oldkey);
	//�\�j�b�N��
	void SonicSwim(char* key, char* oldkey);

	//����
	void WaterFlow();
	//�����蔻��p�֐�
	void IsHitWaterFlow(Transform& transform, int num);

	//�A
	void BubbleMario();
	void BubbleSonic();

	//���񂾂���
	void DeathMario(char* key, char* oldkey);
	void DeathSonic(char* key, char* oldkey);
	//�W�����v�`�F���W���̃��Z�b�g
	void Reset();

	//�`��
	void DrawMario();
	void DrawSonic();

	//�����Ă�Ƃ�
	void DrawMarioAlive();
	void DrawSonicAlive();

	//���������Ƃ�
	void DrawMarioChoking();
	void DrawSonicChoking();
	//�v���C���[���̃A�N�Z�b�T
	Transform* GetPlayerTransform() { return playerTransform; }
	//�����蔻��̃A�N�Z�b�T
	bool* GetIsHitBubble() { return isHitBubble; }
private:
	//���Ƃ̓����蔻��𓾂邽�߂ɕ��
	Floor* floor_ = nullptr;

	//�v���C���[�̏��

	Transform playerTransform[jumpLength];
	float moveSpeed[jumpLength];

	//�d�|���̔��f�p
	WaterGimmick* waterGimmick_ = nullptr;

	//�j������
	bool isSwim[jumpLength];
	//����(�ς��Ȃ�)
	const float buoyancy[jumpLength] = { 6.0f,10.0f };
	//�d��
	float gravity[jumpLength];
	//�����Ă邩
	bool isAlive[jumpLength];
	//����
	int aliveCount[jumpLength];

	//����(�}���I��)
	//����������
	bool isHitWaterflow;
	//�����蔻��p
	Hit waterFlowHit;

	//�A(����)
	//����������
	bool isHitBubble[jumpLength];
	//�����蔻��p
	Hit bubbleHit[jumpLength];
};
