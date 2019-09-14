#pragma once
#include "singletonBase.h"
class shadeSplit : public singletonBase<shadeSplit>
{
private:
	int _startLeft;			//프레임설정할 변수
	int _startRight;
	int _damage;			//스킬데미지
	int _mana;				//스킬 사용 마나
	bool _isPossible;		//스킬을 사용할수 있는가
	bool _isUsing;			//스킬을 사용했는가

public:
	HRESULT init();
	RECT _skillRange;		//스킬 데미지 피격 범위
	int _skillCount;		//스킬 프레임 카운트
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

