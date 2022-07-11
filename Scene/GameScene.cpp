#include "GameScene.h"
#include "DxLib.h"
#include "Global.h"
GameScene::GameScene()
{

}

GameScene::~GameScene()
{
	delete player_;
	delete waterGimmick_;
}

//初期化
void GameScene::Initialize() {
	player_ = new Player();
	player_->Initialize();
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
}
//描画
void GameScene::Draw() {
	player_->Draw();
	//床を描画
	DrawFloor();
}
//床を描画
void GameScene::DrawFloor() {
	//床を描画
	DrawBox(0, player_->getFloorpos(), WIN_WIDTH, WIN_HEIGHT, GetColor(31, 30, 51), true);
}
