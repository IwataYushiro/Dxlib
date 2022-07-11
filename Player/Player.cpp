#include "Player.h"
#include "DxLib.h"
#include "Global.h"

Player::Player() {

	srand(time(NULL));

};
Player::~Player() {};

//初期化
void Player::Initialize() {
	this->transform.x = 32.0f;
	this->transform.y = 32.0f;
	this->transform.radius = 16.0f;
	this->moveSpeed = 5.0f;
	this->floorPos = WIN_HEIGHT - 100.0f;
	this->isSwim = true;
	this->gravity = 6.0f;
	this->isAlive = true;
	this->aliveCount = 60.0f * 20.0f;
	this->bublleCount = 60.0f * 4.0f;
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
	
	if (aliveCount<=0)
	{
		aliveCount = 0;
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
	if (transform.y >= floorPos - transform.radius && isSwim == true)
	{
		gravity = 6.0f;
		isSwim = false;
		transform.y = floorPos - transform.radius;
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

	if (key[KEY_INPUT_R]&& !oldkey[KEY_INPUT_R])
	{
		transform.x = 32.0f;
		transform.y = 32.0f;
		transform.radius = 16.0f;
		isSwim = true;
		isAlive = true;
		aliveCount = 60.0f * 20.0f;
		bublleCount = 60.0f * 4.0f;
	}
}
//描画
void Player::Draw() {
	if (isAlive)
	{
		DrawBox(transform.x - transform.radius, transform.y - transform.radius,
			transform.x + transform.radius, transform.y + transform.radius,
			GetColor(0, 255, 0), TRUE);
	}
	else
	{
		DrawBox(transform.x - transform.radius, transform.y - transform.radius,
			transform.x + transform.radius, transform.y + transform.radius,
			GetColor(255, 0, 0), TRUE);
	}
	DrawFormatString(0, 0, GetColor(0, 0, 0), "Life::%f", aliveCount);
}