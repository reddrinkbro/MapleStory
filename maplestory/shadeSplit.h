#pragma once
#include "singletonBase.h"
class shadeSplit : public singletonBase<shadeSplit>
{
private:
	int _startLeft;			//�����Ӽ����� ����
	int _startRight;
	int _damage;			//��ų������
	int _mana;				//��ų ��� ����
	bool _isPossible;		//��ų�� ����Ҽ� �ִ°�
	bool _isUsing;			//��ų�� ����ߴ°�

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
	int getMana() { return _mana; }
	void setMana(int mana) { _mana = mana; }
	bool getIsPossible() { return _isPossible; }
	void setIsPossible(bool isPossible) { _isPossible = isPossible; }
	bool getIsUsing() { return _isUsing; }
	void setIsUsing(bool isUsing) { _isUsing = isUsing; }
	void usingSkill(void);
	void possibleSkill(void);
	shadeSplit(){}
	~shadeSplit(){}
};

