#pragma once
#include "gameNode.h"
#include "mushMomField.h"
#include "huntingGround.h"
#include "startSpot.h"
#include "temple.h"
class mainGame : public gameNode
{
private:
	startSpot* _startSpot;							//ù��°��
	huntingGround* _hunting;						//�ι�°��
	mushMomField* _mushMom;							//����°��
	temple* _temple;								//�׹�°��
	gameNode* _currentScene;
	map<int, gameNode*> gameNodeMap;
	map<int, gameNode*>::iterator gameNodeIter;
	int playerSpot;									//������ �Դ� ��
	int _skillCount;
public:
	int test;
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);
	void skillFrame(void);  //��ų ������ ����
	void playerFrame(void); //�÷��̾� ������ ����
	void playerMove(void);
	void javelinMove(void);
	float getDistance(float x1, float y1, float x2, float y2);
	float getAngle(float x1, float y1, float x2, float y2);
	mainGame() :_currentScene(NULL) {}
	~mainGame() {}
};

