#pragma once
#include "Floor.h"
#include "Global.h"
#include "Player.h"
#include "WaterGimmick.h"

class GameScene
{
public:
	GameScene();
	~GameScene();

	//������
	void Initialize();
	//�X�V
	void Update();
	//�`��
	void Draw();

private:
	
	int playerJump;

	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	//���`��
	Floor* floor_ = nullptr;
	//�v���C���[���
	Player* player_ = nullptr;
	//�����M�~�b�N���
	WaterGimmick* waterGimmick_ = nullptr;

	
};

