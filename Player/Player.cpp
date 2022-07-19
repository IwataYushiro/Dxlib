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

//初期化
void Player::MarioInitialize() {
	//床初期化
	floor_->Initialize();
	//仕掛け初期化
	waterGimmick_->Initialize();
	//プレイヤー情報
	InitPlayer();
	//水流
	InitWaterflow();
	//泡
	InitBubble();
}

void Player::SonicInitialize() {
	//床初期化
	floor_->Initialize();
	//仕掛け初期化
	waterGimmick_->Initialize();
	//プレイヤー情報
	InitPlayer();

}

//プレイヤー情報
void Player::InitPlayer()
{
	//プレイヤー情報初期化
	this->playerTransform.x = 32.0f;
	this->playerTransform.y = 32.0f;
	this->playerTransform.radius = 16.0f;
	this->moveSpeed = 5.0f;

	this->isSwim = true;
	this->gravity = 6.0f;
	this->isAlive = true;
	this->aliveCount = 60 * 20;
}

//水流
void Player::InitWaterflow()
{
	//水流
	this->isHitWaterflow = false;
	for (int i = 0; i < waterGimmick_->GetEmitMax(); i++)
	{
		this->waterFlowHit.x = 0;
		this->waterFlowHit.y = 0;
		this->waterFlowHit.z = 0;
	}

}
//泡
void Player::InitBubble()
{

	//泡
	this->isHitBubble = false;

	this->bubbleHit.x = 0;
	this->bubbleHit.y = 0;
	this->bubbleHit.z = 0;
}

//更新
void Player::MarioUpdate(char* key, char* oldkey) {
	//マリオ風泳ぎ
	if (isAlive == true)
	{
		MarioSwim(key, oldkey);
		waterGimmick_->MarioUpdate(isHitBubble);
		//水流
		WaterFlow();
		//泡
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

//ソニック更新
void Player::SonicUpdate(char* key, char* oldkey) {
	//ソニック風泳ぎ
	if (isAlive == true)
	{
		SonicSwim(key, oldkey);
		waterGimmick_->SonicUpdate(isHitBubble);

		//泡
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
	//左アローが押されていたら
	if (key[KEY_INPUT_LEFT])
	{
		playerTransform.x -= moveSpeed;
	}
	//右アローが押されていたら
	if (key[KEY_INPUT_RIGHT])
	{
		playerTransform.x += moveSpeed;
	}

	//泳いでいる間
	if (isSwim == true)
	{
		//プレイヤーの座標 -= 浮力(固定) - 重力(徐々に上がる)　
		playerTransform.y -= buoyancy - gravity;
		//重力は徐々に上がる
		gravity += 0.2f;
	}
}
//マリオ風泳ぎ
void Player::MarioSwim(char* key, char* oldkey) {

	SwimProperty(key, oldkey);
	//スペースキーを押した瞬間泳ぐ(床から離れている状態)
	if (key[KEY_INPUT_SPACE] && !oldkey[KEY_INPUT_SPACE])
	{
		isSwim = true;
		//重力が0になる
		gravity = 0.0f;
	}
	

	//泳いでる最中床に足を付けたら
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
//ソニック風泳ぎ
void Player::SonicSwim(char* key, char* oldkey) {

	SwimProperty(key, oldkey);
	//スペースキーを押した瞬間泳ぐ(床から離れている状態)
	if (key[KEY_INPUT_SPACE] && !oldkey[KEY_INPUT_SPACE] && isSwim == false)
	{
		isSwim = true;
		//重力が0になる
		gravity = 0.0f;
	}
	//泳いでいる間
	if (isSwim == true)
	{
		//プレイヤーの座標 -= 浮力(固定) - 重力(徐々に上がる)　
		playerTransform.y -= buoyancy - gravity;
		//重力は徐々に上がる
		gravity += 0.2f;
	}

	//泳いでる最中床に足を付けたら
	if (playerTransform.y >= floor_->getSonicFloorpos() - playerTransform.radius)
	{
		gravity = 6.0f;
		isSwim = false;
		playerTransform.y = floor_->getSonicFloorpos() - playerTransform.radius;
	}

}

//水流
void Player::WaterFlow()
{
	for (int i = 0; i < waterGimmick_->GetEmitMax(); i++)
	{
		IsHitWaterFlow(waterGimmick_->GetWaterFlowTransform()[i], i);
	}

	//水流に飲み込まれた時
	if (isHitWaterflow == true)
	{
		playerTransform.x -= 2.0f;
		isHitWaterflow = false;
	}
}
//当たり判定用関数
void Player::IsHitWaterFlow(Transform& transform, int num)
{
	//水流が出てるとき
	if (waterGimmick_->GetIsActiveWaterFlow()[num] == true)
	{
		waterFlowHit.x = playerTransform.x - transform.x;
		waterFlowHit.y = playerTransform.y - transform.y;
		waterFlowHit.z = waterFlowHit.x * waterFlowHit.x + waterFlowHit.y * waterFlowHit.y;
	}
	//当たってるか
	if (waterFlowHit.z <= (playerTransform.radius + transform.radius) *
		(playerTransform.radius + transform.radius))
	{
		isHitWaterflow = true;
	}

}

//泡
void Player::Bubble()
{
	waterGimmick_->IsHitBubble(playerTransform, isHitBubble);

	if (isHitBubble == true)
	{
		isHitBubble = false;
		aliveCount = 60 * 20;
	}
}

//死んだあとの処理
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
	//プレイヤー情報初期化
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

//描画
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

//生きてるとき
void Player::DrawMarioAlive()
{
	DrawBox(playerTransform.x - playerTransform.radius, playerTransform.y - playerTransform.radius,
		playerTransform.x + playerTransform.radius, playerTransform.y + playerTransform.radius,
		GetColor(255, 0, 0), TRUE);
	//お知らせ
	DrawString(0, 30, "アローで移動、スペースで泳ぎますわよ", GetColor(255, 255, 255));
}

//生きてるとき
void Player::DrawSonicAlive()
{
	DrawBox(playerTransform.x - playerTransform.radius, playerTransform.y - playerTransform.radius,
		playerTransform.x + playerTransform.radius, playerTransform.y + playerTransform.radius,
		GetColor(0, 255, 0), TRUE);
	//お知らせ
	DrawString(0, 30, "アローで移動、スペースで泳ぎますわよ", GetColor(255, 255, 255));
}

//窒息死
void Player::DrawChoking()
{
	DrawBox(playerTransform.x - playerTransform.radius, playerTransform.y - playerTransform.radius,
		playerTransform.x + playerTransform.radius, playerTransform.y + playerTransform.radius,
		GetColor(255, 255, 255), TRUE);
	//お知らせ
	DrawString(0, 30, "Rで復活よ", GetColor(0, 0, 0));
}