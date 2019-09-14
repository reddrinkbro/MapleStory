#pragma once
#include "gameNode.h"
#include "drake.h"
#include "copperDrake.h"
#include "JuniorBalrog.h"
struct templePortal
{
	RECT rc;
	int portalFrame;
};
class temple : public gameNode
{
private:
	templePortal _portal;
	RECT _field[16];
	RECT bossHp;
	HBRUSH bossHpColor;
	float _bgSpeedX;
	float _bgSpeedY;
	int _count;
	int _deadCount;
public:
	HRESULT init(void);
	drake* _drake;
	vector<drake*> drakeVec;
	copperDrake* _copperDrake;
	vector<copperDrake*> copperDrakeVec;
	JuniorBalrog* _JuniorBalrog;
	void update(void);
	void release(void);
	void render(HDC hdc);
	void intersectFeild(void);  //¹Ù´Ú¿¡ ÂøÁö
	void portalFrame(void);		//Æ÷Å» ÇÁ·¹ÀÓ
	void monsterSpawn(void);
	void monsterFrame(void);
	void monsterIntersect(void);
	temple(){}
	~temple(){}
};

