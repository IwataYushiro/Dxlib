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

	//�X�V
	void Update();

	//�����X�V
	void UpdateWaterFlow();
	//�����蔻��
	void IsHitWaterFlow(Transform transform, int num);
	//�A�X�V
	void UpdateBubble();
	//�`��
	void Draw();
	//�����`��
	void DrawWaterFlow(int num);

	//�ő�l

	static const int GetEmitMax() { return EMITTER_MAX; }
	//�A�N�Z�b�T
	Transform* GetWaterFlowTransform() { return waterFlowTransform; }
	bool* GetIsActiveWaterFlow() { return waterFlowIsActive; }
	bool GetIsHitWaterFlow() { return isHitWaterFlow; }
private:
	//�������p�[�e�B�N���������邽�߂̕ϐ�
	static const int EMITTER_MAX = 1500;			//�ő��
	//���̏����擾
	Floor* floor_ = nullptr;

	float  waterFlowWidth;						//����
	float  waterFlowHeight;						//�c��
	Transform waterFlowTransform[EMITTER_MAX];	//���W
	float  waterFlowSpeed[EMITTER_MAX];			//���x
	int    waterFlowBright[EMITTER_MAX];		//���邳
	bool   waterFlowIsActive[EMITTER_MAX];		//�����Ă邩

	//�����̓����蔻��p
	Hit waterFlowHit;
	//����������
	bool isHitWaterFlow;
};

