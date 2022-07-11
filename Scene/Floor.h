#pragma once
class Floor
{
public:
	Floor();
	~Floor();

	//初期化
	void Initialize();
	//床を描画
	void DrawFloor();

	//アクセッサ
	float getFloorpos() { return floorPos; }
private:

	//床の位置
	float floorPos;

};
