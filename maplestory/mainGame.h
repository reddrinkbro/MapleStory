#pragma once
#include "gameNode.h"
#include "mushMomField.h"
#include "huntingGround.h"
#include "startSpot.h"
#include "temple.h"
class mainGame : public gameNode
{
private:
	startSpot* _startSpot;							//첫번째맵
	huntingGround* _hunting;						//두번째맵
	mushMomField* _mushMom;							//세번째맵
	temple* _temple;								//네번째맵
	gameNode* _currentScene;
	map<int, gameNode*> gameNodeMap;
	map<int, gameNode*>::iterator gameNodeIter;
	int playerSpot;									//유저가 왔던 곳
	int _skillCount;
public:
	int test;
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);
	void skillFrame(void);  //스킬 프레임 설정
	void playerFrame(void); //플레이어 프레임 설정
	void playerMove(void);
	void javelinMove(void);
	float getDistance(float x1, float y1, float x2, float y2);
	float getAngle(float x1, float y1, float x2, float y2);
	mainGame() :_currentScene(NULL) {}
	~mainGame() {}
};

