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
	//���V�Q��������
	void InitFloating();

	//�X�V
	void MarioUpdate(bool isHitBubble);
	void SonicUpdate(bool isHitBubble);

	//�����X�V
	void UpdateWaterFlow(float floorPos);
	//�A�X�V
	void UpdateMarioBubble(bool& isHit);
	void UpdateSonicBubble(bool& isHit);
	//���V�Q���X�V
	void UpdateFloating();

	//���Z�b�g
	void Reset();
	//�`��
	void DrawMario();
	void DrawSonic();

	//�����`��
	void DrawWaterFlow(int num);
	//�A�`��
	void DrawMarioBubble();
	void DrawSonicBubble();
	//���V�����`��
	void DrawFloating(int num);

	//�����蔻��
	void IsHitBubbleMario(Transform& transform, bool& isHit);
	void IsHitBubbleSonic(Transform& transform, bool& isHit);

	//�ő�l
	static const int GetWaterFlowEmitMax() { return WATERFLOW_MAX; }
	static const int GetFloatingEmitMax() { return FLOATING_MAX; }

	//�A�N�Z�b�T(����)
	Transform* GetWaterFlowTransform() { return waterFlowTransform; }
	bool* GetIsActiveWaterFlow() { return isActiveWaterFlow; }

	//�A�N�Z�b�T(�A)
	Transform GetMarioBubbleTransform() { return bubbleTransform[mario]; }
	bool GetMarioIsActiveBubble() { return isActiveBubble[mario]; }

	Transform GetSonicBubbleTransform() { return bubbleTransform[sonic]; }
	bool GetSonicIsActiveBubble() { return isActiveBubble[sonic]; }

	//�A�N�Z�b�T(���V�Q��)
	Transform* GetFloatingTransform() { return floatingTransform; }
	bool* GetIsActiveFloating() { return isActiveFloating; }

private:
	//���̏����擾
	Floor* floor_ = nullptr;

	//����
		//�������p�[�e�B�N���������邽�߂̕ϐ�
	static const int WATERFLOW_MAX = 1500;			//�ő��

	float  waterFlowWidth;						//����
	float  waterFlowHeight;						//�c��
	Transform waterFlowTransform[WATERFLOW_MAX];	//���W
	float  waterFlowSpeed[WATERFLOW_MAX];			//���x
	int    waterFlowBright[WATERFLOW_MAX];		//���邳
	bool   isActiveWaterFlow[WATERFLOW_MAX];		//�����Ă邩


private://�A

	float  bubbleWidth[jumpLength];						//����
	float  bubbleHeight[jumpLength];						//�c��
	Transform bubbleTransform[jumpLength];				//���W
	float  bubbleSpeed[jumpLength];						//���x
	bool   isActiveBubble[jumpLength];					//�����Ă邩

	//�A�̓����蔻��p
	Hit bubbleHit[jumpLength];

	//�A���o��J�E���g
	int bubbleCount[jumpLength];
private://���V�Q��

	//�������p�[�e�B�N���������邽�߂̕ϐ�
	static const int FLOATING_MAX = 1500;			//�ő��

	float  floatingWidth;						//����
	float  floatingHeight;						//�c��
	Transform floatingTransform[FLOATING_MAX];	//���W
	float  floatingSpeed[FLOATING_MAX];			//���x
	int    floatingBright[FLOATING_MAX];		//���邳
	bool   isActiveFloating[FLOATING_MAX];		//�����Ă邩

};

