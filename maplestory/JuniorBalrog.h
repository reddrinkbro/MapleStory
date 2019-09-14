#pragma once
#include "monsterBase.h"
struct skillStuct{
	RECT rc;
	int frame;
	int count;
	bool skillUse;								//스킬사용
	bool skillEnd;								//스킬이 종료됬는지
};
class JuniorBalrog : public monsterBase
{
private:
	int hitTime;
	bool _isUsingSkill;
public:
	skillStuct _skill[2];
	int random;
	int skillSelect;
	bool isreal;
	int coolDownTime;							//스킬 쿨타임
	void monsterMove(void);
	bool getIsUsingSkill() { return _isUsingSkill; }
	void setIsUsingSkill(bool isUsingSkill) { _isUsingSkill = isUsingSkill; }
	void usingSkill(void);
	JuniorBalrog();
	~JuniorBalrog();
};

