#include "Player.h"
#include "DxLib.h"
#include "Global.h"

Player::Player() {

};
Player::~Player() {};

//������
void Player::Initialize() {
	this->transform.x = 32.0f;
	this->transform.y = 32.0f;
	this->transform.radius = 16.0f;
	this->moveSpeed = 5.0f;
	this->floorPos = WIN_HEIGHT - 100.0f;
	this->isSwim = true;
	this->gravity = 6.0f;
}

//�X�V
void Player::Update(char* key, char* oldkey) {
	//�}���I���j��
	MarioSwim(key, oldkey);
}

//�}���I���j��
void Player::MarioSwim(char* key, char* oldkey) {

	//���A���[��������Ă�����
	if (key[KEY_INPUT_LEFT])
	{
		transform.x -= moveSpeed;
	}
	//�E�A���[��������Ă�����
	if (key[KEY_INPUT_RIGHT])
	{
		transform.x += moveSpeed;
	}
	//�X�y�[�X�L�[���������u�ԉj��(�����痣��Ă�����)
	if (key[KEY_INPUT_SPACE] && !oldkey[KEY_INPUT_SPACE])
	{
		isSwim = true;
		//�d�͂�0�ɂȂ�
		gravity = 0.0f;
	}
	//�j���ł����
	if (isSwim == true)
	{
		//�v���C���[�̍��W -= ����(�Œ�) - �d��(���X�ɏオ��)�@
		transform.y -= buoyancy - gravity;
		//�d�͂͏��X�ɏオ��
		gravity += 0.2f;
	}

	//�j���ł�Œ����ɑ���t������
	if (transform.y >= floorPos - transform.radius && isSwim == true)
	{
		gravity = 6.0f;
		isSwim = false;
		transform.y = floorPos - 100.0f - transform.radius;
	}
	//�d�͂�10�ȏ�̏ꍇ
	if (gravity >= 10.0f)
	{
		//�d�͂��Œ肷��
		gravity = 10.0f;
	}
}

//�`��
void Player::Draw() {
	DrawBox(transform.x - transform.radius, transform.y - transform.radius,
		transform.x + transform.radius, transform.y + transform.radius,
		GetColor(0, 255, 0), TRUE);
}