#pragma once
class Floor
{
public:
	~Floor();

	//������
	void Initialize();
	//����`��
	void DrawFloor();

	//�A�N�Z�b�T
	float getFloorpos() { return floorPos; }
private:

	//���̈ʒu
	float floorPos;

};