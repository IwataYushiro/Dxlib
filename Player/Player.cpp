#include "Player.h"
#include "DxLib.h"

Player::Player(){
	
};
Player::~Player(){};

//èâä˙âª
void Player::Initialize() {
this->transform.x = 32.0f;
	this->transform.y = 32.0f;
	this->transform.radius = 16.0f;
	this->moveSpeed = 5.0f;
}
//çXêV
void Player::Update(char* key) {
	

	if (key[KEY_INPUT_LEFT])
	{
		transform.x -= moveSpeed;
	}
	if (key[KEY_INPUT_RIGHT])
	{
		transform.x += moveSpeed;
	}
}

//ï`âÊ
void Player::Draw() {
	DrawBox(transform.x-transform.radius, transform.y - transform.radius,
		transform.x + transform.radius, transform.y + transform.radius,
		GetColor(0, 255, 0), TRUE);
}