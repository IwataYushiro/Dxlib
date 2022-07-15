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

	//水流
	this->isHitWaterflow = false;
	for (int i = 0; i < waterGimmick_->GetEmitMax(); i++)
	{
		this->waterFlowHit.x = 0;
		this->waterFlowHit.y = 0;
		this->waterFlowHit.z = 0;
	}

	//泡
	this->isHitBubble = false;

	this->bubbleHit.x = 0;
	this->bubbleHit.y = 0;
	this->bubbleHit.z = 0;

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
	//泡
	Bubble();

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
	IsHitBubble(playerTransform);

	if (isHitBubble==true)
	{
		isHitBubble = false;
		aliveCount += 400;
	}
}
//当たり判定用関数
void Player::IsHitBubble(Transform transform)
{
	//泡が出てるとき
	if (waterGimmick_->GetIsActiveBubble() == true)
	{
		bubbleHit.x = playerTransform.x - transform.x;
		bubbleHit.y = playerTransform.y - transform.y;
		bubbleHit.z = bubbleHit.x * bubbleHit.x + bubbleHit.y * bubbleHit.y;
	}
	//当たってるか
	if (bubbleHit.z <= (playerTransform.radius + transform.radius) *
		(playerTransform.radius + transform.radius))
	{
		isHitBubble = true;
		
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
		aliveCount = 60.0f * 20.0f;
		
		isHitWaterflow = false;
		isHitBubble = false;
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