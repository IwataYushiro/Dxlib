#include "Player.h"
#include "DxLib.h"
#include "Global.h"

Player::~Player() {
	delete floor_;
	delete waterGimmick_;
};

//初期化
void Player::Initialize() {
	//床初期化
	floor_ = new Floor();
	floor_->Initialize();

	//仕掛け初期化
	waterGimmick_ = new WaterGimmick();
	waterGimmick_->Initialize();

	//プレイヤー情報初期化
	this->playerTransform.x = 32.0f;
	this->playerTransform.y = 32.0f;
	this->playerTransform.radius = 16.0f;
	this->moveSpeed = 5.0f;

	this->isSwim = true;
	this->gravity = 6.0f;
	this->isAlive = true;
	this->aliveCount = 60.0f * 20.0f;
	this->isHitWaterflow = false;

	for (int i = 0; i < waterGimmick_->GetEmitMax(); i++)
	{
		this->playerWaterFlowHit.x = 0;
		this->playerWaterFlowHit.y = 0;
		this->playerWaterFlowHit.z = 0;
	}
}

//更新
void Player::Update(char* key, char* oldkey) {
	//マリオ風泳ぎ
	if (isAlive == true)
	{
		MarioSwim(key, oldkey);
		waterGimmick_->Update();

	}
	else
	{
		Death(key, oldkey);

	}
	//水流
	WaterFlow();

	if (aliveCount <= 0.0f)
	{
		aliveCount = 0.0f;
		isAlive = false;
		isHitWaterflow = false;
	}
	aliveCount--;
}

//マリオ風泳ぎ
void Player::MarioSwim(char* key, char* oldkey) {

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

	//スペースキーを押した瞬間泳ぐ(床から離れている状態)
	if (key[KEY_INPUT_SPACE] && !oldkey[KEY_INPUT_SPACE])
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
	if (playerTransform.y >= floor_->getFloorpos() - playerTransform.radius && isSwim == true)
	{
		gravity = 6.0f;
		isSwim = false;
		playerTransform.y = floor_->getFloorpos() - playerTransform.radius;
	}
	//重力が10以上の場合
	if (gravity >= 10.0f)
	{
		//重力を固定する
		gravity = 10.0f;
	}
}

void Player::IsHitWaterFlow(Transform& transform, int num)
{
	//水流が出てるとき
	if (waterGimmick_->GetIsActiveWaterFlow()[num] == true)
	{
		playerWaterFlowHit.x = playerTransform.x - transform.x;
		playerWaterFlowHit.y = playerTransform.y - transform.y;
		playerWaterFlowHit.z = playerWaterFlowHit.x * playerWaterFlowHit.x + playerWaterFlowHit.y * playerWaterFlowHit.y;
	}
	//当たってるか
	if (playerWaterFlowHit.z <= (playerTransform.radius + transform.radius) *
		(playerTransform.radius + transform.radius))
	{
		isHitWaterflow = true;
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

//死んだあとの処理
void Player::Death(char* key, char* oldkey) {

	if (key[KEY_INPUT_R] && !oldkey[KEY_INPUT_R])
	{
		playerTransform.x = 32.0f;
		playerTransform.y = 32.0f;
		playerTransform.radius = 16.0f;
		isSwim = true;
		isAlive = true;
		isHitWaterflow = false;
		aliveCount = 60.0f * 20.0f;
	}
}
//描画
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
//生きてるとき
void Player::DrawAlive()
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
		GetColor(255, 0, 0), TRUE);
	//お知らせ
	DrawString(0, 30, "Rで復活よ", GetColor(0, 0, 0));
}