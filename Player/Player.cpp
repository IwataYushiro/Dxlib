#include "Player.h"
#include "DxLib.h"
#include "Global.h"

Player::Player() {

};
Player::~Player() {};

//‰Šú‰»
void Player::Initialize() {
	this->transform.x = 32.0f;
	this->transform.y = 32.0f;
	this->transform.radius = 16.0f;
	this->moveSpeed = 5.0f;
	this->isSwim = true;
	this->swimPower = 6.0f;
	this->gravity = 6.0f;
}
//XV
void Player::Update(char* key, char* oldkey) {


	if (key[KEY_INPUT_LEFT])
	{
		transform.x -= moveSpeed;
	}
	if (key[KEY_INPUT_RIGHT])
	{
		transform.x += moveSpeed;
	}

	if (key[KEY_INPUT_SPACE] && !oldkey[KEY_INPUT_SPACE])
	{
		isSwim = true;
		gravity = 0.0f;
	}
	if (isSwim == true)
	{
		transform.y -= swimPower - gravity;
		gravity += 0.2f;
	}
	if (transform.y >= WIN_HEIGHT - 100.0f - transform.radius && isSwim == true)
	{
		gravity = 8.0f;
		isSwim = false;
		transform.y = WIN_HEIGHT - 100.0f - transform.radius;
	}
	if (gravity >= 10.0f)
	{
		gravity = 10.0f;
	}
}

//•`‰æ
void Player::Draw() {
	DrawBox(transform.x - transform.radius, transform.y - transform.radius,
		transform.x + transform.radius, transform.y + transform.radius,
		GetColor(0, 255, 0), TRUE);
}