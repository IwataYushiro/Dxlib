#pragma once
class Floor
{
public:
	~Floor();

	//初期化
	void Initialize();
	//床を描画
	void DrawMarioFloor();
	//ソニックVer
	void DrawSonicFloor();

	//アクセッサ
	const float getMarioFloorpos() { return marioFloorPos; }
	const float getSonicFloorpos() { return sonicFloorPos; }
private:

	//床の位置
	float marioFloorPos;
	float sonicFloorPos;

};
