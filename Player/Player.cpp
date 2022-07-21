#include "Player.h"
#include "DxLib.h"
#include "Global.h"

Player::~Player() {
	delete floor_;
	delete waterGimmick_;
};

//初期化
void Player::Initialize() {
	this->floor_ = new Floor();
	this->waterGimmick_ = new WaterGimmick();
	//床初期化
	floor_->Initialize();
	//仕掛け初期化
	waterGimmick_->Initialize();
	//プレイヤー情報
	InitPlayer();
	//乗り物
	InitVehicle();
	//水流
	InitWaterflow();
	//泡
	InitBubble();
	//浮遊水流
	InitFloating();
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
	this->gravity[mario] = 6.0f;
	this->gravity[sonic] = 10.0f;

}
//乗り物
void Player::InitVehicle()
{
	//乗ってるか
	this->isBoardingVehicle = false;

	this->vehicleTransform.x = 500.0f;
	this->vehicleTransform.y = 500.0f;
	this->vehicleTransform.radius = 32.0f;
}

//水流
void Player::InitWaterflow()
{
	//水流
	this->isHitWaterflow = false;
	
	this->waterFlowHit.x = 0.0f;
	this->waterFlowHit.y = 0.0f;
	this->waterFlowHit.z = 0.0f;
	
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
//浮遊水流
void Player::InitFloating()
{
	//水流
	this->isHitFloating= false;

	this->floatingHit.x = 0.0f;
	this->floatingHit.y = 0.0f;
	this->floatingHit.z = 0.0f;

}

//更新
void Player::MarioUpdate(char* key, char* oldkey) {
	//マリオ風泳ぎ
	if (isAlive[mario] == true)
	{	MarioSwim(key, oldkey);
		
		MarioVehicle(key, oldkey);
		
		if (isBoardingVehicle==false)
		{	
			waterGimmick_->MarioUpdate(isHitBubble[mario]);
			aliveCount[mario]--;
		}
		//水流
		
		WaterFlow();
		//泡
		BubbleMario();

	}
	else
	{
		DeathMario(key, oldkey);
	}

	if (aliveCount[mario] <= 0 || playerTransform[mario].y > WIN_HEIGHT + playerTransform[mario].radius)
	{
		aliveCount[mario] = 0;
		isAlive[mario] = false;
		isHitWaterflow = false;
	}
	
}

//ソニック更新
void Player::SonicUpdate(char* key, char* oldkey) {
	//ソニック風泳ぎ
	if (isAlive[sonic] == true)
	{
		SonicSwim(key, oldkey);
		waterGimmick_->SonicUpdate(isHitBubble[sonic]);

		//浮遊水流
		Floating();
		//泡
		BubbleSonic();
	}
	else
	{
		DeathSonic(key, oldkey);
	}

	if (aliveCount[sonic] <= 0 || playerTransform[sonic].y > WIN_HEIGHT + playerTransform[sonic].radius)
	{
		aliveCount[sonic] = 0;
		isAlive[sonic] = false;
		isHitWaterflow = false;
	}
	aliveCount[sonic]--;
}

//マリオ風泳ぎ
void Player::MarioSwim(char* key, char* oldkey) {

	if (isBoardingVehicle==false)
	{
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
			isSwim[mario] = true;
			//重力が0になる
			gravity[mario] = 0.0f;
		}

		//泳いでいる間
		if (isSwim[mario] == true)
		{
			//プレイヤーの座標 -= 浮力(固定) - 重力(徐々に上がる)　
			playerTransform[mario].y -= buoyancy[mario] - gravity[mario];
			//重力は徐々に上がる
			gravity[mario] += 0.2f;
		}
		if (gravity[mario] >= 10.0f)
		{
			gravity[mario] = 10.0f;
		}

		//泳いでる最中床に足を付けたら
		if (playerTransform[mario].y >= floor_->getMarioFloorpos() - playerTransform[mario].radius)
		{
			if (playerTransform[mario].x > 400.0f && playerTransform[mario].x < 800.0f)
			{
				if (playerTransform[mario].x <= 400.0f + playerTransform[mario].radius && isSwim[mario] == true)
				{
					playerTransform[mario].x = 400.0f + playerTransform[mario].radius;

				}
				else if (playerTransform[mario].x >= 800.0f - playerTransform[mario].radius && isSwim[mario] == true)
				{
					playerTransform[mario].x = 800.0f - playerTransform[mario].radius;
				}
				isSwim[mario] = true;
			}
			else
			{
				gravity[mario] = 6.0f;
				isSwim[mario] = false;
				playerTransform[mario].y = floor_->getMarioFloorpos() - playerTransform[mario].radius;
			}

		}
	}
}
//乗り物
void Player::MarioVehicle(char* key, char* oldkey)
{
	if (isBoardingVehicle == true)
	{
		//左アローが押されていたら
		if (key[KEY_INPUT_LEFT])
		{
			vehicleTransform.x -= moveSpeed[mario];
		}
		//右アローが押されていたら
		if (key[KEY_INPUT_RIGHT])
		{
			vehicleTransform.x += moveSpeed[mario];
		}
		//上アローが押されていたら
		if (key[KEY_INPUT_UP])
		{
			vehicleTransform.y -= moveSpeed[mario];
		}
		//下アローが押されていたら
		if (key[KEY_INPUT_DOWN])
		{
			vehicleTransform.y += moveSpeed[mario];
		}

		//スペースキーを押した瞬間降りる(床から離れている状態)
		if (key[KEY_INPUT_SPACE] && !oldkey[KEY_INPUT_SPACE])
		{
			isBoardingVehicle = false;

			vehicleTransform.x = 500.0f;
			vehicleTransform.y = 500.0f;
			vehicleTransform.radius = 32.0f;
		}

		//泳いでる最中床に足を付けたら
		if (vehicleTransform.y >= floor_->getMarioFloorpos() - vehicleTransform.radius)
		{
			if (vehicleTransform.x > 400.0f && vehicleTransform.x < 800.0f)
			{
				if (vehicleTransform.x <= 400.0f + vehicleTransform.radius && isSwim[mario] == true)
				{
					vehicleTransform.x = 400.0f + vehicleTransform.radius;

				}
				else if (vehicleTransform.x >= 800.0f - vehicleTransform.radius && isSwim[mario] == true)
				{
					vehicleTransform.x = 800.0f - vehicleTransform.radius;
				}

			}
			else
			{
				vehicleTransform.y = floor_->getMarioFloorpos() - vehicleTransform.radius;
			}

		}
	}
}

//ソニック風泳ぎ
void Player::SonicSwim(char* key, char* oldkey) {


	//左アローが押されていたら
	if (key[KEY_INPUT_LEFT])
	{
		playerTransform[sonic].x -= moveSpeed[sonic];
	}
	//右アローが押されていたら
	if (key[KEY_INPUT_RIGHT])
	{
		playerTransform[sonic].x += moveSpeed[sonic];
	}

	//スペースキーを押した瞬間泳ぐ(床から離れている状態)
	if (key[KEY_INPUT_SPACE] && !oldkey[KEY_INPUT_SPACE] && isSwim[sonic] == false)
	{
		isSwim[sonic] = true;
		//重力が0になる
		gravity[sonic] = 0.0f;
	}
	//泳いでいる間
	if (isSwim[sonic] == true)
	{
		//プレイヤーの座標 -= 浮力(固定) - 重力(徐々に上がる)　
		playerTransform[sonic].y -= buoyancy[sonic] - gravity[sonic];
		//重力は徐々に上がる
		gravity[sonic] += 0.2f;
	}
	if (gravity[sonic] >= 15.0f)
	{
		gravity[sonic] = 15.0f;
	}
	//泳いでる最中床に足を付けたら
	if (playerTransform[sonic].y >= floor_->getSonicFloorpos() - playerTransform[sonic].radius)
	{
		if (playerTransform[sonic].x > 700.0f)
		{
			if (playerTransform[sonic].x <= 700.0f + playerTransform[sonic].radius && isSwim[sonic] == true)
			{
				playerTransform[sonic].x = 700.0f + playerTransform[sonic].radius;
			}
			isSwim[sonic] = true;
		}
		else
		{
			gravity[sonic] = 10.0f;
			isSwim[sonic] = false;
			playerTransform[sonic].y = floor_->getSonicFloorpos() - playerTransform[sonic].radius;
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
	//水流に飲み込まれた時
	if (isHitWaterflow == true)
	{
		playerTransform[mario].x -= 2.0f;
		isHitWaterflow = false;
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
	waterGimmick_->IsHitBubbleMario(playerTransform[mario], isHitBubble[mario]);

	if (isHitBubble[mario] == true)
	{
		isHitBubble[mario] = false;
		aliveCount[mario] = 60 * 20;
	}
}
void Player::BubbleSonic()
{
	waterGimmick_->IsHitBubbleSonic(playerTransform[sonic], isHitBubble[sonic]);

	if (isHitBubble[sonic] == true)
	{
		isHitBubble[sonic] = false;
		aliveCount[sonic] = 60 * 20;
	}
}

//水流
void Player::Floating()
{
	for (int i = 0; i < waterGimmick_->GetFloatingEmitMax(); i++)
	{
		IsHitFloating(waterGimmick_->GetFloatingTransform()[i], i);
	}

	//水流に飲み込まれた時
	if (isHitFloating == true)
	{
		isSwim[sonic] = true;
		gravity[sonic] = 7.0f;
		playerTransform[sonic].y -= gravity[sonic] - (gravity[sonic] - 0.5f);
		isHitFloating = false;
	}
}

//当たり判定用関数
void Player::IsHitFloating(Transform& transform, int num)
{
	//水流が出てるとき
	for (int i = 0; i < jumpLength; i++)
	{
		if (waterGimmick_->GetIsActiveFloating()[num] == true)
		{
			floatingHit.x = playerTransform[i].x - transform.x;
			floatingHit.y = playerTransform[i].y - transform.y;
			floatingHit.z = floatingHit.x * floatingHit.x + floatingHit.y * floatingHit.y;
		}
		//当たってるか
		if (floatingHit.z <= (playerTransform[i].radius + transform.radius) *
			(playerTransform[i].radius + transform.radius))
		{
			isHitFloating = true;
		}
	}
}
//死んだあとの処理
void Player::DeathMario(char* key, char* oldkey) {

	if (key[KEY_INPUT_R] && !oldkey[KEY_INPUT_R])
	{
		playerTransform[mario].x = 32.0f;
		playerTransform[mario].y = 32.0f;
		playerTransform[mario].radius = 16.0f;
		isSwim[mario] = true;
		isAlive[mario] = true;
		aliveCount[mario] = 60 * 20;

		isHitWaterflow = false;
		isHitBubble[mario] = false;

		waterGimmick_->Reset();
	}
}

void Player::DeathSonic(char* key, char* oldkey) {

	if (key[KEY_INPUT_R] && !oldkey[KEY_INPUT_R])
	{
		playerTransform[sonic].x = 32.0f;
		playerTransform[sonic].y = 32.0f;
		playerTransform[sonic].radius = 16.0f;
		isSwim[sonic] = true;
		isAlive[sonic] = true;
		aliveCount[sonic] = 60 * 20;

		isHitBubble[sonic] = false;

		waterGimmick_->Reset();
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
		gravity[mario] = 6.0f;
		gravity[sonic] = 10.0f;
		isAlive[i] = true;
		isHitWaterflow = false;
		isHitBubble[i] = false;
		isHitFloating = false;

		isBoardingVehicle = false;

		vehicleTransform.x = 32.0f;
		vehicleTransform.y = 32.0f;
		vehicleTransform.radius = 16.0f;

		waterGimmick_->Reset();
	}

}

//描画
void Player::DrawMario() {
	if (isAlive[mario] == true)
	{
		if (isBoardingVehicle==false)
		{
			DrawMarioAlive();
		}
		DrawVehicle();
	}
	else
	{
		DrawMarioChoking();
	}

	DrawFormatString(0, 0, GetColor(0, 0, 0), "Life::%d", aliveCount[mario]);
}
void Player::DrawSonic() {
	if (isAlive[sonic] == true)
	{
		DrawSonicAlive();
	}
	else
	{
		DrawSonicChoking();
	}

	DrawFormatString(0, 0, GetColor(0, 0, 0), "Life::%d", aliveCount[sonic]);
}

//生きてるとき
void Player::DrawMarioAlive()
{
	DrawBox(playerTransform[mario].x - playerTransform[mario].radius, playerTransform[mario].y - playerTransform[mario].radius,
		playerTransform[mario].x + playerTransform[mario].radius, playerTransform[mario].y + playerTransform[mario].radius,
		GetColor(255, 0, 0), TRUE);
	//お知らせ
	DrawString(0, 30, "アローで移動、スペースで泳ぎますわよ", GetColor(255, 255, 255));
	DrawString(0, 100, "Cでジャンプ方式や仕掛けが変わりまっせ", GetColor(100, 255, 100));
}
void  Player::DrawVehicle()
{
	DrawBox(vehicleTransform.x - vehicleTransform.radius, vehicleTransform.y - vehicleTransform.radius,
		vehicleTransform.x + vehicleTransform.radius, vehicleTransform.y + vehicleTransform.radius,
		GetColor(0, 0, 255), TRUE);
	//お知らせ
	DrawString(0, 30, "アローで移動、スペースで泳ぎますわよ", GetColor(255, 255, 255));
	DrawString(0, 100, "Cでジャンプ方式や仕掛けが変わりまっせ", GetColor(100, 255, 100));
	if (isBoardingVehicle==true)
	{
		DrawString(0, 200, "乗りごごちヨシ！", GetColor(0, 0, 200));
	}
	
}

//生きてるとき
void Player::DrawSonicAlive()
{
	DrawBox(playerTransform[sonic].x - playerTransform[sonic].radius, playerTransform[sonic].y - playerTransform[sonic].radius,
		playerTransform[sonic].x + playerTransform[sonic].radius, playerTransform[sonic].y + playerTransform[sonic].radius,
		GetColor(0, 255, 0), TRUE);
	//お知らせ
	DrawString(0, 30, "アローで移動、スペースで泳ぎますわよ", GetColor(255, 255, 255));
	DrawString(0, 100, "Cでジャンプ方式や仕掛けが変わりまっせ", GetColor(255, 100, 100));
}

//窒息死
void Player::DrawMarioChoking()
{
	DrawBox(playerTransform[mario].x - playerTransform[mario].radius, playerTransform[mario].y - playerTransform[mario].radius,
		playerTransform[mario].x + playerTransform[mario].radius, playerTransform[mario].y + playerTransform[mario].radius,
		GetColor(255, 255, 255), TRUE);
	//お知らせ
	DrawString(0, 30, "Rで復活よ", GetColor(0, 0, 0));
}

void Player::DrawSonicChoking()
{
	DrawBox(playerTransform[sonic].x - playerTransform[sonic].radius, playerTransform[sonic].y - playerTransform[sonic].radius,
		playerTransform[sonic].x + playerTransform[sonic].radius, playerTransform[sonic].y + playerTransform[sonic].radius,
		GetColor(255, 255, 255), TRUE);
	//お知らせ
	DrawString(0, 30, "Rで復活よ", GetColor(0, 0, 0));
}