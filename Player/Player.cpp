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
void Player::Initialize() {
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

//�v���C���[���
void Player::InitPlayer()
{
	for (int i = 0; i < jumpLength; i++)
	{
		//�v���C���[��񏉊���
		this->playerTransform[i].x = 32.0f;
		this->playerTransform[i].y = 32.0f;
		this->playerTransform[i].radius = 16.0f;
		this->moveSpeed[i] = 5.0f;

		this->isSwim[i] = true;
		this->isAlive[i] = true;
		this->aliveCount[i] = 60 * 20;
	}
	this->gravity[0] = 6.0f;
	this->gravity[1] = 10.0f;

}

//����
void Player::InitWaterflow()
{
	//����
	this->isHitWaterflow = false;
	/*for (int i = 0; i < waterGimmick_->GetEmitMax(); i++)
	{*/
	this->waterFlowHit.x = 0.0f;
	this->waterFlowHit.y = 0.0f;
	this->waterFlowHit.z = 0.0f;
	//}

}
//�A
void Player::InitBubble()
{
	for (int i = 0; i < jumpLength; i++)
	{
		//�A
		this->isHitBubble[i] = false;

		this->bubbleHit[i].x = 0.0f;
		this->bubbleHit[i].y = 0.0f;
		this->bubbleHit[i].z = 0.0f;
	}
}

//�X�V
void Player::MarioUpdate(char* key, char* oldkey) {
	//�}���I���j��
	if (isAlive[0] == true)
	{
		MarioSwim(key, oldkey);
		waterGimmick_->MarioUpdate(isHitBubble[0]);
		//����
		WaterFlow();
		//�A
		BubbleMario();

	}
	else
	{
		DeathMario(key, oldkey);
	}

	if (aliveCount[0] <= 0 || playerTransform[0].y > WIN_HEIGHT + playerTransform[0].radius)
	{
		aliveCount[0] = 0;
		isAlive[0] = false;
		isHitWaterflow = false;
	}
	aliveCount[0]--;
}

//�\�j�b�N�X�V
void Player::SonicUpdate(char* key, char* oldkey) {
	//�\�j�b�N���j��
	if (isAlive[1] == true)
	{
		SonicSwim(key, oldkey);
		waterGimmick_->SonicUpdate(isHitBubble[1]);

		//�A
		BubbleSonic();
	}
	else
	{
		DeathSonic(key, oldkey);
	}

	if (aliveCount[1] <= 0 || playerTransform[1].y > WIN_HEIGHT + playerTransform[1].radius)
	{
		aliveCount[1] = 0;
		isAlive[1] = false;
		isHitWaterflow = false;
	}
	aliveCount[1]--;
}

//�}���I���j��
void Player::MarioSwim(char* key, char* oldkey) {


	//���A���[��������Ă�����
	if (key[KEY_INPUT_LEFT])
	{
		playerTransform[mario].x -= moveSpeed[mario];
	}
	//�E�A���[��������Ă�����
	if (key[KEY_INPUT_RIGHT])
	{
		playerTransform[mario].x += moveSpeed[mario];
	}
	//�X�y�[�X�L�[���������u�ԉj��(�����痣��Ă�����)
	if (key[KEY_INPUT_SPACE] && !oldkey[KEY_INPUT_SPACE])
	{
		isSwim[0] = true;
		//�d�͂�0�ɂȂ�
		gravity[0] = 0.0f;
	}

	//�j���ł����
	if (isSwim[0] == true)
	{
		//�v���C���[�̍��W -= ����(�Œ�) - �d��(���X�ɏオ��)�@
		playerTransform[0].y -= buoyancy[0] - gravity[0];
		//�d�͂͏��X�ɏオ��
		gravity[0] += 0.2f;
	}
	if (gravity[0] >= 10.0f)
	{
		gravity[0] = 10.0f;
	}
	//�j���ł�Œ����ɑ���t������
	if (playerTransform[0].y >= floor_->getMarioFloorpos() - playerTransform[0].radius)
	{
		if (playerTransform[0].x > 400.0f && playerTransform[0].x < 800.0f)
		{
			if (playerTransform[0].x <= 400.0f + playerTransform[0].radius && isSwim[0] == true)
			{
				playerTransform[0].x = 400.0f + playerTransform[0].radius;

			}
			else if (playerTransform[0].x >= 800.0f - playerTransform[0].radius && isSwim[0] == true)
			{
				playerTransform[0].x = 800.0f - playerTransform[0].radius;
			}
			isSwim[0] = true;
		}
		else
		{
			gravity[0] = 6.0f;
			isSwim[0] = false;
			playerTransform[0].y = floor_->getMarioFloorpos() - playerTransform[0].radius;
		}

	}
}
//�\�j�b�N���j��
void Player::SonicSwim(char* key, char* oldkey) {


	//���A���[��������Ă�����
	if (key[KEY_INPUT_LEFT])
	{
		playerTransform[1].x -= moveSpeed[1];
	}
	//�E�A���[��������Ă�����
	if (key[KEY_INPUT_RIGHT])
	{
		playerTransform[1].x += moveSpeed[1];
	}

	//�X�y�[�X�L�[���������u�ԉj��(�����痣��Ă�����)
	if (key[KEY_INPUT_SPACE] && !oldkey[KEY_INPUT_SPACE] && isSwim[1] == false)
	{
		isSwim[1] = true;
		//�d�͂�0�ɂȂ�
		gravity[1] = 0.0f;
	}
	//�j���ł����
	if (isSwim[1] == true)
	{
		//�v���C���[�̍��W -= ����(�Œ�) - �d��(���X�ɏオ��)�@
		playerTransform[1].y -= buoyancy[1] - gravity[1];
		//�d�͂͏��X�ɏオ��
		gravity[1] += 0.2f;
	}
	if (gravity[0] >= 15.0f)
	{
		gravity[0] = 15.0f;
	}
	//�j���ł�Œ����ɑ���t������
	if (playerTransform[1].y >= floor_->getSonicFloorpos() - playerTransform[1].radius)
	{
		if (playerTransform[1].x > 700.0f)
		{
			if (playerTransform[1].x <= 700.0f + playerTransform[1].radius && isSwim[1] == true)
			{
				playerTransform[1].x = 700.0f + playerTransform[1].radius;
			}
			isSwim[1] = true;
		}
		else
		{
			gravity[1] = 10.0f;
			isSwim[1] = false;
			playerTransform[1].y = floor_->getSonicFloorpos() - playerTransform[1].radius;
		}

	}

}

//����
void Player::WaterFlow()
{
	for (int i = 0; i < waterGimmick_->GetWaterFlowEmitMax(); i++)
	{
		IsHitWaterFlow(waterGimmick_->GetWaterFlowTransform()[i], i);
	}

	for (int i = 0; i < jumpLength; i++)
	{
		//�����Ɉ��ݍ��܂ꂽ��
		if (isHitWaterflow == true)
		{
			playerTransform[i].x -= 2.0f;
			isHitWaterflow = false;
		}
	}

}
//�����蔻��p�֐�
void Player::IsHitWaterFlow(Transform& transform, int num)
{
	//�������o�Ă�Ƃ�
	for (int i = 0; i < jumpLength; i++)
	{
		if (waterGimmick_->GetIsActiveWaterFlow()[num] == true)
		{
			waterFlowHit.x = playerTransform[i].x - transform.x;
			waterFlowHit.y = playerTransform[i].y - transform.y;
			waterFlowHit.z = waterFlowHit.x * waterFlowHit.x + waterFlowHit.y * waterFlowHit.y;
		}
		//�������Ă邩
		if (waterFlowHit.z <= (playerTransform[i].radius + transform.radius) *
			(playerTransform[i].radius + transform.radius))
		{
			isHitWaterflow = true;
		}
	}
}

//�A
void Player::BubbleMario()
{
	waterGimmick_->IsHitBubbleMario(playerTransform[0], isHitBubble[0]);

	if (isHitBubble[0] == true)
	{
		isHitBubble[0] = false;
		aliveCount[0] = 60 * 20;
	}
}
void Player::BubbleSonic()
{
	waterGimmick_->IsHitBubbleSonic(playerTransform[1], isHitBubble[1]);

	if (isHitBubble[1] == true)
	{
		isHitBubble[1] = false;
		aliveCount[1] = 60 * 20;
	}
}

//���񂾂��Ƃ̏���
void Player::DeathMario(char* key, char* oldkey) {

	if (key[KEY_INPUT_R] && !oldkey[KEY_INPUT_R])
	{
		playerTransform[0].x = 32.0f;
		playerTransform[0].y = 32.0f;
		playerTransform[0].radius = 16.0f;
		isSwim[0] = true;
		isAlive[0] = true;
		aliveCount[0] = 60 * 20;

		isHitWaterflow = false;
		isHitBubble[0] = false;


	}
}

void Player::DeathSonic(char* key, char* oldkey) {

	if (key[KEY_INPUT_R] && !oldkey[KEY_INPUT_R])
	{
		playerTransform[1].x = 32.0f;
		playerTransform[1].y = 32.0f;
		playerTransform[1].radius = 16.0f;
		isSwim[1] = true;
		isAlive[1] = true;
		aliveCount[1] = 60 * 20;

		isHitBubble[1] = false;
	}
}

void Player::Reset()
{
	for (int i = 0; i < jumpLength; i++)
	{
		//�v���C���[��񏉊���
		playerTransform[i].x = 32.0f;
		playerTransform[i].y = 32.0f;
		playerTransform[i].radius = 16.0f;
		moveSpeed[i] = 5.0f;
		aliveCount[i] = 60 * 20;

		isSwim[i] = true;
		gravity[0] = 6.0f;
		gravity[1] = 10.0f;
		isAlive[i] = true;
		isHitWaterflow = false;
		isHitBubble[i] = false;
	}

}

//�`��
void Player::DrawMario() {
	if (isAlive[0] == true)
	{
		DrawMarioAlive();
	}
	else
	{
		DrawMarioChoking();
	}

	DrawFormatString(0, 0, GetColor(0, 0, 0), "Life::%d", aliveCount[0]);
}
void Player::DrawSonic() {
	if (isAlive[1] == true)
	{
		DrawSonicAlive();
	}
	else
	{
		DrawSonicChoking();
	}

	DrawFormatString(0, 0, GetColor(0, 0, 0), "Life::%d", aliveCount[1]);
}

//�����Ă�Ƃ�
void Player::DrawMarioAlive()
{
	DrawBox(playerTransform[0].x - playerTransform[0].radius, playerTransform[0].y - playerTransform[0].radius,
		playerTransform[0].x + playerTransform[0].radius, playerTransform[0].y + playerTransform[0].radius,
		GetColor(255, 0, 0), TRUE);
	//���m�点
	DrawString(0, 30, "�A���[�ňړ��A�X�y�[�X�ŉj���܂����", GetColor(255, 255, 255));
}

//�����Ă�Ƃ�
void Player::DrawSonicAlive()
{
	DrawBox(playerTransform[1].x - playerTransform[1].radius, playerTransform[1].y - playerTransform[1].radius,
		playerTransform[1].x + playerTransform[1].radius, playerTransform[1].y + playerTransform[1].radius,
		GetColor(0, 255, 0), TRUE);
	//���m�点
	DrawString(0, 30, "�A���[�ňړ��A�X�y�[�X�ŉj���܂����", GetColor(255, 255, 255));
}

//������
void Player::DrawMarioChoking()
{
	DrawBox(playerTransform[0].x - playerTransform[0].radius, playerTransform[0].y - playerTransform[0].radius,
		playerTransform[0].x + playerTransform[0].radius, playerTransform[0].y + playerTransform[0].radius,
		GetColor(255, 255, 255), TRUE);
	//���m�点
	DrawString(0, 30, "R�ŕ�����", GetColor(0, 0, 0));
}

void Player::DrawSonicChoking()
{
	DrawBox(playerTransform[1].x - playerTransform[1].radius, playerTransform[1].y - playerTransform[1].radius,
		playerTransform[1].x + playerTransform[1].radius, playerTransform[1].y + playerTransform[1].radius,
		GetColor(255, 255, 255), TRUE);
	//���m�点
	DrawString(0, 30, "R�ŕ�����", GetColor(0, 0, 0));
}