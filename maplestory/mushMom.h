#pragma once
#include "monsterBase.h"
struct skill
{
	RECT rc;
	int frame;
	int count;
	int coolDownTime;						//스킬쿨타임
	bool skillend;							//스킬 프레임을 모두 다썼는지?	연기까지
};
class mushMom : public monsterBase
{
private:
	int hitTime;
	int random;
	bool _isUsingSkill;
public:
	skill _skill;
	bool isreal;
	int test;
	bool getIsUsingSkill() { return _isUsingSkill; }
	void setIsUsingSkill(bool isUsingSkill) { _isUsingSkill = isUsingSkill; }
	void monsterMove(void);
	void usingSkill(void);
	mushMom();
	~mushMom();
};

