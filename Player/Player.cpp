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
void Player::Initialize() {
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

//プレイヤー情報
void Player::InitPlayer()
{
	for (int i = 0; i < jumpLength; i++)
	{
		//プレイヤー情報初期化
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

//水流
void Player::InitWaterflow()
{
	//水流
	this->isHitWaterflow = false;
	/*for (int i = 0; i < waterGimmick_->GetEmitMax(); i++)
	{*/
	this->waterFlowHit.x = 0.0f;
	this->waterFlowHit.y = 0.0f;
	this->waterFlowHit.z = 0.0f;
	//}

}
//泡
void Player::InitBubble()
{
	for (int i = 0; i < jumpLength; i++)
	{
		//泡
		this->isHitBubble[i] = false;

		this->bubbleHit[i].x = 0.0f;
		this->bubbleHit[i].y = 0.0f;
		this->bubbleHit[i].z = 0.0f;
	}
}

//更新
void Player::MarioUpdate(char* key, char* oldkey) {
	//マリオ風泳ぎ
	if (isAlive[0] == true)
	{
		MarioSwim(key, oldkey);
		waterGimmick_->MarioUpdate(isHitBubble[0]);
		//水流
		WaterFlow();
		//泡
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

//ソニック更新
void Player::SonicUpdate(char* key, char* oldkey) {
	//ソニック風泳ぎ
	if (isAlive[1] == true)
	{
		SonicSwim(key, oldkey);
		waterGimmick_->SonicUpdate(isHitBubble[1]);

		//泡
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

//マリオ風泳ぎ
void Player::MarioSwim(char* key, char* oldkey) {


	//左アローが押されていたら
	if (key[KEY_INPUT_LEFT])
	{
		playerTransform[mario].x -= moveSpeed[mario];
	}
	//右アローが押されていたら
	if (key[KEY_INPUT_RIGHT])
	{
		playerTransform[mario].x += moveSpeed[mario];
	}
	//スペースキーを押した瞬間泳ぐ(床から離れている状態)
	if (key[KEY_INPUT_SPACE] && !oldkey[KEY_INPUT_SPACE])
	{
		isSwim[0] = true;
		//重力が0になる
		gravity[0] = 0.0f;
	}

	//泳いでいる間
	if (isSwim[0] == true)
	{
		//プレイヤーの座標 -= 浮力(固定) - 重力(徐々に上がる)　
		playerTransform[0].y -= buoyancy[0] - gravity[0];
		//重力は徐々に上がる
		gravity[0] += 0.2f;
	}
	if (gravity[0] >= 10.0f)
	{
		gravity[0] = 10.0f;
	}
	//泳いでる最中床に足を付けたら
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
//ソニック風泳ぎ
void Player::SonicSwim(char* key, char* oldkey) {


	//左アローが押されていたら
	if (key[KEY_INPUT_LEFT])
	{
		playerTransform[1].x -= moveSpeed[1];
	}
	//右アローが押されていたら
	if (key[KEY_INPUT_RIGHT])
	{
		playerTransform[1].x += moveSpeed[1];
	}

	//スペースキーを押した瞬間泳ぐ(床から離れている状態)
	if (key[KEY_INPUT_SPACE] && !oldkey[KEY_INPUT_SPACE] && isSwim[1] == false)
	{
		isSwim[1] = true;
		//重力が0になる
		gravity[1] = 0.0f;
	}
	//泳いでいる間
	if (isSwim[1] == true)
	{
		//プレイヤーの座標 -= 浮力(固定) - 重力(徐々に上がる)　
		playerTransform[1].y -= buoyancy[1] - gravity[1];
		//重力は徐々に上がる
		gravity[1] += 0.2f;
	}
	if (gravity[0] >= 15.0f)
	{
		gravity[0] = 15.0f;
	}
	//泳いでる最中床に足を付けたら
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

//水流
void Player::WaterFlow()
{
	for (int i = 0; i < waterGimmick_->GetWaterFlowEmitMax(); i++)
	{
		IsHitWaterFlow(waterGimmick_->GetWaterFlowTransform()[i], i);
	}

	for (int i = 0; i < jumpLength; i++)
	{
		//水流に飲み込まれた時
		if (isHitWaterflow == true)
		{
			playerTransform[i].x -= 2.0f;
			isHitWaterflow = false;
		}
	}

}
//当たり判定用関数
void Player::IsHitWaterFlow(Transform& transform, int num)
{
	//水流が出てるとき
	for (int i = 0; i < jumpLength; i++)
	{
		if (waterGimmick_->GetIsActiveWaterFlow()[num] == true)
		{
			waterFlowHit.x = playerTransform[i].x - transform.x;
			waterFlowHit.y = playerTransform[i].y - transform.y;
			waterFlowHit.z = waterFlowHit.x * waterFlowHit.x + waterFlowHit.y * waterFlowHit.y;
		}
		//当たってるか
		if (waterFlowHit.z <= (playerTransform[i].radius + transform.radius) *
			(playerTransform[i].radius + transform.radius))
		{
			isHitWaterflow = true;
		}
	}
}

//泡
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

//死んだあとの処理
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
		//プレイヤー情報初期化
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

//描画
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

//生きてるとき
void Player::DrawMarioAlive()
{
	DrawBox(playerTransform[0].x - playerTransform[0].radius, playerTransform[0].y - playerTransform[0].radius,
		playerTransform[0].x + playerTransform[0].radius, playerTransform[0].y + playerTransform[0].radius,
		GetColor(255, 0, 0), TRUE);
	//お知らせ
	DrawString(0, 30, "アローで移動、スペースで泳ぎますわよ", GetColor(255, 255, 255));
}

//生きてるとき
void Player::DrawSonicAlive()
{
	DrawBox(playerTransform[1].x - playerTransform[1].radius, playerTransform[1].y - playerTransform[1].radius,
		playerTransform[1].x + playerTransform[1].radius, playerTransform[1].y + playerTransform[1].radius,
		GetColor(0, 255, 0), TRUE);
	//お知らせ
	DrawString(0, 30, "アローで移動、スペースで泳ぎますわよ", GetColor(255, 255, 255));
}

//窒息死
void Player::DrawMarioChoking()
{
	DrawBox(playerTransform[0].x - playerTransform[0].radius, playerTransform[0].y - playerTransform[0].radius,
		playerTransform[0].x + playerTransform[0].radius, playerTransform[0].y + playerTransform[0].radius,
		GetColor(255, 255, 255), TRUE);
	//お知らせ
	DrawString(0, 30, "Rで復活よ", GetColor(0, 0, 0));
}

void Player::DrawSonicChoking()
{
	DrawBox(playerTransform[1].x - playerTransform[1].radius, playerTransform[1].y - playerTransform[1].radius,
		playerTransform[1].x + playerTransform[1].radius, playerTransform[1].y + playerTransform[1].radius,
		GetColor(255, 255, 255), TRUE);
	//お知らせ
	DrawString(0, 30, "Rで復活よ", GetColor(0, 0, 0));
}