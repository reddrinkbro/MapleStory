#pragma once
#include "blueMushroom.h"
#include "OrangeMushroom.h"
#include "mushMom.h"
#include "shurikenBurst.h"
#include "windTalisman.h"
#include "shadeSplit.h"
#include "gameNode.h"

struct mushMomFieldPortal
{
	RECT rc;
	int portalFrame;
};
class mushMomField : public gameNode
{
private:
	mushMomFieldPortal _portal[2];
	RECT _field[11];
	blueMushroom* _blueMushroom;
	vector <blueMushroom*> blueMushroomVec;
	OrangeMushroom* _orangeMushroom;
	vector <OrangeMushroom*> orangeMushroomVec;
	RECT bossHp;
	HBRUSH bossHpColor;
	mushMom* _mushMom;
	float _bgSpeedX;
	float _bgSpeedY;
	int _count;
	int _deadCount;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);
	void intersectFeild(void);  //¹Ù´Ú¿¡ ÂøÁö
	void portalFrame(void);		//Æ÷Å» ÇÁ·¹ÀÓ
	void monsterSpawn(void);
	void monsterFrame(void);
	void monsterIntersect(void);
	mushMomField(){}
	~mushMomField(){}
};

