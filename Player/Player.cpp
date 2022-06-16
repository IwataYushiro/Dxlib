#include "Player.h"
#include "DxLib.h"
#include "Global.h"

Player::Player() {

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
}

//更新
void Player::Update(char* key, char* oldkey) {
	//マリオ風泳ぎ
	MarioSwim(key, oldkey);
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
		transform.y = floorPos - 100.0f - transform.radius;
	}
	//重力が10以上の場合
	if (gravity >= 10.0f)
	{
		//重力を固定する
		gravity = 10.0f;
	}
}

//描画
void Player::Draw() {
	DrawBox(transform.x - transform.radius, transform.y - transform.radius,
		transform.x + transform.radius, transform.y + transform.radius,
		GetColor(0, 255, 0), TRUE);
}