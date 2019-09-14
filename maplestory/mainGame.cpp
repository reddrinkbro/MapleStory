#include "stdafx.h"
#include "mainGame.h"

//=========================
//	## init(void) ## �ʱ�ȭ
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//�̰����� �ʱ�ȭ
	playerSpot = 1;						
	IMAGEMANAGER->addFrameImage("�÷��̾�", "player/player.bmp", 315, 1099, 4, 13, true, RGB(255, 0, 255));		//�÷��̾�
	IMAGEMANAGER->addFrameImage("ǥâ", "player/ǥâ.bmp", 60, 30, 2, 1, true, RGB(255, 0, 255));				//ǥâ
	IMAGEMANAGER->addImage("UI", "UI/UI.bmp", 800, 68, true, RGB(255, 0, 255));									//UI
	IMAGEMANAGER->addImage("Slot", "UI/slot.bmp", 151, 80);														//UI(����)
	IMAGEMANAGER->addImage("HP", "UI/HP.bmp", 107, 16, true, RGB(255, 0, 255));									//HP��
	IMAGEMANAGER->addImage("MP", "UI/MP.bmp", 107, 16, true, RGB(255, 0, 255));									//MP��
	IMAGEMANAGER->addImage("EmptyHp", "UI/empty.bmp", 107, 16);													//�� HP��
	IMAGEMANAGER->addImage("EmptyMp", "UI/empty.bmp", 107, 16);													//�� MP��
	IMAGEMANAGER->addFrameImage("�÷�������", "skill/flashJump.bmp", 650, 170, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ű����", "skill/luckySeven.bmp", 300, 88, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����˹���Ʈ", "skill/shurikenBurst.bmp", 2612, 390, 7, 2, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("�����˹���Ʈźȯ", "skill/shurikenBurstBullet.bmp", 714, 182, 3, 2, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("����Ż������źȯ", "skill/windTalismanBullet.bmp", 726, 272, 3, 2, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("����Ż������", "skill/windTalisman.bmp", 3271, 422, 10, 2, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("���̵彺�ø�", "skill/shadeSplit.bmp", 6559, 381, 10, 1, true, RGB(0, 0, 0));


	_startSpot = new startSpot;
	_startSpot->init();
	
	_hunting = new huntingGround;
	_hunting->init();

	_mushMom = new mushMomField;
	_mushMom->init();

	_temple = new temple;
	_temple->init();
	gameNodeMap.insert(make_pair(1, _startSpot));	//���� ���� �ʵ�� ����
	gameNodeMap.insert(make_pair(2, _hunting));
	gameNodeMap.insert(make_pair(3, _mushMom));
	gameNodeMap.insert(make_pair(4, _temple));
	_currentScene = gameNodeMap.find(playerSpot)->second;
	test = 0;
	return S_OK;
}

//=====================
//	## release(void) ##
//=====================
void mainGame::release(void)
{
	gameNode::release();
	//�����Ҵ��� �ߴٸ� ���⿡�� SAFE_DELETE() ���
	SAFE_DELETE(_startSpot);
	SAFE_DELETE(_mushMom);
	SAFE_DELETE(_hunting);
	SAFE_DELETE(_temple);
}

//=============================
//	## update(void) ## ������Ʈ
//=============================
void mainGame::update(void)
{	
	gameNode::update();	
	//�̰����� ����, Ű����, ���콺��� ������Ʈ�� �Ѵ�
	_currentScene->update();
	playerMove();
	skillFrame();
	
	LUCKSEVEN->possibleSkill();
	SHURIKENBURST->possibleSkill();
	WINDTALISMAN->possibleSkill();
	SHADESPLIT->possibleSkill();
	if (PLAYER->_playerRect.rc.left < 0)	//�÷��̾�� ���� �ٱ����� ������ ����
	{
		PLAYER->_playerRect.rc.left = 0;
		PLAYER->_playerRect.rc.right = PLAYER->_playerRect.rc.left + 85;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		PLAYER->playerLevelUp();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		PLAYER->_isHit = true;
	}

	// ��ų ���
	if (FLASHJUMP->getIsPossible())
	{
		if (PLAYER->_isLeft)
		{
			FLASHJUMP->_skillRange.left = PLAYER->_playerRect.rc.right-25;
			FLASHJUMP->_skillRange.right = FLASHJUMP->_skillRange.left + 130;
			FLASHJUMP->_skillRange.top = PLAYER->_playerRect.rc.top + 30;
			FLASHJUMP->_skillRange.bottom = FLASHJUMP->_skillRange.top + 85;
		}
		else
		{
			FLASHJUMP->_skillRange.left = PLAYER->_playerRect.rc.left - 105;
			FLASHJUMP->_skillRange.right = FLASHJUMP->_skillRange.left + 130;
			FLASHJUMP->_skillRange.top = PLAYER->_playerRect.rc.top + 30;
			FLASHJUMP->_skillRange.bottom = FLASHJUMP->_skillRange.top + 85;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SHIFT) && !PLAYER->_isUsingSkill)
	{
		LUCKSEVEN->usingSkill();
		PLAYER->_isAttack = true;
		PLAYER->_isUsingSkill = true;
		PLAYER->_javelin1._rc = RectMake(LUCKSEVEN->_skillRange.left + 30, LUCKSEVEN->_skillRange.top, 30, 30);
		PLAYER->_javelin2._rc = RectMake(LUCKSEVEN->_skillRange.left + 30, LUCKSEVEN->_skillRange.top, 30, 30);
		PLAYER->_javelin1._usingJavelin = true;
		PLAYER->_javelin2._usingJavelin = true;
		if (PLAYER->_playerRect.mp.left > WINSIZEX / 2 - 252)
		{
			PLAYER->_playerRect.mp.left -= 3;
			PLAYER->_playerRect.mp.right -= 3;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_INSERT) && SHURIKENBURST->getIsPossible())
	{
		SHURIKENBURST->usingSkill();
		PLAYER->_isAttack = true;
		PLAYER->_isUsingSkill = true;
		if (PLAYER->_isLeft)
		{
			SHURIKENBURST->_javelin.rc = RectMake(PLAYER->_playerRect.rc.left - 109, PLAYER->_playerRect.rc.bottom - 70, 238, 91);
		}
		else
		{
			SHURIKENBURST->_javelin.rc = RectMake(SHURIKENBURST->_skillRange.left + 50, PLAYER->_playerRect.rc.bottom - 70, 238, 91);
		}
		if (PLAYER->_playerRect.mp.left > WINSIZEX / 2 - 250)
		{
			PLAYER->_playerRect.mp.left -= 5;
			PLAYER->_playerRect.mp.right -= 5;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_HOME) && WINDTALISMAN->getIsPossible())
	{
		WINDTALISMAN->usingSkill();
		PLAYER->_isAttack = true;
		PLAYER->_isUsingSkill = true;
		if (PLAYER->_isLeft)
		{
			WINDTALISMAN->_javelin.rc = RectMake(WINDTALISMAN->_skillRange.right-238, WINDTALISMAN->_skillRange.bottom - 150, 238, 91);
		}
		else
		{
			WINDTALISMAN->_javelin.rc = RectMake(WINDTALISMAN->_skillRange.left, WINDTALISMAN->_skillRange.bottom - 150, 238, 91);
		}
		if (PLAYER->_playerRect.mp.left > WINSIZEX / 2 - 245)
		{
			PLAYER->_playerRect.mp.left -= 10;
			PLAYER->_playerRect.mp.right -= 10;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_PRIOR) && SHADESPLIT->getIsPossible())
	{
		SHADESPLIT->usingSkill();
		PLAYER->_isAttack = false;
		PLAYER->_isMove = false;
		PLAYER->_isUsingSkill = true;
		if (PLAYER->_playerRect.mp.left > WINSIZEX / 2 - 225)
		{
			PLAYER->_playerRect.mp.left -= 30;
			PLAYER->_playerRect.mp.right -= 30;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DELETE))
	{
		if (PLAYER->_playerRect.hp.left < WINSIZEX / 2 - 256)
		{
			PLAYER->_playerRect.hp.left += 30;
			PLAYER->_playerRect.hp.right += 30;
		}
	}
	if (PLAYER->_playerRect.hp.left >= WINSIZEX / 2 - 256)
	{
		PLAYER->_playerRect.hp.left -= PLAYER->_playerRect.hp.left - (WINSIZEX / 2 - 256);
		PLAYER->_playerRect.hp.right -= PLAYER->_playerRect.hp.left - (WINSIZEX / 2 - 256);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_END))
	{
		if (PLAYER->_playerRect.mp.left < WINSIZEX / 2 - 148)
		{
			PLAYER->_playerRect.mp.left += 30;
			PLAYER->_playerRect.mp.right += 30;
		}
	}
	if (PLAYER->_playerRect.mp.left >= WINSIZEX / 2 - 148)
	{
		PLAYER->_playerRect.mp.left -= PLAYER->_playerRect.mp.left - (WINSIZEX / 2 - 148);
		PLAYER->_playerRect.mp.right -= PLAYER->_playerRect.mp.left - (WINSIZEX / 2 - 148);
	}
	if (PLAYER->_jumpCount < 2 && !PLAYER->_isAttack && !PLAYER->_isUsingSkill)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT) )//����,��ų����߿��� �̵��� �Ұ����ϴ�
		{
			PLAYER->_isLeft = true;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			PLAYER->_isMove = false;
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			PLAYER->_isMove = true;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) )
		{
			PLAYER->_isLeft = false;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT)) PLAYER->_isMove = false;
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			PLAYER->_isMove = true;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		PLAYER->_isLie = false;
		PLAYER->_isDownJump = false;
		PLAYER->_isDownClimbing = false;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		PLAYER->_isDownJump = true;
		PLAYER->_isDownClimbing = true;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		PLAYER->_isLie = true;
		PLAYER->_isDownClimbing = true;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) &&!PLAYER->_isHit && !PLAYER->_isRopeUsing)
	{
		PLAYER->_isLie = false;
		if (!PLAYER->_isDownJump)
		{
			PLAYER->_isJump = true;
			PLAYER->_jumpCount++;
			if (PLAYER->_jumpCount == 2)
			{
				PLAYER->flashJump();
				PLAYER->_jumpCount++;
			}
		}
		else
		{
			PLAYER->_jumpCount --;
			PLAYER->_isJump = true;
		}
	}
	
	if (KEYMANAGER->isOnceKeyDown(VK_CONTROL) && !PLAYER->_isUsingSkill && !PLAYER->_isLie) //��ų ���� ���ݺҰ�
	{
		
		PLAYER->_isAttack = true;
		PLAYER->_isMove = false;
		PLAYER->_javelin1._usingJavelin = true;
		PLAYER->_javelin1._rc = RectMake(PLAYER->_playerRect.rc.left + (PLAYER->_playerRect.rc.right - PLAYER->_playerRect.rc.left) / 2, PLAYER->_playerRect.rc.top + 30, 30, 30);

		
	}
	if (KEYMANAGER->isStayKeyDown(VK_CONTROL) && !PLAYER->_isMove && !PLAYER->_isUsingSkill)
	{
		PLAYER->_isAttack = true;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		PLAYER->_isClimbing = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))PLAYER->_isClimbing = false;
	if (!PLAYER->_isAttack) PLAYER->_playerRect.attackFrame = 0; //���ݾ��Ҷ��� �������� 0���� �ʱ�ȭ
	else if(PLAYER->_isAttack && !SHADESPLIT->getIsUsing() && !WINDTALISMAN->getIsUsing() && !SHURIKENBURST->getIsUsing())
	{
		javelinMove();
	}
	playerFrame();
}

//============================
//	## render(HDC hdc) ## ����
//============================

void mainGame::render(HDC hdc)
{
	char str[128];
	//��� �� ��Ʈ�� (�̰͵� ������ �״�� �Ѱ�)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//=============================================================
	if (PLAYER->_isPlayerMoveMap)
	{
		
		_currentScene->render(getMemDC());
		if (KEYMANAGER->isToggleKey(VK_F1))
		{
			Rectangle(getMemDC(), PLAYER->_playerRect.rc.left, PLAYER->_playerRect.rc.top, PLAYER->_playerRect.rc.right, PLAYER->_playerRect.rc.bottom);
		}
		
		if (PLAYER->_javelin2._usingJavelin)
		{
			IMAGEMANAGER->frameRender("ǥâ", getMemDC(), PLAYER->_javelin2._rc.left, PLAYER->_javelin2._rc.top);
		}
		if (PLAYER->_javelin1._usingJavelin)
		{
			IMAGEMANAGER->frameRender("ǥâ", getMemDC(), PLAYER->_javelin1._rc.left, PLAYER->_javelin1._rc.top);
		}
		IMAGEMANAGER->frameRender("�÷��̾�", getMemDC(), PLAYER->_playerRect.rc.left, PLAYER->_playerRect.rc.top);

		if (PLAYER->_jumpCount > 2)
		{
			IMAGEMANAGER->frameRender("�÷�������", getMemDC(), FLASHJUMP->_skillRange.left, FLASHJUMP->_skillRange.top);
		}
		if (PLAYER->_isUsingSkill)
		{
			if (LUCKSEVEN->getIsUsing())
			{
				IMAGEMANAGER->frameRender("��Ű����", getMemDC(), LUCKSEVEN->_skillRange.left, LUCKSEVEN->_skillRange.top);
			}
			if (SHURIKENBURST->getIsUsing())
			{
				IMAGEMANAGER->frameRender("�����˹���Ʈ", getMemDC(), SHURIKENBURST->_skillRange.left, SHURIKENBURST->_skillRange.top);
				if (SHURIKENBURST->getStartLeft() > 3)
				{
					IMAGEMANAGER->frameRender("�����˹���Ʈźȯ", getMemDC(), SHURIKENBURST->_javelin.rc.left, SHURIKENBURST->_javelin.rc.top);
				}
				else if (SHURIKENBURST->getStartRight() < 3)
				{
					IMAGEMANAGER->frameRender("�����˹���Ʈźȯ", getMemDC(), SHURIKENBURST->_javelin.rc.left, SHURIKENBURST->_javelin.rc.top);
				}
			}
			if (WINDTALISMAN->getIsUsing())
			{
				IMAGEMANAGER->frameRender("����Ż������", getMemDC(), WINDTALISMAN->_skillRange.left, WINDTALISMAN->_skillRange.top);

				if (WINDTALISMAN->getStartLeft() > 4)
				{
					IMAGEMANAGER->frameRender("����Ż������źȯ", getMemDC(), WINDTALISMAN->_javelin.rc.left, WINDTALISMAN->_javelin.rc.top);
				}
				else if (WINDTALISMAN->getStartRight() < 5)
				{
					IMAGEMANAGER->frameRender("����Ż������źȯ", getMemDC(), WINDTALISMAN->_javelin.rc.left, WINDTALISMAN->_javelin.rc.top);
				}
			}
			if (SHADESPLIT->getIsUsing())
			{
				IMAGEMANAGER->frameRender("���̵彺�ø�", getMemDC(), SHADESPLIT->_skillRange.left, SHADESPLIT->_skillRange.top);
			}
		}
		IMAGEMANAGER->render("EmptyMp", getMemDC(), WINSIZEX / 2 - 148, WINSIZEY - 19);
		IMAGEMANAGER->render("MP", getMemDC(), PLAYER->_playerRect.mp.left, PLAYER->_playerRect.mp.top);
		IMAGEMANAGER->render("EmptyHp", getMemDC(), WINSIZEX / 2 - 256, WINSIZEY - 19);
		IMAGEMANAGER->render("HP", getMemDC(), PLAYER->_playerRect.hp.left, PLAYER->_playerRect.hp.top);
		IMAGEMANAGER->render("Slot", getMemDC(), WINSIZEX - 150, WINSIZEY - 80);
		IMAGEMANAGER->render("UI", getMemDC(), 0, WINSIZEY - 68);
	}
	
	//sprintf(str, " %d %d", PLAYER->_playerRect.rc.left, PLAYER->_playerRect.rc.top);
	//TextOut(getMemDC(), 100, 100 , str, strlen(str));

	
	//=============================================================
	//������� ������ HDC�� �׸���
	this->getBackBuffer()->render(getHDC());
}

void mainGame::playerFrame(void)
{
	
	if (PLAYER->_isMove)	// ���� �����϶�
	{
		if (PLAYER->_isLeft)
		{
			PLAYER->_count++;
			if (PLAYER->_playerRect.rc.left > 0)
			{
				PLAYER->_playerRect.rc.left -= 3;
				PLAYER->_playerRect.rc.right -= 3;
				if (PLAYER->_isRopeUsing)
				{
					PLAYER->_playerRect.rc.left += 3;
					PLAYER->_playerRect.rc.right += 3;
				}
			}
			IMAGEMANAGER->findImage("�÷��̾�")->setFrameY(1);
			if (PLAYER->_count % 12 == 0)
			{
				PLAYER->_playerRect.moveFrame++;
				if (PLAYER->_playerRect.moveFrame > 3)
				{
					PLAYER->_playerRect.moveFrame = 0;
				}
				IMAGEMANAGER->findImage("�÷��̾�")->setFrameX(PLAYER->_playerRect.moveFrame);
			}
		}
		else  // ������ �����϶�
		{
			PLAYER->_count++;
			if (PLAYER->_playerRect.rc.right < WINSIZEX)
			{
				PLAYER->_playerRect.rc.left += 3;
				PLAYER->_playerRect.rc.right += 3;
				if (PLAYER->_isRopeUsing)
				{
					PLAYER->_playerRect.rc.left -= 3;
					PLAYER->_playerRect.rc.right -= 3;
				}
			}
			IMAGEMANAGER->findImage("�÷��̾�")->setFrameY(2);
			if (PLAYER->_count % 12 == 0)
			{
				PLAYER->_playerRect.moveFrame++;
				if (PLAYER->_playerRect.moveFrame > 3)
				{
					PLAYER->_playerRect.moveFrame = 0;
				}
				IMAGEMANAGER->findImage("�÷��̾�")->setFrameX(PLAYER->_playerRect.moveFrame);
			}
			
		}
		
		
	}
	
	if (PLAYER->_isJump)							//�÷��̾ �����Ҷ�
	{
		PLAYER->playerJump();
		PLAYER->_playerRect.time += 0.03;
		if (PLAYER->_jumpCount > 2)
		{
			FLASHJUMP->_skillCount++;
		}
		if (!PLAYER->_isAttack)
		{
			if (PLAYER->_isLeft)
			{
				IMAGEMANAGER->findImage("�÷��̾�")->setFrameX(0);
				IMAGEMANAGER->findImage("�÷��̾�")->setFrameY(9);
				IMAGEMANAGER->findImage("�÷�������")->setFrameY(0);
				if (FLASHJUMP->_skillCount % 9 == 0)
				{
					FLASHJUMP->setStartLeft(FLASHJUMP->getStartLeft() + 1);
					if (FLASHJUMP->getStartLeft() > 4)
					{
						FLASHJUMP->setStartLeft(0);
						PLAYER->_isUsingSkill = false;
						PLAYER->_isAttack = false;
					}
					IMAGEMANAGER->findImage("�÷�������")->setFrameX(FLASHJUMP->getStartLeft());
				}
			}
			else if (!PLAYER->_isLeft)
			{
				IMAGEMANAGER->findImage("�÷��̾�")->setFrameX(1);
				IMAGEMANAGER->findImage("�÷��̾�")->setFrameY(9);
				IMAGEMANAGER->findImage("�÷�������")->setFrameY(1);
				if (FLASHJUMP->_skillCount % 9 == 0)
				{
					FLASHJUMP->setStartRight(FLASHJUMP->getStartRight() - 1);
					if (FLASHJUMP->getStartRight() < 0)
					{
						FLASHJUMP->setStartRight(4);
						PLAYER->_isUsingSkill = false;
						PLAYER->_isAttack = false;
					}
					IMAGEMANAGER->findImage("�÷�������")->setFrameX(FLASHJUMP->getStartRight());
				}
			}
		}
		else
		{
			if (PLAYER->_isLeft)
			{
				PLAYER->_playerRect.rc.left -= 3;
				PLAYER->_playerRect.rc.right -= 3;
			}
			else
			{
				PLAYER->_playerRect.rc.left += 3;
				PLAYER->_playerRect.rc.right += 3;
			}
		}
	}
	
	else if (PLAYER->_isHit)								//�÷��̾ �������� �¾�����
	{
		if (PLAYER->_isLeft)
		{
			IMAGEMANAGER->findImage("�÷��̾�")->setFrameX(0);
			IMAGEMANAGER->findImage("�÷��̾�")->setFrameY(9);
		}
		else if (!PLAYER->_isLeft)
		{
			IMAGEMANAGER->findImage("�÷��̾�")->setFrameX(1);
			IMAGEMANAGER->findImage("�÷��̾�")->setFrameY(9);
		}
	}
	
	if (PLAYER->_isAttack || LUCKSEVEN->getIsUsing()) //�÷��̾� ����
	{
		PLAYER->_count++;
		if (PLAYER->_isLeft) //�����϶�
		{
			/*if (PLAYER->_isMove)//�����߿��� �������� �����
			{
			PLAYER->_isMove = false;
			}*/
			if (PLAYER->_attack == 0)
			{
				IMAGEMANAGER->findImage("�÷��̾�")->setFrameY(3);

				if (PLAYER->_count % 13 == 0)
				{
					PLAYER->_playerRect.attackFrame++;
				}

				else if (PLAYER->_playerRect.attackFrame > 2)
				{
					PLAYER->_playerRect.attackFrame = 0;
					PLAYER->_attack = RND->getInt(3); //3���� ������ �������� ����
					PLAYER->_isUsingSkill = false;
					PLAYER->_isAttack = false;		  //���� ��Ȱ��ȭ
				}
				IMAGEMANAGER->findImage("�÷��̾�")->setFrameX(PLAYER->_playerRect.attackFrame);

			}
			else if (PLAYER->_attack == 1)
			{
				IMAGEMANAGER->findImage("�÷��̾�")->setFrameY(4);
				if (PLAYER->_count % 13 == 0)
				{
					PLAYER->_playerRect.attackFrame++;
				}

				else if (PLAYER->_playerRect.attackFrame > 2)
				{
					PLAYER->_playerRect.attackFrame = 0;
					PLAYER->_attack = RND->getInt(3); //3���� ������ �������� ����
					PLAYER->_isUsingSkill = false;
					PLAYER->_isAttack = false;		  //���� ��Ȱ��ȭ
				}
				IMAGEMANAGER->findImage("�÷��̾�")->setFrameX(PLAYER->_playerRect.attackFrame);
			}
			else if (PLAYER->_attack == 2 || SHURIKENBURST->getIsUsing() || WINDTALISMAN->getIsUsing())
			{
				IMAGEMANAGER->findImage("�÷��̾�")->setFrameY(5);
				if (PLAYER->_count % 13 == 0)
				{
					PLAYER->_playerRect.attackFrame++;
				}

				else if (PLAYER->_playerRect.attackFrame > 2)
				{
					PLAYER->_playerRect.attackFrame = 0;
					PLAYER->_attack = RND->getInt(3); //3���� ������ �������� ����
					PLAYER->_isUsingSkill = false;
					PLAYER->_isAttack = false;		  //���� ��Ȱ��ȭ
				}
				IMAGEMANAGER->findImage("�÷��̾�")->setFrameX(PLAYER->_playerRect.attackFrame);
			}

		}
		else  //�������϶�
		{
			if (PLAYER->_attack == 0)
			{
				IMAGEMANAGER->findImage("�÷��̾�")->setFrameY(6);

				if (PLAYER->_count % 13 == 0)
				{
					PLAYER->_playerRect.attackFrame++;
				}
				else if (PLAYER->_playerRect.attackFrame > 2)
				{
					PLAYER->_playerRect.attackFrame = 0;
					PLAYER->_isUsingSkill = false;
					PLAYER->_isAttack = false;		  //���� ��Ȱ��ȭ
					PLAYER->_attack = RND->getInt(3); //3���� ������ �������� ����
				}
				IMAGEMANAGER->findImage("�÷��̾�")->setFrameX(PLAYER->_playerRect.attackFrame);

			}
			else if (PLAYER->_attack == 1)
			{
				IMAGEMANAGER->findImage("�÷��̾�")->setFrameY(7);
				if (PLAYER->_count % 13 == 0)
				{
					PLAYER->_playerRect.attackFrame++;
				}

				else if (PLAYER->_playerRect.attackFrame > 2)
				{
					PLAYER->_playerRect.attackFrame = 0;
					PLAYER->_isUsingSkill = false;
					PLAYER->_isAttack = false;		  //���� ��Ȱ��ȭ
					PLAYER->_attack = RND->getInt(3); //3���� ������ �������� ����
				}
				IMAGEMANAGER->findImage("�÷��̾�")->setFrameX(PLAYER->_playerRect.attackFrame);
			}
			else if (PLAYER->_attack == 2 || SHURIKENBURST->getIsUsing() || WINDTALISMAN->getIsUsing())
			{
				IMAGEMANAGER->findImage("�÷��̾�")->setFrameY(8);
				if (PLAYER->_count % 13 == 0)
				{
					PLAYER->_playerRect.attackFrame++;
				}

				else if (PLAYER->_playerRect.attackFrame > 2)
				{
					PLAYER->_playerRect.attackFrame = 0;
					PLAYER->_isUsingSkill = false;

					PLAYER->_attack = RND->getInt(3); //3���� ������ �������� ����

				}
				IMAGEMANAGER->findImage("�÷��̾�")->setFrameX(PLAYER->_playerRect.attackFrame);
			}
		}
	}
	
	else if (!PLAYER->_isMove && !PLAYER->_isJump && !PLAYER->_isHit) // ����, �������� ������
	{
		if (PLAYER->_isLeft)
		{
			IMAGEMANAGER->findImage("�÷��̾�")->setFrameX(0);
			IMAGEMANAGER->findImage("�÷��̾�")->setFrameY(0);
		}
		else
		{
			IMAGEMANAGER->findImage("�÷��̾�")->setFrameX(1);
			IMAGEMANAGER->findImage("�÷��̾�")->setFrameY(0);
		}
	}
	if (PLAYER->_isLie) //���帰 �����̸�
	{
		if (PLAYER->_isAttack)PLAYER->_isAttack = false;
		if (PLAYER->_isMove)PLAYER->_isMove = false;
		if (PLAYER->_isJump)PLAYER->_isLie = false;
		else if (PLAYER->_isLeft)
		{
			IMAGEMANAGER->findImage("�÷��̾�")->setFrameX(0);
			IMAGEMANAGER->findImage("�÷��̾�")->setFrameY(10);
		}
		else
		{
			IMAGEMANAGER->findImage("�÷��̾�")->setFrameX(1);
			IMAGEMANAGER->findImage("�÷��̾�")->setFrameY(10);
		}
	}
	if (PLAYER->_javelin1._usingJavelin) //ǥâ ���ư���
	{
		PLAYER->_count++;
		IMAGEMANAGER->findImage("ǥâ")->setFrameY(0);
		if (PLAYER->_count % 2 == 0)
		{
			PLAYER->_javelin1._frame = 1;
		}
		else
		{
			PLAYER->_javelin1._frame = 0;
		}
		IMAGEMANAGER->findImage("ǥâ")->setFrameX(PLAYER->_javelin1._frame);

	}
	if (PLAYER->_javelin2._usingJavelin) //ǥâ ���ư���
	{
		IMAGEMANAGER->findImage("ǥâ")->setFrameY(0);
		if (PLAYER->_count % 2 == 0)
		{
			PLAYER->_javelin2._frame = 1;
		}
		else
		{
			PLAYER->_javelin2._frame = 0;
		}
		IMAGEMANAGER->findImage("ǥâ")->setFrameX(PLAYER->_javelin2._frame);


	}

	if (PLAYER->_javelin1._time > 1.3f && PLAYER->_javelin1._usingJavelin)
	{
		PLAYER->_javelin1._time = 0;
		PLAYER->_javelin1._usingJavelin = false;
		PLAYER->_isAttack = false;		  //���� ��Ȱ��ȭ
		PLAYER->_javelin1._rc.left = 1920;
		PLAYER->_javelin1._rc.right = PLAYER->_javelin1._rc.left + 30;
		PLAYER->_javelin1._rc.top = 1080;
		PLAYER->_javelin1._rc.bottom = PLAYER->_javelin1._rc.top + 30;
	}
	if(LUCKSEVEN->getIsUsing() && PLAYER->_javelin2._time > 1.3f)
	{
		LUCKSEVEN->setIsUsing(false);
		PLAYER->_isUsingSkill = false;
		PLAYER->_javelin2._time = 0;
		PLAYER->_javelin2._usingJavelin = false;
		PLAYER->_javelin2._rc.left = 1920;
		PLAYER->_javelin2._rc.right = PLAYER->_javelin2._rc.left + 30;
		PLAYER->_javelin2._rc.top = 1080;
		PLAYER->_javelin2._rc.bottom = PLAYER->_javelin2._rc.top + 30;
	}
	if (PLAYER->_isRopeUsing)						//�÷��̾ ������ Ÿ�� ������
	{
		PLAYER->_count++;
		IMAGEMANAGER->findImage("�÷��̾�")->setFrameY(13);
		if (PLAYER->_count % 21 == 0)
		{
			PLAYER->_playerRect.climbFrame = 1;
		}
		else if (PLAYER->_count % 44 == 0)
		{
			PLAYER->_playerRect.climbFrame = 0;
		}
		IMAGEMANAGER->findImage("�÷��̾�")->setFrameX(PLAYER->_playerRect.climbFrame);
	}
	if (PLAYER->_isLadderUsing)							//�÷��̾ ��ٸ��� Ÿ�� ������
	{
		PLAYER->_count++;
		IMAGEMANAGER->findImage("�÷��̾�")->setFrameY(12);
		if (PLAYER->_count % 21 == 0)
		{
			PLAYER->_playerRect.climbFrame = 1;
		}
		else if (PLAYER->_count % 44 == 0)
		{
			PLAYER->_playerRect.climbFrame = 0;
		}
		IMAGEMANAGER->findImage("�÷��̾�")->setFrameX(PLAYER->_playerRect.climbFrame);
	}
	
}

void mainGame::playerMove(void)
{
	if (gameNodeMap.find(playerSpot)->second->getIsInplayer() && gameNodeMap.find(playerSpot)->second->getIsLeft())
	{
		gameNodeMap.find(playerSpot)->second->setIsInPlayer(false);
		gameNodeMap.find(playerSpot)->second->setIsLeft(false);
		playerSpot++;
		gameNodeMap.find(playerSpot)->second->setIsInPlayer(true);
		PLAYER->_moveCount = 1;
		PLAYER->_isPlayerMoveMap = false;
	}
	else if(gameNodeMap.find(playerSpot)->second->getIsInplayer() && gameNodeMap.find(playerSpot)->second->getIsRight())
	{
		gameNodeMap.find(playerSpot)->second->setIsInPlayer(false);
		gameNodeMap.find(playerSpot)->second->setIsRight(false);
		playerSpot--;
		gameNodeMap.find(playerSpot)->second->setIsInPlayer(true);
		PLAYER->_moveCount = -1;
		PLAYER->_isPlayerMoveMap = false;
	}
	_currentScene = gameNodeMap.find(playerSpot)->second;
}

void mainGame::javelinMove(void)
{
	if (PLAYER->_javelin1._time < 1.3f)
	{
		PLAYER->_javelin1._time += 0.05f;
	}
	if (PLAYER->_isLeft)
	{
		PLAYER->_javelin1._rc.left -= 17;
		PLAYER->_javelin1._rc.right -= 17;
	}
	else
	{
		PLAYER->_javelin1._rc.left += 17;
		PLAYER->_javelin1._rc.right += 17;
	}
	if (LUCKSEVEN->getIsUsing())
	{
		PLAYER->_javelin2._time += 0.05f;
		
		PLAYER->_javelin2._angle = PLAYER->getAngle(PLAYER->_javelin1._rc.left, PLAYER->_javelin1._rc.top, PLAYER->_javelin2._rc.left, PLAYER->_javelin2._rc.top);
		
		if (PLAYER->_isLeft)
		{
			PLAYER->_javelin2._rc.left = PLAYER->_javelin1._rc.left - 30;
			PLAYER->_javelin2._rc.right = PLAYER->_javelin1._rc.left;
		}
		else
		{
			PLAYER->_javelin2._rc.left = PLAYER->_javelin1._rc.left - 30;
			PLAYER->_javelin2._rc.right = PLAYER->_javelin1._rc.right;
		}
		PLAYER->_javelin2._rc.top = -sinf(PLAYER->_javelin2._angle) * 15 + PLAYER->_javelin1._rc.top;
		PLAYER->_javelin2._rc.bottom = -sinf(PLAYER->_javelin2._angle) * 15 + PLAYER->_javelin1._rc.bottom;
	}
}

void mainGame::skillFrame(void)
{
	if (LUCKSEVEN->getIsUsing())
	{
		LUCKSEVEN->_skillCount++;
		if (PLAYER->_isLeft)
		{
			IMAGEMANAGER->findImage("��Ű����")->setFrameY(0);
			if (LUCKSEVEN->_skillCount % 6 == 0)
			{
				LUCKSEVEN->setStartLeft(LUCKSEVEN->getStartLeft() + 1);
				if (LUCKSEVEN->getStartLeft() > 4)
				{
					LUCKSEVEN->setStartLeft(0);
				}
				IMAGEMANAGER->findImage("��Ű����")->setFrameX(LUCKSEVEN->getStartLeft());
			}
		}
		else  //�������϶�
		{
			IMAGEMANAGER->findImage("��Ű����")->setFrameY(1);
			if (LUCKSEVEN->_skillCount % 6 == 0)
			{
				LUCKSEVEN->setStartRight(LUCKSEVEN->getStartRight() - 1);
				if (LUCKSEVEN->getStartRight() < 0)
				{
					LUCKSEVEN->setStartRight(4);
				}
				IMAGEMANAGER->findImage("��Ű����")->setFrameX(LUCKSEVEN->getStartRight());
			}
		}
	}

	if (SHURIKENBURST->getIsUsing())
	{
		SHURIKENBURST->_skillCount++;
		SHURIKENBURST->_javelin.count++;
		if (PLAYER->_isLeft)																							
		{
			SHURIKENBURST->_javelin.rc.left -=5;
			SHURIKENBURST->_javelin.rc.right -=5;
			IMAGEMANAGER->findImage("�����˹���Ʈ")->setFrameY(0);
			if (SHURIKENBURST->_skillCount % 5 == 0)
			{
				SHURIKENBURST->setStartLeft(SHURIKENBURST->getStartLeft() + 1);
				if (SHURIKENBURST->getStartLeft() > 6)
				{
					SHURIKENBURST->setStartLeft(0);
				}
				IMAGEMANAGER->findImage("�����˹���Ʈźȯ")->setFrameY(0);
				if (SHURIKENBURST->_javelin.count % 2 == 0)
				{
					SHURIKENBURST->_javelin.startLeft++;
					if (SHURIKENBURST->_javelin.startLeft > 2)
					{
						SHURIKENBURST->_javelin.startLeft = 0;
						SHURIKENBURST->setIsUsing(false);
						PLAYER->_isUsingSkill = false;
						PLAYER->_isAttack = false;
						SHURIKENBURST->_javelin.rc.left = 1920;
						SHURIKENBURST->_javelin.rc.right = SHURIKENBURST->_javelin.rc.left + 238;
						SHURIKENBURST->_javelin.rc.top = 1080;
						SHURIKENBURST->_javelin.rc.bottom = SHURIKENBURST->_javelin.rc.top + 91;
					}
					IMAGEMANAGER->findImage("�����˹���Ʈźȯ")->setFrameX(SHURIKENBURST->_javelin.startLeft);
				}
				
				IMAGEMANAGER->findImage("�����˹���Ʈ")->setFrameX(SHURIKENBURST->getStartLeft());
			}
		}
		else
		{
			SHURIKENBURST->_javelin.rc.left += 5;
			SHURIKENBURST->_javelin.rc.right += 5;
			IMAGEMANAGER->findImage("�����˹���Ʈ")->setFrameY(1);
			if (SHURIKENBURST->_skillCount % 5 == 0)
			{
				SHURIKENBURST->_javelin.count++;
				SHURIKENBURST->setStartRight(SHURIKENBURST->getStartRight() - 1);
				if (SHURIKENBURST->getStartRight() < 0)
				{
					SHURIKENBURST->setStartRight(6);
				}
				IMAGEMANAGER->findImage("�����˹���Ʈźȯ")->setFrameY(1);
				if (SHURIKENBURST->_javelin.count % 2 == 0 && SHURIKENBURST->getStartRight() <3)
				{
					SHURIKENBURST->_javelin.startRight--;
					if (SHURIKENBURST->_javelin.startRight < 0)
					{
						SHURIKENBURST->_javelin.startRight = 2;
						SHURIKENBURST->setIsUsing(false);
						PLAYER->_isUsingSkill = false;
						PLAYER->_isAttack = false;
						SHURIKENBURST->_javelin.rc.left = 1920;
						SHURIKENBURST->_javelin.rc.right = SHURIKENBURST->_javelin.rc.left + 238;
						SHURIKENBURST->_javelin.rc.top = 1080;
						SHURIKENBURST->_javelin.rc.bottom = SHURIKENBURST->_javelin.rc.top + 91;
					}
					IMAGEMANAGER->findImage("�����˹���Ʈźȯ")->setFrameX(SHURIKENBURST->_javelin.startRight);
				}
				IMAGEMANAGER->findImage("�����˹���Ʈ")->setFrameX(SHURIKENBURST->getStartRight());
			}
		}
	}
	if (WINDTALISMAN->getIsUsing())
	{
		WINDTALISMAN->_skillCount++;
		WINDTALISMAN->_javelin.count++;
		if (PLAYER->_isLeft)
		{
			WINDTALISMAN->_javelin.rc.left -= 5;
			WINDTALISMAN->_javelin.rc.right -= 5;
			IMAGEMANAGER->findImage("����Ż������")->setFrameY(0);
			if (WINDTALISMAN->_skillCount % 5 == 0)
			{
				WINDTALISMAN->setStartLeft(WINDTALISMAN->getStartLeft() + 1);
				if (WINDTALISMAN->getStartLeft() > 9)
				{
					WINDTALISMAN->setStartLeft(0);
				}
				IMAGEMANAGER->findImage("����Ż������źȯ")->setFrameY(0);
				if (WINDTALISMAN->_javelin.count % 15 == 0)
				{
					WINDTALISMAN->_javelin.startLeft++;
					if (WINDTALISMAN->_javelin.startLeft > 2)
					{
						WINDTALISMAN->_javelin.startLeft = 0;
						WINDTALISMAN->setIsUsing(false);
						PLAYER->_isUsingSkill = false;
						PLAYER->_isAttack = false;
						WINDTALISMAN->_javelin.rc.left = 1920;
						WINDTALISMAN->_javelin.rc.right = WINDTALISMAN->_javelin.rc.left + 238;
						WINDTALISMAN->_javelin.rc.top = 1080;
						WINDTALISMAN->_javelin.rc.bottom = WINDTALISMAN->_javelin.rc.top + 91;
					}
					IMAGEMANAGER->findImage("����Ż������źȯ")->setFrameX(WINDTALISMAN->_javelin.startLeft);
				}
				IMAGEMANAGER->findImage("����Ż������")->setFrameX(WINDTALISMAN->getStartLeft());
			}
		}
		else
		{
			WINDTALISMAN->_javelin.rc.left += 5;
			WINDTALISMAN->_javelin.rc.right += 5;
			IMAGEMANAGER->findImage("����Ż������")->setFrameY(1);
			if (WINDTALISMAN->_skillCount % 5 == 0)
			{
				WINDTALISMAN->setStartRight(WINDTALISMAN->getStartRight() - 1);
				if (WINDTALISMAN->getStartRight() < 0)
				{
					WINDTALISMAN->setStartRight(9);
				}
				IMAGEMANAGER->findImage("����Ż������źȯ")->setFrameY(1);
				if (WINDTALISMAN->_javelin.count % 15 == 0)
				{
					WINDTALISMAN->_javelin.startRight--;
					if (WINDTALISMAN->_javelin.startRight < 0)
					{
						WINDTALISMAN->_javelin.startRight = 2;
						WINDTALISMAN->setIsUsing(false);
						PLAYER->_isUsingSkill = false;
						PLAYER->_isAttack = false;
						WINDTALISMAN->_javelin.rc.left = 1920;
						WINDTALISMAN->_javelin.rc.right = WINDTALISMAN->_javelin.rc.left + 238;
						WINDTALISMAN->_javelin.rc.top = 1080;
						WINDTALISMAN->_javelin.rc.bottom = WINDTALISMAN->_javelin.rc.top + 91;
					}
					IMAGEMANAGER->findImage("����Ż������źȯ")->setFrameX(WINDTALISMAN->_javelin.startRight);
				}
				IMAGEMANAGER->findImage("����Ż������")->setFrameX(WINDTALISMAN->getStartRight());
			}
		}
	}
	if (SHADESPLIT->getIsUsing())
	{
		SHADESPLIT->_skillCount++;
		if (PLAYER->_isLeft)
		{
			IMAGEMANAGER->findImage("���̵彺�ø�")->setFrameY(0);
			if (SHADESPLIT->_skillCount % 4 == 0)
			{
				SHADESPLIT->setStartLeft(SHADESPLIT->getStartLeft() + 1);
				if (SHADESPLIT->getStartLeft() > 9)
				{
					SHADESPLIT->setIsUsing(false);
					SHADESPLIT->setStartLeft(0);
					PLAYER->_isUsingSkill = false;
					SHADESPLIT->_skillRange.left = 1920;
					SHADESPLIT->_skillRange.right = SHADESPLIT->_skillRange.left + 656;
					SHADESPLIT->_skillRange.top = 1080;
					SHADESPLIT->_skillRange.bottom = SHADESPLIT->_skillRange.top + 381;
				}
				IMAGEMANAGER->findImage("���̵彺�ø�")->setFrameX(SHADESPLIT->getStartLeft());
			}
		}
		else
		{
			IMAGEMANAGER->findImage("���̵彺�ø�")->setFrameY(1);
			if (SHADESPLIT->_skillCount % 4 == 0)
			{
				SHADESPLIT->setStartRight(SHADESPLIT->getStartRight() - 1);
				if (SHADESPLIT->getStartRight() < 0)
				{
					SHADESPLIT->setIsUsing(false);
					SHADESPLIT->setStartRight(9);
					PLAYER->_isUsingSkill = false;
					SHADESPLIT->_skillRange.left = 1920;
					SHADESPLIT->_skillRange.right = SHADESPLIT->_skillRange.left + 656;
					SHADESPLIT->_skillRange.top = 1080;
					SHADESPLIT->_skillRange.bottom = SHADESPLIT->_skillRange.top + 381;
				}
				IMAGEMANAGER->findImage("���̵彺�ø�")->setFrameX(SHADESPLIT->getStartRight());
			}
		}
	}
}
