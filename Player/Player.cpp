#include "Player.h"
#include "DxLib.h"
#include "Global.h"

Player::Player() {
	this->floor_ = new Floor();
	this->waterGimmick_ = new WaterGimmick();
}
Player::~Player() {
	delete floor_;
	delete waterGimmick_;
};

//������
void Player::MarioInitialize() {
	//��������
	floor_->Initialize();
	//�d�|��������
	waterGimmick_->Initialize();
	//�v���C���[���
	InitPlayer();
	//����
	InitWaterflow();
	//�A
	InitBubble();
}

void Player::SonicInitialize() {
	//��������
	floor_->Initialize();
	//�d�|��������
	waterGimmick_->Initialize();
	//�v���C���[���
	InitPlayer();

}

//�v���C���[���
void Player::InitPlayer()
{
	//�v���C���[��񏉊���
	this->playerTransform.x = 32.0f;
	this->playerTransform.y = 32.0f;
	this->playerTransform.radius = 16.0f;
	this->moveSpeed = 5.0f;

	this->isSwim = true;
	this->gravity = 6.0f;
	this->isAlive = true;
	this->aliveCount = 60 * 20;
}

//����
void Player::InitWaterflow()
{
	//����
	this->isHitWaterflow = false;
	for (int i = 0; i < waterGimmick_->GetEmitMax(); i++)
	{
		this->waterFlowHit.x = 0;
		this->waterFlowHit.y = 0;
		this->waterFlowHit.z = 0;
	}

}
//�A
void Player::InitBubble()
{

	//�A
	this->isHitBubble = false;

	this->bubbleHit.x = 0;
	this->bubbleHit.y = 0;
	this->bubbleHit.z = 0;
}

//�X�V
void Player::MarioUpdate(char* key, char* oldkey) {
	//�}���I���j��
	if (isAlive == true)
	{
		MarioSwim(key, oldkey);
		waterGimmick_->MarioUpdate(isHitBubble);
		//����
		WaterFlow();
		//�A
		Bubble();

	}
	else
	{
		Death(key, oldkey);
	}

	if (aliveCount <= 0)
	{
		aliveCount = 0;
		isAlive = false;
		isHitWaterflow = false;
	}
	aliveCount--;
}

//�\�j�b�N�X�V
void Player::SonicUpdate(char* key, char* oldkey) {
	//�\�j�b�N���j��
	if (isAlive == true)
	{
		SonicSwim(key, oldkey);
		waterGimmick_->SonicUpdate(isHitBubble);

		//�A
		Bubble();
	}
	else
	{
		Death(key, oldkey);
	}
	if (aliveCount <= 0)
	{
		aliveCount = 0;
		isAlive = false;
		isHitWaterflow = false;
	}
	aliveCount--;
}

void Player::SwimProperty(char* key, char* oldkey)
{
	//���A���[��������Ă�����
	if (key[KEY_INPUT_LEFT])
	{
		playerTransform.x -= moveSpeed;
	}
	//�E�A���[��������Ă�����
	if (key[KEY_INPUT_RIGHT])
	{
		playerTransform.x += moveSpeed;
	}

	//�j���ł����
	if (isSwim == true)
	{
		//�v���C���[�̍��W -= ����(�Œ�) - �d��(���X�ɏオ��)�@
		playerTransform.y -= buoyancy - gravity;
		//�d�͂͏��X�ɏオ��
		gravity += 0.2f;
	}
}
//�}���I���j��
void Player::MarioSwim(char* key, char* oldkey) {

	SwimProperty(key, oldkey);
	//�X�y�[�X�L�[���������u�ԉj��(�����痣��Ă�����)
	if (key[KEY_INPUT_SPACE] && !oldkey[KEY_INPUT_SPACE])
	{
		isSwim = true;
		//�d�͂�0�ɂȂ�
		gravity = 0.0f;
	}
	

	//�j���ł�Œ����ɑ���t������
	if (playerTransform.y >= floor_->getMarioFloorpos() - playerTransform.radius)
	{
		if (playerTransform.x > 400.0f && playerTransform.x < 800.0f)
		{
			if (playerTransform.x <= 400.0f + playerTransform.radius && isSwim == true)
			{
				playerTransform.x = 400.0f + playerTransform.radius;

			}
			else if (playerTransform.x >= 800.0f - playerTransform.radius && isSwim == true)
			{
				playerTransform.x = 800.0f - playerTransform.radius;
			}
			isSwim = true;
		}
		else
		{
			gravity = 6.0f;
			isSwim = false;
			playerTransform.y = floor_->getMarioFloorpos() - playerTransform.radius;
		}

	}
}
//�\�j�b�N���j��
void Player::SonicSwim(char* key, char* oldkey) {

	SwimProperty(key, oldkey);
	//�X�y�[�X�L�[���������u�ԉj��(�����痣��Ă�����)
	if (key[KEY_INPUT_SPACE] && !oldkey[KEY_INPUT_SPACE] && isSwim == false)
	{
		isSwim = true;
		//�d�͂�0�ɂȂ�
		gravity = 0.0f;
	}
	//�j���ł����
	if (isSwim == true)
	{
		//�v���C���[�̍��W -= ����(�Œ�) - �d��(���X�ɏオ��)�@
		playerTransform.y -= buoyancy - gravity;
		//�d�͂͏��X�ɏオ��
		gravity += 0.2f;
	}

	//�j���ł�Œ����ɑ���t������
	if (playerTransform.y >= floor_->getSonicFloorpos() - playerTransform.radius)
	{
		gravity = 6.0f;
		isSwim = false;
		playerTransform.y = floor_->getSonicFloorpos() - playerTransform.radius;
	}

}

//����
void Player::WaterFlow()
{
	for (int i = 0; i < waterGimmick_->GetEmitMax(); i++)
	{
		IsHitWaterFlow(waterGimmick_->GetWaterFlowTransform()[i], i);
	}

	//�����Ɉ��ݍ��܂ꂽ��
	if (isHitWaterflow == true)
	{
		playerTransform.x -= 2.0f;
		isHitWaterflow = false;
	}
}
//�����蔻��p�֐�
void Player::IsHitWaterFlow(Transform& transform, int num)
{
	//�������o�Ă�Ƃ�
	if (waterGimmick_->GetIsActiveWaterFlow()[num] == true)
	{
		waterFlowHit.x = playerTransform.x - transform.x;
		waterFlowHit.y = playerTransform.y - transform.y;
		waterFlowHit.z = waterFlowHit.x * waterFlowHit.x + waterFlowHit.y * waterFlowHit.y;
	}
	//�������Ă邩
	if (waterFlowHit.z <= (playerTransform.radius + transform.radius) *
		(playerTransform.radius + transform.radius))
	{
		isHitWaterflow = true;
	}

}

//�A
void Player::Bubble()
{
	waterGimmick_->IsHitBubble(playerTransform, isHitBubble);

	if (isHitBubble == true)
	{
		isHitBubble = false;
		aliveCount = 60 * 20;
	}
}

//���񂾂��Ƃ̏���
void Player::Death(char* key, char* oldkey) {

	if (key[KEY_INPUT_R] && !oldkey[KEY_INPUT_R])
	{
		playerTransform.x = 32.0f;
		playerTransform.y = 32.0f;
		playerTransform.radius = 16.0f;
		isSwim = true;
		isAlive = true;
		aliveCount = 60 * 20;

		isHitWaterflow = false;
		isHitBubble = false;
	}
}

void Player::Reset()
{
	//�v���C���[��񏉊���
	playerTransform.x = 32.0f;
	playerTransform.y = 32.0f;
	playerTransform.radius = 16.0f;
	moveSpeed = 5.0f;

	isSwim = true;
	gravity = 6.0f;
	isAlive = true;
	aliveCount = 60 * 20;

	isHitWaterflow = false;
	isHitBubble = false;
}

//�`��
void Player::DrawMario() {
	if (isAlive == true)
	{
		DrawMarioAlive();
	}
	else
	{
		DrawChoking();
	}

	DrawFormatString(0, 0, GetColor(0, 0, 0), "Life::%d", aliveCount);
}
void Player::DrawSonic() {
	if (isAlive == true)
	{
		DrawSonicAlive();
	}
	else
	{
		DrawChoking();
	}

	DrawFormatString(0, 0, GetColor(0, 0, 0), "Life::%d", aliveCount);
}

//�����Ă�Ƃ�
void Player::DrawMarioAlive()
{
	DrawBox(playerTransform.x - playerTransform.radius, playerTransform.y - playerTransform.radius,
		playerTransform.x + playerTransform.radius, playerTransform.y + playerTransform.radius,
		GetColor(255, 0, 0), TRUE);
	//���m�点
	DrawString(0, 30, "�A���[�ňړ��A�X�y�[�X�ŉj���܂����", GetColor(255, 255, 255));
}

//�����Ă�Ƃ�
void Player::DrawSonicAlive()
{
	DrawBox(playerTransform.x - playerTransform.radius, playerTransform.y - playerTransform.radius,
		playerTransform.x + playerTransform.radius, playerTransform.y + playerTransform.radius,
		GetColor(0, 255, 0), TRUE);
	//���m�点
	DrawString(0, 30, "�A���[�ňړ��A�X�y�[�X�ŉj���܂����", GetColor(255, 255, 255));
}

//������
void Player::DrawChoking()
{
	DrawBox(playerTransform.x - playerTransform.radius, playerTransform.y - playerTransform.radius,
		playerTransform.x + playerTransform.radius, playerTransform.y + playerTransform.radius,
		GetColor(255, 255, 255), TRUE);
	//���m�点
	DrawString(0, 30, "R�ŕ�����", GetColor(0, 0, 0));
}