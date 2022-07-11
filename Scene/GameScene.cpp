#include "GameScene.h"
#include "DxLib.h"
#include "Global.h"
GameScene::GameScene()
{

}

GameScene::~GameScene()
{
	delete player_;
	delete waterGimmick_;
}

//������
void GameScene::Initialize() {
	player_ = new Player();
	player_->Initialize();
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
}
//�`��
void GameScene::Draw() {
	player_->Draw();
	//����`��
	DrawFloor();
}
//����`��
void GameScene::DrawFloor() {
	//����`��
	DrawBox(0, player_->getFloorpos(), WIN_WIDTH, WIN_HEIGHT, GetColor(31, 30, 51), true);
}
