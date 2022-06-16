#pragma once
#include "Player.h"

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

	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	//�v���C���[���
	Player* player_ = nullptr;

};

