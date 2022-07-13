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

	this->transform.x = 32.0f;
	this->transform.y = 32.0f;
	this->transform.radius = 16.0f;
	this->moveSpeed = 5.0f;
	
	this->isSwim = true;
	this->gravity = 6.0f;
	this->isAlive = true;
	this->aliveCount = 60.0f * 20.0f;

	
}

//更新
void Player::Update(char* key, char* oldkey) {
	//マリオ風泳ぎ
	if (isAlive)
	{
		MarioSwim(key, oldkey);
	}
	else
	{
		Death(key, oldkey);

	}

	if (aliveCount <= 0.0f)
	{
		aliveCount = 0.0f;
		isAlive = false;
	}
	aliveCount--;
}

//マリオ風泳ぎ
void Player::MarioSwim(char* key, char* oldkey) {

	//左アローが押されていたら
	if (key[KEY_INPUT_LEFT])
	{
		transform.x -= moveSpeed;
	}
	//右アローが押されていたら
	if (key[KEY_INPUT_RIGHT])
	{
		transform.x += moveSpeed;
	}
	//水流に飲み込まれた時
	if (waterGimmick_->GetIsHitWaterflow() == true)
	{
		this->moveSpeed /= 2.0f;
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
		transform.y -= buoyancy - gravity;
		//重力は徐々に上がる
		gravity += 0.2f;
	}

	//泳いでる最中床に足を付けたら
	if (transform.y >= floor_->getFloorpos() - transform.radius && isSwim == true)
	{
		gravity = 6.0f;
		isSwim = false;
		transform.y = floor_->getFloorpos() - transform.radius;
	}
	//重力が10以上の場合
	if (gravity >= 10.0f)
	{
		//重力を固定する
		gravity = 10.0f;
	}
}
//死んだあとの処理
void Player::Death(char* key, char* oldkey) {

	if (key[KEY_INPUT_R] && !oldkey[KEY_INPUT_R])
	{
		transform.x = 32.0f;
		transform.y = 32.0f;
		transform.radius = 16.0f;
		isSwim = true;
		isAlive = true;
		aliveCount = 60.0f * 20.0f;
	}
}
//描画
void Player::Draw() {
	if (isAlive)
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
	DrawBox(transform.x - transform.radius, transform.y - transform.radius,
		transform.x + transform.radius, transform.y + transform.radius,
		GetColor(0, 255, 0), TRUE);
	//お知らせ
	DrawString(0, 30, "アローで移動、スペースで泳ぎますわよ", GetColor(255, 255, 255));
}
//窒息死
void Player::DrawChoking()
{
	DrawBox(transform.x - transform.radius, transform.y - transform.radius,
		transform.x + transform.radius, transform.y + transform.radius,
		GetColor(255, 0, 0), TRUE);
	//お知らせ
	DrawString(0, 30, "Rで復活よ", GetColor(0, 0, 0));
}