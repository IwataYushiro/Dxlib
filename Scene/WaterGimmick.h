#pragma once
#include "Floor.h"
#include "Hit.h"
#include "Global.h"
#include "Player.h"
#include "Transform.h"

#include <stdlib.h>
#include <time.h>

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
	//�A�X�V
	void UpdateBubble();
	//�`��
	void Draw();
	//�����`��
	void DrawWaterFlow(int num);

	//�A�N�Z�b�T
	bool GetIsHitWaterflow() { return isHitWaterflow; }
private:

	//���̏����擾
	Floor* floor_ = nullptr;

	//�v���C���[���
	//Player* player_ = nullptr;

	//�������p�[�e�B�N���������邽�߂̕ϐ�
	static const int EMITTER_MAX = 1500;			//�ő��

	float  waterFlowWidth;						//����
	float  waterFlowHeight;						//�c��
	float  waterFlowPosX[EMITTER_MAX];			//X���W
	float  waterFlowPosY[EMITTER_MAX];			//Y���W
	float  waterFlowRadius[EMITTER_MAX];		//�����A�̔��a
	float  waterFlowSpeed[EMITTER_MAX];			//���x
	int    waterFlowBright[EMITTER_MAX];		//���邳
	bool   waterFlowIsActive[EMITTER_MAX];		//�����Ă邩

	//�����̓����蔻��p
	Hit waterFlowHit;
	//����������
	bool isHitWaterflow;
};

