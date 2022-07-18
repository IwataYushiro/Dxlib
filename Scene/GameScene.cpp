#include "GameScene.h"
#include "DxLib.h"

GameScene::GameScene()
{
	
}

GameScene::~GameScene()
{
	delete floor_;
	delete player_;
	delete waterGimmick_;
}

//������
void GameScene::Initialize() {
	floor_ = new Floor();
	floor_->Initialize();

	player_ = new Player();
	player_->Initialize();

	waterGimmick_ = new WaterGimmick();
	waterGimmick_->Initialize();
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
	player_->Update(keys, oldkeys);
	//�d�|��
	waterGimmick_->Update(player_->GetIsHitBubble());
}

//�`��
void GameScene::Draw() {
	//�v���C���[�`��
	player_->Draw();
	//�d�|��
	waterGimmick_->Draw();
	// �����܂�
	
	//����`��
	floor_->DrawFloor();
}
