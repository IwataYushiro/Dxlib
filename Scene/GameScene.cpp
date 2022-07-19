#include "GameScene.h"
#include "DxLib.h"

GameScene::GameScene()
{
	player_ = new Player();
	floor_ = new Floor();
	waterGimmick_ = new WaterGimmick();

}

GameScene::~GameScene()
{
	delete floor_;
	delete player_;
	delete waterGimmick_;
}

//������
void GameScene::Initialize() {

	floor_->Initialize();
	waterGimmick_->Initialize();
	playerJump = mario;

	switch (playerJump)
	{
	case mario:
		player_->MarioInitialize();
		break;
	case sonic:
		player_->SonicInitialize();
		break;
	}

}
//�X�V
void GameScene::Update() {

	// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
	for (int i = 0; i < 256; ++i)
	{
		oldkeys[i] = keys[i];
	}
	// �ŐV�̃L�[�{�[�h�����擾
	GetHitKeyStateAll(keys);

	// ��ʃN���A
	ClearDrawScreen();

	//�X�V����
	switch (playerJump)
	{
	case mario:
		player_->MarioUpdate(keys, oldkeys);
		//�d�|��
		waterGimmick_->MarioUpdate(player_->GetIsHitBubble());
		if (keys[KEY_INPUT_1] && !oldkeys[KEY_INPUT_1])
		{
			player_->Reset();
			playerJump = sonic;
			break;
		}

	case sonic:
		player_->SonicUpdate(keys, oldkeys);
		//�d�|��
		waterGimmick_->SonicUpdate(player_->GetIsHitBubble());
		if (keys[KEY_INPUT_1] && !oldkeys[KEY_INPUT_1])
		{
			player_->Reset();
			playerJump = mario;
			break;
		}
	}

}

//�`��
void GameScene::Draw() {


	switch (playerJump)
	{

	case mario:
		//�d�|��
		waterGimmick_->MarioDraw();
		// �����܂�
		//�v���C���[�`��
		player_->DrawMario();
		//����`��
		floor_->DrawMarioFloor();
		DrawString(0, 150, "mario", GetColor(255, 0, 0));
		break;

	case sonic:
		//�d�|��
		waterGimmick_->SonicDraw();
		// �����܂�
		//�v���C���[�`��
		player_->DrawSonic();
		//����`��
		floor_->DrawSonicFloor();

		DrawString(0, 150, "sonic", GetColor(0, 255, 0));
		break;
	
	}

}
