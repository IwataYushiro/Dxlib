#pragma once
#include "Floor.h"
#include "Hit.h"
#include "Global.h"
#include <stdlib.h>
#include <time.h>
#include <Transform.h>

class WaterGimmick
{
public:
	~WaterGimmick();
	//������
	void Initialize();

	//����������
	void InitWaterflow();
	//�A������
	void InitBubble();

	//�X�V
	void MarioUpdate(bool& isHitBubble);
	void SonicUpdate(bool& isHitBubble);

	//�����X�V
	void UpdateWaterFlow(float floorPos);
	//�A�X�V
	void UpdateBubble(bool& isHit);

	//�`��
	void MarioDraw();
	void SonicDraw();

	//�����`��
	void DrawWaterFlow(int num);
	//�A�`��
	void DrawBubble();
	//�����蔻��
	void IsHitBubble(Transform& transform, bool& isHit);
	//�ő�l

	static const int GetEmitMax() { return EMITTER_MAX; }
	//�A�N�Z�b�T(����)
	Transform* GetWaterFlowTransform() { return waterFlowTransform; }
	bool* GetIsActiveWaterFlow() { return isActiveWaterFlow; }

	//�A�N�Z�b�T(����)
	Transform GetBubbleTransform() { return bubbleTransform; }
	bool GetIsActiveBubble() { return isActiveBubble; }

private://����
	//�������p�[�e�B�N���������邽�߂̕ϐ�
	static const int EMITTER_MAX = 1500;			//�ő��
	//���̏����擾
	Floor* floor_ = nullptr;

	float  waterFlowWidth;						//����
	float  waterFlowHeight;						//�c��
	Transform waterFlowTransform[EMITTER_MAX];	//���W
	float  waterFlowSpeed[EMITTER_MAX];			//���x
	int    waterFlowBright[EMITTER_MAX];		//���邳
	bool   isActiveWaterFlow[EMITTER_MAX];		//�����Ă邩


private://�A

	float  bubbleWidth;						//����
	float  bubbleHeight;						//�c��
	Transform bubbleTransform;				//���W
	float  bubbleSpeed;						//���x
	bool   isActiveBubble;					//�����Ă邩
		
	//�A�̓����蔻��p
	Hit bubbleHit;

	//�A���o��J�E���g
	int bubbleCount;

};

