#pragma once
#include "monsterBase.h"
struct skill
{
	RECT rc;
	int frame;
	int count;
	int coolDownTime;						//��ų��Ÿ��
	bool skillend;							//��ų �������� ��� �ٽ����?	�������
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

