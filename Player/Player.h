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
	//��蕨
	void InitVehicle();
	
	//����
	void InitWaterflow();
	//�A
	void InitBubble();
	//���V����
	void InitFloating();

	//�X�V
	void MarioUpdate(char* key, char* oldkey);
	
	void SonicUpdate(char* key, char* oldkey);

	//�}���I���j��
	void MarioSwim(char* key, char* oldkey);
	//��蕨�X�V
	void MarioVehicle(char* key, char* oldkey);
	//��蕨�̓����蔻��
	// 
	//�\�j�b�N��
	void SonicSwim(char* key, char* oldkey);

	//����
	void WaterFlow();
	//�����蔻��p�֐�
	void IsHitWaterFlow(Transform& transform, int num);

	//�A
	void BubbleMario();
	void BubbleSonic();
	//���V����
	void Floating();
	//�����蔻��p�֐�
	void IsHitFloating(Transform& transform, int num);

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
	//��蕨
	void DrawVehicle();

	void DrawSonicAlive();

	//���������Ƃ�
	void DrawMarioChoking();
	void DrawSonicChoking();
	//�v���C���[���̃A�N�Z�b�T
	Transform* GetPlayerTransform() { return playerTransform; }
	//�����蔻��̃A�N�Z�b�T
	bool GetIsHitMarioBubble() { return isHitBubble[mario]; }
	bool GetIsHitSonicBubble() { return isHitBubble[sonic]; }

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
	
	//��蕨
	bool isBoardingVehicle;//����Ă邩
	Transform vehicleTransform;

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

	//���V����
	//����������
	bool isHitFloating;
	//�����蔻��p
	Hit floatingHit;
};
