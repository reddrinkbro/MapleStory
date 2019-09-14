#pragma once
#include "gameNode.h"
#include "stump.h"
#include "AxeStump.h"
struct huntingGroundPortal
{
	RECT rc;
	int portalFrame;
};
struct field
{
	RECT rc;
};

class huntingGround : public gameNode
{
private:
	huntingGroundPortal _portal[2];
	field _field[13];
	stump* _stump;
	vector <stump*> stumpVec;
	AxeStump* _axeStump;
	vector <AxeStump*> axeStumpVec;
	float _bgSpeedX;
	float _bgSpeedY;
	int _count;
	int test;
public:
	HRESULT init();
	void update(void);
	void release(void);
	void render(HDC hdc);
	void portalFrame(void);
	void intersectFeild(void);  //�ٴڿ� ����
	void monsterSpawn(void);	//���� ��ȯ
	void monsterDie(void);		//���� ���
	void monsterFrame(void);
	void monsterIntersect(void);//���� �ǰ�
	huntingGround(){}
	~huntingGround(){}
};

