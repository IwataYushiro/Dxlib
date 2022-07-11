#pragma once
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
	//床を描画
	void DrawFloor();
private:

	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	//プレイヤー包含
	Player* player_ = nullptr;
	//水中ギミック包含
	WaterGimmick* waterGimmick_ = nullptr;
};

