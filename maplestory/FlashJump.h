#pragma once
#include "singletonBase.h"
class FlashJump : public singletonBase<FlashJump>
{
private:
	int _startLeft;			//�����Ӽ����� ����
	int _startRight;
	int _damage;			//��ų������
	bool _isPossible;		//��ų�� ����Ҽ� �ִ°�
public:
	HRESULT init();
	RECT _skillRange;		//��ų ������ �ǰ� ����
	int _skillCount;		//��ų ������ ī��Ʈ
	int getStartLeft() { return _startLeft; }
	void setStartLeft(int startLeft) { _startLeft = startLeft; }
	int getStartRight() { return _startRight; }
	void setStartRight(int startRight) { _startRight = startRight; }
	int getDamage() { return _damage; }
	void setDamage(int damage) { _damage = damage; }
	bool getIsPossible() { return _isPossible; }
	void setIsPossible(bool isPossible) { _isPossible = isPossible; }
	FlashJump(){}
	~FlashJump(){}
};

