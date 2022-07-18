#include "GameScene.h"
#include "DxLib.h"

GameScene::GameScene()
{
	
}

GameScene::~GameScene()
{
	delete floor_;
	delete player_;
	delete waterGimmick_;
}

//初期化
void GameScene::Initialize() {
	floor_ = new Floor();
	floor_->Initialize();

	player_ = new Player();
	player_->Initialize();

	waterGimmick_ = new WaterGimmick();
	waterGimmick_->Initialize();
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
	player_->Update(keys, oldkeys);
	//仕掛け
	waterGimmick_->Update(player_->GetIsHitBubble());
}

//描画
void GameScene::Draw() {
	//プレイヤー描画
	player_->Draw();
	//仕掛け
	waterGimmick_->Draw();
	// ここまで
	
	//床を描画
	floor_->DrawFloor();
}
