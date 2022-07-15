#include "Player.h"
#include "DxLib.h"
#include "Global.h"

Player::~Player() {
	delete floor_;
	delete waterGimmick_;
};

//������
void Player::Initialize() {
	//��������
	floor_ = new Floor();
	floor_->Initialize();

	//�d�|��������
	waterGimmick_ = new WaterGimmick();
	waterGimmick_->Initialize();

	//�v���C���[��񏉊���
	this->playerTransform.x = 32.0f;
	this->playerTransform.y = 32.0f;
	this->playerTransform.radius = 16.0f;
	this->moveSpeed = 5.0f;

	this->isSwim = true;
	this->gravity = 6.0f;
	this->isAlive = true;
	this->aliveCount = 60.0f * 20.0f;

	//����
	this->isHitWaterflow = false;
	for (int i = 0; i < waterGimmick_->GetEmitMax(); i++)
	{
		this->waterFlowHit.x = 0;
		this->waterFlowHit.y = 0;
		this->waterFlowHit.z = 0;
	}

	//�A
	this->isHitBubble = false;

	this->bubbleHit.x = 0;
	this->bubbleHit.y = 0;
	this->bubbleHit.z = 0;

}

//�X�V
void Player::Update(char* key, char* oldkey) {
	//�}���I���j��
	if (isAlive == true)
	{
		MarioSwim(key, oldkey);
		waterGimmick_->Update();

	}
	else
	{
		Death(key, oldkey);
	}

	//����
	WaterFlow();
	//�A
	Bubble();

	if (aliveCount <= 0.0f)
	{
		aliveCount = 0.0f;
		isAlive = false;
		isHitWaterflow = false;
	}
	aliveCount--;
}

//�}���I���j��
void Player::MarioSwim(char* key, char* oldkey) {

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
		playerTransform.y -= buoyancy - gravity;
		//�d�͂͏��X�ɏオ��
		gravity += 0.2f;
	}

	//�j���ł�Œ����ɑ���t������
	if (playerTransform.y >= floor_->getFloorpos() - playerTransform.radius && isSwim == true)
	{
		gravity = 6.0f;
		isSwim = false;
		playerTransform.y = floor_->getFloorpos() - playerTransform.radius;
	}
	//�d�͂�10�ȏ�̏ꍇ
	if (gravity >= 10.0f)
	{
		//�d�͂��Œ肷��
		gravity = 10.0f;
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
	IsHitBubble(playerTransform);

	if (isHitBubble==true)
	{
		isHitBubble = false;
		aliveCount += 400;
	}
}
//�����蔻��p�֐�
void Player::IsHitBubble(Transform transform)
{
	//�A���o�Ă�Ƃ�
	if (waterGimmick_->GetIsActiveBubble() == true)
	{
		bubbleHit.x = playerTransform.x - transform.x;
		bubbleHit.y = playerTransform.y - transform.y;
		bubbleHit.z = bubbleHit.x * bubbleHit.x + bubbleHit.y * bubbleHit.y;
	}
	//�������Ă邩
	if (bubbleHit.z <= (playerTransform.radius + transform.radius) *
		(playerTransform.radius + transform.radius))
	{
		isHitBubble = true;
		
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
		aliveCount = 60.0f * 20.0f;
		
		isHitWaterflow = false;
		isHitBubble = false;
	}
}
//�`��
void Player::Draw() {
	if (isAlive == true)
	{
		DrawAlive();
	}
	else
	{
		DrawChoking();
	}

	DrawFormatString(0, 0, GetColor(0, 0, 0), "Life::%f", aliveCount);
}
//�����Ă�Ƃ�
void Player::DrawAlive()
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
		GetColor(255, 0, 0), TRUE);
	//���m�点
	DrawString(0, 30, "R�ŕ�����", GetColor(0, 0, 0));
}