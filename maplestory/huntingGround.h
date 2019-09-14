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
	void intersectFeild(void);  //바닥에 착지
	void monsterSpawn(void);	//몬스터 소환
	void monsterDie(void);		//몬스터 사망
	void monsterFrame(void);
	void monsterIntersect(void);//몬스터 피격
	huntingGround(){}
	~huntingGround(){}
};

