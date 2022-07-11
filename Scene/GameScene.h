#pragma once
#include "Floor.h"
#include "Player.h"
#include "WaterGimmick.h"

class GameScene
{
public:
	GameScene();
	~GameScene();

	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Draw();

private:

	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	//床描画
	Floor* floor_ = nullptr;
	//プレイヤー包含
	Player* player_ = nullptr;
	//水中ギミック包含
	WaterGimmick* waterGimmick_ = nullptr;

	//泡が出るカウント
	float bublleCount;
};

