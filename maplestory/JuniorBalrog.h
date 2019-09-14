#pragma once
#include "monsterBase.h"
struct skillStuct{
	RECT rc;
	int frame;
	int count;
	bool skillUse;								//��ų���
	bool skillEnd;								//��ų�� ��������
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
	int coolDownTime;							//��ų ��Ÿ��
	void monsterMove(void);
	bool getIsUsingSkill() { return _isUsingSkill; }
	void setIsUsingSkill(bool isUsingSkill) { _isUsingSkill = isUsingSkill; }
	void usingSkill(void);
	JuniorBalrog();
	~JuniorBalrog();
};

