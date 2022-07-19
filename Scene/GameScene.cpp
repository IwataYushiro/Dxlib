#include "GameScene.h"
#include "DxLib.h"

GameScene::GameScene()
{
	player_ = new Player();
	floor_ = new Floor();
	waterGimmick_ = new WaterGimmick();

}

GameScene::~GameScene()
{
	delete floor_;
	delete player_;
	delete waterGimmick_;
}

//初期化
void GameScene::Initialize() {

	floor_->Initialize();
	waterGimmick_->Initialize();
	playerJump = mario;

	switch (playerJump)
	{
	case mario:
		player_->MarioInitialize();
		break;
	case sonic:
		player_->SonicInitialize();
		break;
	}

}
//更新
void GameScene::Update() {

	// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
	for (int i = 0; i < 256; ++i)
	{
		oldkeys[i] = keys[i];
	}
	// 最新のキーボード情報を取得
	GetHitKeyStateAll(keys);

	// 画面クリア
	ClearDrawScreen();

	//更新処理
	switch (playerJump)
	{
	case mario:
		player_->MarioUpdate(keys, oldkeys);
		//仕掛け
		waterGimmick_->MarioUpdate(player_->GetIsHitBubble());
		if (keys[KEY_INPUT_1] && !oldkeys[KEY_INPUT_1])
		{
			player_->Reset();
			playerJump = sonic;
			break;
		}

	case sonic:
		player_->SonicUpdate(keys, oldkeys);
		//仕掛け
		waterGimmick_->SonicUpdate(player_->GetIsHitBubble());
		if (keys[KEY_INPUT_1] && !oldkeys[KEY_INPUT_1])
		{
			player_->Reset();
			playerJump = mario;
			break;
		}
	}

}

//描画
void GameScene::Draw() {


	switch (playerJump)
	{

	case mario:
		//仕掛け
		waterGimmick_->MarioDraw();
		// ここまで
		//プレイヤー描画
		player_->DrawMario();
		//床を描画
		floor_->DrawMarioFloor();
		DrawString(0, 150, "mario", GetColor(255, 0, 0));
		break;

	case sonic:
		//仕掛け
		waterGimmick_->SonicDraw();
		// ここまで
		//プレイヤー描画
		player_->DrawSonic();
		//床を描画
		floor_->DrawSonicFloor();

		DrawString(0, 150, "sonic", GetColor(0, 255, 0));
		break;
	
	}

}
