#pragma once
class Floor
{
public:
	~Floor();

	//������
	void Initialize();
	//����`��
	void DrawMarioFloor();
	//�\�j�b�NVer
	void DrawSonicFloor();

	//�A�N�Z�b�T
	const float getMarioFloorpos() { return marioFloorPos; }
	const float getSonicFloorpos() { return sonicFloorPos; }
private:

	//���̈ʒu
	float marioFloorPos;
	float sonicFloorPos;

};
