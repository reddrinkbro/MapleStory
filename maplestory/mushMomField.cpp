#include "stdafx.h"
#include "mushMomField.h"

HRESULT mushMomField::init(void)
{
	setIsInPlayer(false);
	setIsLeft(false);
	setIsRight(false);
	IMAGEMANAGER->addImage("�ӽ����ʵ�", "Map/�ӽ����ʵ�.bmp", 1920, 1080);												//���
	IMAGEMANAGER->addFrameImage("portal", "Map/portal.bmp", 1286, 133, 14, 1, true, RGB(255, 0, 255));					//��Ż
	IMAGEMANAGER->addFrameImage("portal", "Map/portal.bmp", 1286, 133, 14, 1, true, RGB(255, 0, 255));					//��Ż
	IMAGEMANAGER->addFrameImage("�Ķ�����","Monster/BlueMushroom.bmp", 207, 432, 3, 6, true, RGB(255, 0, 255));			//�Ķ�����
	IMAGEMANAGER->addFrameImage("��Ȳ����", "Monster/OrangeMushroom.bmp", 228, 414, 3, 6, true, RGB(255, 0, 255));		//��Ȳ����
	IMAGEMANAGER->addFrameImage("�ӽ���", "Monster/Mushmom.bmp", 1827, 1205, 10, 8, true, RGB(255, 0, 255));			//�ӽ���
	IMAGEMANAGER->addFrameImage("�ӽ�����ų","Monster/MushmomSkill.bmp", 767, 125, 3, 1, true, RGB(255, 0, 255));		//�ӽ�����ų
	IMAGEMANAGER->addImage("�ӽ���ü�¹�", "Monster/UI/�ӽ���ü�¹�.bmp", 750, 34, true, RGB(255, 0, 255));				//�ӽ���ü�¹�
	IMAGEMANAGER->addImage("��ü�¹�", "Monster/UI/���ͺ�ü�¹�.bmp", 710, 10);										//��ü�¹�
	bossHp = RectMake(168, 10, 710, 10);																				//�ӽ�������ü�¹�
	_field[0] = RectMake(0, 1030, 1920, 200);																			//�ٴ� �簢��
	_field[1] = RectMake(0, 375, 500, 50); 																				//�ٴ� �簢��
	_field[2] = RectMake(785, 995, 430, 50);																			//�ٴ� �簢��
	_field[3] = RectMake(907, 560, 120, 50);																			//�ٴ� �簢��
	_field[4] = RectMake(1192, 732, 30, 50);																			//�ٴ� �簢��
	_field[5] = RectMake(1340, 579, 30, 50);																			//�ٴ� �簢��
	_field[6] = RectMake(1359, 885, 30, 50);																			//�ٴ� �簢��
	_field[7] = RectMake(1760, 923, 200, 50);																			//�ٴ� �簢��
	_field[8] = RectMake(1650, 923, 55, 50);																			//�ٴ� �簢��
	_field[9] = RectMake(685, 559, 215, 160);																			//�ٴ� �簢��
	_field[10] = RectMake(630, 779, 20,50);																				//�ٴ� �簢��
	_portal[0].rc = RectMake(1760, 800, 92, 133);																		//��Ż �簢��(��׽ý� ����� ���±�)
	_portal[1].rc = RectMake(60, 897, 92, 133);																			//��Ż �簢��(���� ���±�)
	
	for (int i = 0; i < 2;i++)
	{
		_portal[i].portalFrame = 0;
	}
	_bgSpeedX = _bgSpeedY = 0;
	_deadCount = 0;
	_mushMom = new mushMom;																								//�ӽ��� ����
	return S_OK;
}

void mushMomField::release(void)
{
}

void mushMomField::update(void)
{
	RECT rcTemp;
	_count++;
	PLAYER->_playerRect.rc.top += GRAVITY;			//������ �߷� �ۿ�
	PLAYER->_playerRect.rc.bottom += GRAVITY;
	intersectFeild();								//�簢�� �浹
	portalFrame();									//��Ż ������
	monsterSpawn();									//���� ��ȯ
	monsterIntersect();								//���Ϳ� ��ȣ�ۿ�
	monsterFrame();									//���� ������
	for (int i = 0; i < blueMushroomVec.size();i++)
	{
		blueMushroomVec[i]->_monsterRect.top += GRAVITY;
		blueMushroomVec[i]->_monsterRect.bottom += GRAVITY;
	}
	for (int i = 0; i < orangeMushroomVec.size(); i++)
	{
		orangeMushroomVec[i]->_monsterRect.top += GRAVITY;
		orangeMushroomVec[i]->_monsterRect.bottom += GRAVITY;
	}
	if (_mushMom->isreal && !_mushMom->getIsUsingSkill())
	{
		_mushMom->_monsterRect.top += 3;
		_mushMom->_monsterRect.bottom += 3;
	}
	if (PLAYER->_playerRect.rc.right > 1920)
	{
		PLAYER->_playerRect.rc.left -= 3;
		PLAYER->_playerRect.rc.right -= 3;
	}
	if (_bgSpeedX > 964 && _bgSpeedY > 400 || _bgSpeedY >400 && _bgSpeedX >= 0)
	{
		PLAYER->_isPlayerMoveMap = true;
	}
	if (PLAYER->_playerRect.rc.right > WINSIZEX/2 + 150 && _bgSpeedX <967) //���������� �̵��ϸ� ȭ���� ����´�
	{
		if (PLAYER->_isPlayerMoveMap)
		{
			_bgSpeedX += 3;
			PLAYER->_playerRect.rc.left -= 3;
			PLAYER->_playerRect.rc.right -= 3;
			for (int i = 0; i < 11; i++)				//�ٴ��� �����ϴ� �簢���� �̵�
			{
				_field[i].left -= 3;
				_field[i].right -= 3;
			}
			for (int i = 0; i < 2; i++)					//��Ż�� �̵�
			{
				_portal[i].rc.left -= 3;
				_portal[i].rc.right -= 3;
			}
			for (int i = 0; i < blueMushroomVec.size(); i++)
			{
				blueMushroomVec[i]->_monsterRect.left -= 3;
				blueMushroomVec[i]->_monsterRect.right -= 3;
			}
			for (int i = 0; i < orangeMushroomVec.size(); i++)
			{
				orangeMushroomVec[i]->_monsterRect.left -= 3;
				orangeMushroomVec[i]->_monsterRect.right -= 3;
			}
			
			_mushMom->_monsterRect.left -= 3;
			_mushMom->_monsterRect.right -= 3;
			if (PLAYER->_jumpCount > 2 && !PLAYER->_isLeft)
			{
				_bgSpeedX += 7;
				PLAYER->_playerRect.rc.left -= 7;
				PLAYER->_playerRect.rc.right -= 7;
				for (int i = 0; i < 11;i++)					//�ٴ� �̵�
				{
					_field[i].left -= 7;
					_field[i].right -= 7;
				}
				for (int i = 0; i < 2; i++)					//��Ż�� �̵�
				{
					_portal[i].rc.left -= 7;
					_portal[i].rc.right -= 7;
				}

				for (int i = 0; i < orangeMushroomVec.size(); i++)
				{
					orangeMushroomVec[i]->_monsterRect.left -= 7;
					orangeMushroomVec[i]->_monsterRect.right -= 7;
				}
				for (int i = 0; i < blueMushroomVec.size();i++)
				{
					blueMushroomVec[i]->_monsterRect.left -= 7;
					blueMushroomVec[i]->_monsterRect.right -= 7;
				}
				_mushMom->_monsterRect.left -= 7;
				_mushMom->_monsterRect.right -= 7;
			}
		}
		else
		{
			_bgSpeedX += 9;
			PLAYER->_playerRect.rc.left -= 9;
			PLAYER->_playerRect.rc.right -= 9;
			for (int i = 0; i < 11; i++)				//�ٴ��� �����ϴ� �簢���� �̵�
			{
				_field[i].left -= 9;
				_field[i].right -= 9;
			}
			for (int i = 0; i < 2; i++)					//��Ż�� �̵�
			{
				_portal[i].rc.left -= 9;
				_portal[i].rc.right -= 9;
			}
			for (int i = 0; i < blueMushroomVec.size(); i++)
			{
				blueMushroomVec[i]->_monsterRect.left -= 9;
				blueMushroomVec[i]->_monsterRect.right -= 9;
			}
			for (int i = 0; i < orangeMushroomVec.size(); i++)
			{
				orangeMushroomVec[i]->_monsterRect.left -= 9;
				orangeMushroomVec[i]->_monsterRect.right -= 9;
			}
			
			_mushMom->_monsterRect.left -= 9;
			_mushMom->_monsterRect.right -= 9;
			
		}
	}
	else if (PLAYER->_playerRect.rc.left < WINSIZEX / 2 - 150 && _bgSpeedX >0)//�������� �̵��ϸ� ȭ���� ����´�
	{
		if (PLAYER->_isPlayerMoveMap)
		{
			_bgSpeedX -= 3;
			PLAYER->_playerRect.rc.left += 3;
			PLAYER->_playerRect.rc.right += 3;
			for (int i = 0; i < 11; i++)
			{
				_field[i].left += 3;
				_field[i].right += 3;
			}
			for (int i = 0; i < 2; i++)
			{
				_portal[i].rc.left += 3;
				_portal[i].rc.right += 3;
			}
			for (int i = 0; i < blueMushroomVec.size(); i++)
			{
				blueMushroomVec[i]->_monsterRect.left += 3;
				blueMushroomVec[i]->_monsterRect.right += 3;
			}
			for (int i = 0; i < orangeMushroomVec.size(); i++)
			{
				orangeMushroomVec[i]->_monsterRect.left += 3;
				orangeMushroomVec[i]->_monsterRect.right += 3;
			}
			
			_mushMom->_monsterRect.left += 3;
			_mushMom->_monsterRect.right += 3;
			if (PLAYER->_jumpCount > 2 && PLAYER->_isLeft)
			{
				_bgSpeedX -= 7;
				PLAYER->_playerRect.rc.left += 7;
				PLAYER->_playerRect.rc.right += 7;
				for (int i = 0; i < 11;i++)					//�ٴ� �̵�
				{
					_field[i].left += 7;
					_field[i].right += 7;
				}
				for (int i = 0; i < 2; i++)					//��Ż�� �̵�
				{
					_portal[i].rc.left += 7;
					_portal[i].rc.right += 7;
				}

				for (int i = 0; i < orangeMushroomVec.size(); i++)
				{
					orangeMushroomVec[i]->_monsterRect.left += 7;
					orangeMushroomVec[i]->_monsterRect.right += 7;
				}
				for (int i = 0; i < blueMushroomVec.size();i++)
				{
					blueMushroomVec[i]->_monsterRect.left += 7;
					blueMushroomVec[i]->_monsterRect.right += 7;
				}
				_mushMom->_monsterRect.left += 7;
				_mushMom->_monsterRect.right += 7;
			}
		}
		else
		{
			_bgSpeedX -= 9;
			PLAYER->_playerRect.rc.left += 9;
			PLAYER->_playerRect.rc.right += 9;
			for (int i = 0; i < 11; i++)
			{
				_field[i].left += 9;
				_field[i].right += 9;
			}
			for (int i = 0; i < 2; i++)
			{
				_portal[i].rc.left += 9;
				_portal[i].rc.right += 9;
			}
			for (int i = 0; i < blueMushroomVec.size(); i++)
			{
				blueMushroomVec[i]->_monsterRect.left += 9;
				blueMushroomVec[i]->_monsterRect.right += 9;
			}
			for (int i = 0; i < orangeMushroomVec.size(); i++)
			{
				orangeMushroomVec[i]->_monsterRect.left += 9;
				orangeMushroomVec[i]->_monsterRect.right += 9;
			}
			
			_mushMom->_monsterRect.left += 9;
			_mushMom->_monsterRect.right += 9;
			
		}
	}
	else if (PLAYER->_playerRect.rc.bottom > WINSIZEY / 2 + 150 && _bgSpeedY < 445)//�Ʒ������� �̵��ϸ� ȭ���� ����´�
	{
		
		_bgSpeedY += 9;
		PLAYER->_playerRect.rc.top -= 9;
		PLAYER->_playerRect.rc.bottom -= 9;
		for (int i = 0; i < 11; i++)
		{
			_field[i].top -= 9;
			_field[i].bottom -= 9;
		}
		for (int i = 0; i < 2; i++)
		{
			_portal[i].rc.top -= 9;
			_portal[i].rc.bottom -= 9;
		}
		for (int i = 0; i < blueMushroomVec.size(); i++)
		{
			blueMushroomVec[i]->_monsterRect.top -= 9;
			blueMushroomVec[i]->_monsterRect.bottom -= 9;
		}
		for (int i = 0; i < orangeMushroomVec.size(); i++)
		{
			orangeMushroomVec[i]->_monsterRect.top -= 9;
			orangeMushroomVec[i]->_monsterRect.bottom -= 9;
		}
			
		_mushMom->_monsterRect.top -= 9;
		_mushMom->_monsterRect.bottom -= 9;

	}
	else if (PLAYER->_playerRect.rc.top < WINSIZEY / 2 - 150 && _bgSpeedY >0)//�������� �̵��ϸ� ȭ���� ����´�
	{
		if (PLAYER->_isPlayerMoveMap)
		{
			_bgSpeedY -= 3;
			PLAYER->_playerRect.rc.top += 3;
			PLAYER->_playerRect.rc.bottom += 3;
			for (int i = 0; i < 11; i++)
			{
				_field[i].top += 3;
				_field[i].bottom += 3;
			}
			for (int i = 0; i < 2; i++)
			{
				_portal[i].rc.top += 3;
				_portal[i].rc.bottom += 3;
			}
			for (int i = 0; i < blueMushroomVec.size(); i++)
			{
				blueMushroomVec[i]->_monsterRect.top += 3;
				blueMushroomVec[i]->_monsterRect.bottom += 3;
			}
			for (int i = 0; i < orangeMushroomVec.size(); i++)
			{
				orangeMushroomVec[i]->_monsterRect.top += 3;
				orangeMushroomVec[i]->_monsterRect.bottom += 3;
			}

			_mushMom->_monsterRect.top += 3;
			_mushMom->_monsterRect.bottom += 3;
		}
		else
		{
			_bgSpeedY -= 9;
			PLAYER->_playerRect.rc.top += 9;
			PLAYER->_playerRect.rc.bottom += 9;
			for (int i = 0; i < 11; i++)
			{
				_field[i].top += 9;
				_field[i].bottom += 9;
			}
			for (int i = 0; i < 2; i++)
			{
				_portal[i].rc.top += 9;
				_portal[i].rc.bottom += 9;
			}
			for (int i = 0; i < blueMushroomVec.size(); i++)
			{
				blueMushroomVec[i]->_monsterRect.top += 9;
				blueMushroomVec[i]->_monsterRect.bottom += 9;
			}
			for (int i = 0; i < orangeMushroomVec.size(); i++)
			{
				orangeMushroomVec[i]->_monsterRect.top += 9;
				orangeMushroomVec[i]->_monsterRect.bottom += 9;
			}
			
			_mushMom->_monsterRect.top += 9;
			_mushMom->_monsterRect.bottom += 9;
			
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (IntersectRect(&rcTemp, &PLAYER->_playerRect.rc, &_portal[0].rc))
		{
			setIsRight(true);
		}
		if (IntersectRect(&rcTemp, &PLAYER->_playerRect.rc, &_portal[1].rc) &&_mushMom->getIsDie())
		{
			setIsLeft(true);
		}
	}
	if (PLAYER->_moveCount == 1) //��׽ý� ����Ϳ��� ������ ��ž������ ��Ÿ��
	{
		PLAYER->_playerRect.rc.left = _portal[0].rc.left;
		PLAYER->_playerRect.rc.right = PLAYER->_playerRect.rc.left + 79;
		PLAYER->_playerRect.rc.bottom = _portal[0].rc.top;
		PLAYER->_playerRect.rc.top = PLAYER->_playerRect.rc.bottom - 85;
		PLAYER->_moveCount = 0;
	}
	else if (PLAYER->_moveCount == -1)//�������� ������ ��ž������ ��Ÿ��
	{
		PLAYER->_playerRect.rc.left = _portal[1].rc.left;
		PLAYER->_playerRect.rc.right = PLAYER->_playerRect.rc.left + 79;
		PLAYER->_playerRect.rc.bottom = _portal[1].rc.top;
		PLAYER->_playerRect.rc.top = PLAYER->_playerRect.rc.bottom - 85;
		PLAYER->_moveCount = 0;
	}
}

void mushMomField::render(HDC hdc)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	char str[128];
	IMAGEMANAGER->loopRender("�ӽ����ʵ�", getMemDC(), &RectMake(0, 0, 1920, 1080), _bgSpeedX, _bgSpeedY);
	for (int i = 0; i < 2; i++)
	{
		IMAGEMANAGER->frameRender("portal", getMemDC(), _portal[i].rc.left, _portal[i].rc.top);
	}
	if (_mushMom->isreal)
	{
		IMAGEMANAGER->frameRender("�ӽ���", getMemDC(), _mushMom->_monsterRect.left, _mushMom->_monsterRect.top);
		if (_mushMom->getStartFrameX() > 8)
		{
			IMAGEMANAGER->frameRender("�ӽ�����ų", getMemDC(), _mushMom->_skill.rc.left, _mushMom->_skill.rc.top);				//�ӽ�����ų
		}
		IMAGEMANAGER->render("��ü�¹�", getMemDC(), 168, 12);
		bossHpColor = CreateSolidBrush(RGB(255, 0, 0));
		FillRect(getMemDC(), &bossHp, bossHpColor);
		IMAGEMANAGER->render("�ӽ���ü�¹�", getMemDC(), 130, 8);
	}
	for (int i = 0; i < blueMushroomVec.size();i++)
	{
		
		IMAGEMANAGER->frameRender("�Ķ�����", getMemDC(), blueMushroomVec[i]->_monsterRect.left, blueMushroomVec[i]->_monsterRect.top, blueMushroomVec[i]->getStartFrameX(), blueMushroomVec[i]->getStartFrameY());
	}
	for (int i = 0; i < orangeMushroomVec.size(); i++)
	{

		IMAGEMANAGER->frameRender("��Ȳ����", getMemDC(), orangeMushroomVec[i]->_monsterRect.left, orangeMushroomVec[i]->_monsterRect.top, orangeMushroomVec[i]->getStartFrameX(), orangeMushroomVec[i]->getStartFrameY());
	}
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(getMemDC(), _mushMom->_skill.rc.left, _mushMom->_skill.rc.top, _mushMom->_skill.rc.right, _mushMom->_skill.rc.bottom);
	}

	this->getBackBuffer()->render(getHDC());
}

void mushMomField::intersectFeild(void)
{
	RECT rcTemp;
	for (int i = 0;i < 11;i++)
	{
		if (IntersectRect(&rcTemp, &PLAYER->_playerRect.rc, &_field[i]))
		{
			if (i != 2 && i != 8 && i != 9)
			{
				PLAYER->_playerRect.rc.bottom = _field[i].top;
				PLAYER->_playerRect.rc.top = PLAYER->_playerRect.rc.bottom - 85;
				PLAYER->_playerRect.time = 0;
				PLAYER->_isJump = false;
				PLAYER->_isHit = false;
				PLAYER->_jumpCount = 0;
			}
			else if (PLAYER->_playerRect.rc.bottom < _field[i].bottom && i == 2) //���� �ٸ� �κ�
			{
				PLAYER->_playerRect.rc.bottom = _field[i].top;
				PLAYER->_playerRect.rc.top = PLAYER->_playerRect.rc.bottom - 85;
				PLAYER->_playerRect.time = 0;
				PLAYER->_isJump = false;
				PLAYER->_isHit = false;
				PLAYER->_jumpCount = 0;
			}
			else if ((i == 8 || i == 9) && PLAYER->_isMove && !PLAYER->_isLeft) //�밢�� �ö󰡱�
			{
				PLAYER->_playerRect.rc.top = -sinf(PI / 3) * 12.8 + PLAYER->_playerRect.rc.top;
				PLAYER->_playerRect.rc.bottom = -sinf(PI / 3) * 12.8 + PLAYER->_playerRect.rc.bottom;
				PLAYER->_playerRect.time = 0;
				PLAYER->_isJump = false;
				PLAYER->_isHit = false;
				PLAYER->_jumpCount = 0;
			}
			else if ((i == 8 || i == 9) && !PLAYER->_isMove ) //�밢�� ��������
			{
				PLAYER->_playerRect.rc.top = PLAYER->_playerRect.rc.top - sinf(PI / 3) * GRAVITY;
				PLAYER->_playerRect.rc.bottom = PLAYER->_playerRect.rc.bottom - sinf(PI / 3) * GRAVITY;
				PLAYER->_playerRect.time = 0;
				PLAYER->_isJump = false;
				PLAYER->_isHit = false;
				PLAYER->_jumpCount = 0;
			}
			else if ((i == 8 || i == 9) && PLAYER->_isMove && PLAYER->_isLeft) //�밢�� ��������
			{
				PLAYER->_playerRect.rc.top = -sinf(PI / 3) * 6.8 + PLAYER->_playerRect.rc.top;
				PLAYER->_playerRect.rc.bottom = -sinf(PI / 3) * 6.8 + PLAYER->_playerRect.rc.bottom;
				PLAYER->_playerRect.time = 0;
				PLAYER->_isJump = false;
				PLAYER->_isHit = false;
				PLAYER->_jumpCount = 0;
			}
		}
		for (int j = 0; j < blueMushroomVec.size(); j++)
		{
			if (IntersectRect(&rcTemp, &blueMushroomVec[j]->_monsterRect, &_field[i]))
			{
				if (blueMushroomVec[j]->_monsterRect.bottom > _field[i].top && i == 0 || i == 7)
				{
					blueMushroomVec[j]->_monsterRect.bottom = _field[i].top;
					blueMushroomVec[j]->_monsterRect.top = blueMushroomVec[j]->_monsterRect.bottom - 72;
					blueMushroomVec[j]->setTime(0);
					blueMushroomVec[j]->setIsJump(false);
				}
				else if (blueMushroomVec[j]->_monsterRect.bottom < _field[i].bottom && i == 2) //���� �ٸ� �κ�
				{
					blueMushroomVec[j]->_monsterRect.bottom = _field[i].top;
					blueMushroomVec[j]->_monsterRect.top = blueMushroomVec[j]->_monsterRect.bottom - 72;
					blueMushroomVec[j]->setTime(0);
					blueMushroomVec[j]->setIsJump(false);
				}
				else if (i == 8 && blueMushroomVec[j]->getIsMove() && !blueMushroomVec[j]->getIsLeft()) //�밢�� �ö󰡱�
				{
					blueMushroomVec[j]->_monsterRect.top = -sinf(PI / 3) * (GRAVITY + 1) + blueMushroomVec[j]->_monsterRect.top;
					blueMushroomVec[j]->_monsterRect.bottom = -sinf(PI / 3) *(GRAVITY + 1) + blueMushroomVec[j]->_monsterRect.bottom;
					blueMushroomVec[j]->setTime(0);
					blueMushroomVec[j]->setIsJump(false);
				}
				else if (i == 8 && !blueMushroomVec[j]->getIsMove() && !!blueMushroomVec[j]->getIsLeft()) //�밢�� ��������
				{
					blueMushroomVec[j]->_monsterRect.top = blueMushroomVec[j]->_monsterRect.top - sinf(PI / 3) * GRAVITY;
					blueMushroomVec[j]->_monsterRect.bottom = blueMushroomVec[j]->_monsterRect.bottom - sinf(PI / 3) * GRAVITY;
					blueMushroomVec[j]->setTime(0);
					blueMushroomVec[j]->setIsJump(false);
				}
				else if (i == 8 && blueMushroomVec[j]->getIsMove() && blueMushroomVec[j]->getIsLeft()) //�밢�� ��������
				{
					blueMushroomVec[j]->_monsterRect.top = -sinf(PI / 3) * (GRAVITY - 1) + blueMushroomVec[j]->_monsterRect.top;
					blueMushroomVec[j]->_monsterRect.bottom = -sinf(PI / 3) * (GRAVITY - 1) + blueMushroomVec[j]->_monsterRect.bottom;
					blueMushroomVec[j]->setTime(0);
					blueMushroomVec[j]->setIsJump(false);
				}
			}
		}
		for (int j = 0; j < orangeMushroomVec.size(); j++)
		{
			if (IntersectRect(&rcTemp, &orangeMushroomVec[j]->_monsterRect, &_field[i]))
			{
				if (orangeMushroomVec[j]->_monsterRect.bottom > _field[i].top && i == 0 || i == 7)
				{
					orangeMushroomVec[j]->_monsterRect.bottom = _field[i].top;
					orangeMushroomVec[j]->_monsterRect.top = orangeMushroomVec[j]->_monsterRect.bottom - 72;
					orangeMushroomVec[j]->setTime(0);
					orangeMushroomVec[j]->setIsJump(false);
				}
				else if (orangeMushroomVec[j]->_monsterRect.bottom < _field[i].bottom && i == 2) //���� �ٸ� �κ�
				{
					orangeMushroomVec[j]->_monsterRect.bottom = _field[i].top;
					orangeMushroomVec[j]->_monsterRect.top = orangeMushroomVec[j]->_monsterRect.bottom - 72;
					orangeMushroomVec[j]->setTime(0);
					orangeMushroomVec[j]->setIsJump(false);
				}
				else if (i == 8 && orangeMushroomVec[j]->getIsMove() && !orangeMushroomVec[j]->getIsLeft()) //�밢�� �ö󰡱�
				{
					orangeMushroomVec[j]->_monsterRect.top = -sinf(PI / 3) * (GRAVITY + 1) + orangeMushroomVec[j]->_monsterRect.top;
					orangeMushroomVec[j]->_monsterRect.bottom = -sinf(PI / 3) *(GRAVITY + 1) + orangeMushroomVec[j]->_monsterRect.bottom;
					orangeMushroomVec[j]->setTime(0);
					orangeMushroomVec[j]->setIsJump(false);
				}
				else if (i == 8 && !orangeMushroomVec[j]->getIsMove() && !!orangeMushroomVec[j]->getIsLeft()) //�밢�� ��������
				{
					orangeMushroomVec[j]->_monsterRect.top = orangeMushroomVec[j]->_monsterRect.top - sinf(PI / 3) * GRAVITY;
					orangeMushroomVec[j]->_monsterRect.bottom = orangeMushroomVec[j]->_monsterRect.bottom - sinf(PI / 3) * GRAVITY;
					orangeMushroomVec[j]->setTime(0);
					orangeMushroomVec[j]->setIsJump(false);
				}
				else if (i == 8 && orangeMushroomVec[j]->getIsMove() && orangeMushroomVec[j]->getIsLeft()) //�밢�� ��������
				{
					orangeMushroomVec[j]->_monsterRect.top = -sinf(PI / 3) * (GRAVITY - 1) + orangeMushroomVec[j]->_monsterRect.top;
					orangeMushroomVec[j]->_monsterRect.bottom = -sinf(PI / 3) * (GRAVITY - 1) + orangeMushroomVec[j]->_monsterRect.bottom;
					orangeMushroomVec[j]->setTime(0);
					orangeMushroomVec[j]->setIsJump(false);
				}
			}
		}
		if (_mushMom->isreal)
		{
			if (IntersectRect(&rcTemp, &_mushMom->_monsterRect, &_field[i]) &&!_mushMom->getIsUsingSkill())
			{
				if (_mushMom->_monsterRect.bottom > _field[i].top && i == 0 || i == 7)
				{
					_mushMom->_monsterRect.bottom = _field[i].top;
					_mushMom->_monsterRect.top = _mushMom->_monsterRect.bottom - 150;
				}
				else if (_mushMom->_monsterRect.bottom < _field[i].bottom && i == 2) //���� �ٸ� �κ�
				{
					_mushMom->_monsterRect.bottom = _field[i].top;
					_mushMom->_monsterRect.top = _mushMom->_monsterRect.bottom - 150;
				}
			}
		}
	}
}

void mushMomField::portalFrame(void)
{
	for (int i = 0; i < 2;i++)
	{
		IMAGEMANAGER->findImage("portal")->setFrameY(0);
		if (_count % 7 == 0)
		{
			_portal[i].portalFrame++;
			if (_portal[i].portalFrame > 13)
			{
				_portal[i].portalFrame = 0;
			}
			IMAGEMANAGER->findImage("portal")->setFrameX(_portal[i].portalFrame);
		}
	}
}

void mushMomField::monsterSpawn(void)
{
	RECT rcTemp;
	if (blueMushroomVec.size() < 3)
	{
		_blueMushroom = new blueMushroom;
		blueMushroomVec.push_back(_blueMushroom);
	}
	for (int i = 0; i < blueMushroomVec.size(); i++)
	{
		if (blueMushroomVec[i]->getIsJump())	//�Ķ����� ����
		{
			blueMushroomVec[i]->setTime(blueMushroomVec[i]->getTime() + 0.05);
			blueMushroomVec[i]->jump();
		}
		if (blueMushroomVec[i]->_monsterRect.left > _field[0].left && blueMushroomVec[i]->_monsterRect.right < _field[0].right)		//�Ķ����� �̵��Ҽ��ִ� ��
		{
			blueMushroomVec[i]->monsterMove();
			if (blueMushroomVec[i]->_monsterRect.right >= _field[0].right - 300)
			{
				blueMushroomVec[i]->setIsJump(false);
				blueMushroomVec[i]->setTime(0);
			}
		}
		else if (blueMushroomVec[i]->_monsterRect.left <= _field[0].left || blueMushroomVec[i]->_monsterRect.right >= _field[0].right)	//���� �ε�ġ�� �ݴ�� �̵�
		{
			if (blueMushroomVec[i]->getIsLeft())
			{
				blueMushroomVec[i]->setIsLeft(false);
				blueMushroomVec[i]->_monsterRect.left += 2;
				blueMushroomVec[i]->_monsterRect.right += 2;
				blueMushroomVec[i]->setDistance(RND->getFromIntTo(50,150));
			}
			else
			{
				blueMushroomVec[i]->setIsLeft(true);
				blueMushroomVec[i]->_monsterRect.left -= 2;
				blueMushroomVec[i]->_monsterRect.right -= 2;
				blueMushroomVec[i]->setDistance(RND->getFromIntTo(50, 150));
			}
		}
	}
	if (orangeMushroomVec.size() < 3)
	{
		_orangeMushroom = new OrangeMushroom;
		orangeMushroomVec.push_back(_orangeMushroom);
	}
	for (int i = 0; i < orangeMushroomVec.size(); i++)
	{
		if (orangeMushroomVec[i]->getIsJump())	//��Ȳ���� ����
		{
			orangeMushroomVec[i]->setTime(orangeMushroomVec[i]->getTime() + 0.05);
			orangeMushroomVec[i]->jump();
		}
		if (orangeMushroomVec[i]->_monsterRect.left > _field[0].left && orangeMushroomVec[i]->_monsterRect.right < _field[0].right)		//��Ȳ���� �̵��Ҽ��ִ� ��
		{
			orangeMushroomVec[i]->monsterMove();
			if (orangeMushroomVec[i]->_monsterRect.right >= _field[0].right - 300)
			{
				orangeMushroomVec[i]->setIsJump(false);
				orangeMushroomVec[i]->setTime(0);
			}
		}
		else if (orangeMushroomVec[i]->_monsterRect.left <= _field[0].left || orangeMushroomVec[i]->_monsterRect.right >= _field[0].right)	//���� �ε�ġ�� �ݴ�� �̵�
		{
			if (orangeMushroomVec[i]->getIsLeft())
			{
				orangeMushroomVec[i]->setIsLeft(false);
				orangeMushroomVec[i]->_monsterRect.left += 2;
				orangeMushroomVec[i]->_monsterRect.right += 2;
				orangeMushroomVec[i]->setDistance(RND->getFromIntTo(50, 150));
			}
			else
			{
				orangeMushroomVec[i]->setIsLeft(true);
				orangeMushroomVec[i]->_monsterRect.left -= 2;
				orangeMushroomVec[i]->_monsterRect.right -= 2;
				orangeMushroomVec[i]->setDistance(RND->getFromIntTo(50, 150));
			}
		}
	}
	if (_deadCount > 5)
	{
		_mushMom->isreal = true;
	}
	if (_mushMom->isreal)
	{
		if (_mushMom->_monsterRect.left > _field[0].left && _mushMom->_monsterRect.right < _field[2].right)		//��Ȳ���� �̵��Ҽ��ִ� ��
		{
			_mushMom->monsterMove();
		}
		else if (_mushMom->_monsterRect.left <= _field[0].left || _mushMom->_monsterRect.right >= _field[2].right)
		{
			if (_mushMom->getIsLeft())
			{
				_mushMom->setIsLeft(false);
				_mushMom->_monsterRect.left += 2;
				_mushMom->_monsterRect.right += 2;
				_mushMom->setDistance(RND->getFromIntTo(50, 150));
			}
			else
			{
				_mushMom->setIsLeft(true);
				_mushMom->_monsterRect.left -= 2;
				_mushMom->_monsterRect.right -= 2;
				_mushMom->setDistance(RND->getFromIntTo(50, 150));
			}
		}
		if (_mushMom->_skill.skillend)
		{
			_mushMom->_skill.coolDownTime--;
		}
		if (IntersectRect(&rcTemp, &_mushMom->_monsterRect, &PLAYER->_playerRect.rc) && _mushMom->_skill.coolDownTime< 0)
		{
			_mushMom->setIsUsingSkill(true);
			_mushMom->usingSkill();
			_mushMom->_skill.coolDownTime = 100;
		}
		
	}
}

void mushMomField::monsterFrame(void)
{
	//�Ķ�����
	for (int i = 0; i < blueMushroomVec.size();i++)
	{
		blueMushroomVec[i]->_monsterCount++;
		if (blueMushroomVec[i]->getIsLeft())											//�Ķ������� ������ ����
		{
			if (blueMushroomVec[i]->getIsMove() || blueMushroomVec[i]->getIsChase())	//�Ķ������� �����̰ų� �i�ư���
			{
				blueMushroomVec[i]->setStartFrameY(1);
				IMAGEMANAGER->findImage("�Ķ�����")->setFrameY(blueMushroomVec[i]->getStartFrameY());
				if (blueMushroomVec[i]->_monsterCount % 15 == 0)
				{
					blueMushroomVec[i]->setStartFrameX(blueMushroomVec[i]->getStartFrameX() + 1);
					if (blueMushroomVec[i]->getStartFrameX() > 2)
					{
						blueMushroomVec[i]->setStartFrameX(0);
					}
					IMAGEMANAGER->findImage("�Ķ�����")->setFrameX(blueMushroomVec[i]->getStartFrameX());
				}
			}
			
			else if (blueMushroomVec[i]->getIsHit())									//�Ķ������� ���ݴ��Ҷ�
			{
				blueMushroomVec[i]->setStartFrameX(2);
				blueMushroomVec[i]->setStartFrameY(0);
				IMAGEMANAGER->findImage("�Ķ�����")->setFrameX(blueMushroomVec[i]->getStartFrameX());
				IMAGEMANAGER->findImage("�Ķ�����")->setFrameY(blueMushroomVec[i]->getStartFrameY());
			}
			else if (blueMushroomVec[i]->getIsDie())									//�Ķ������� ������
			{
				blueMushroomVec[i]->setStartFrameY(2);
				IMAGEMANAGER->findImage("�Ķ�����")->setFrameY(blueMushroomVec[i]->getStartFrameY());
				if (blueMushroomVec[i]->_monsterCount % 18 == 0)
				{
					blueMushroomVec[i]->setStartFrameX(blueMushroomVec[i]->getStartFrameX() + 1);
					if (blueMushroomVec[i]->getStartFrameX() > 2)
					{
						blueMushroomVec[i]->setStartFrameX(2);
						blueMushroomVec.erase(blueMushroomVec.begin() + i);
						_deadCount++;
						break;
					}
					IMAGEMANAGER->findImage("�Ķ�����")->setFrameX(blueMushroomVec[i]->getStartFrameX());
				}
			}
			else if (blueMushroomVec[i]->getIsJump())
			{
				blueMushroomVec[i]->setStartFrameX(1);
				blueMushroomVec[i]->setStartFrameY(1);
				IMAGEMANAGER->findImage("�Ķ�����")->setFrameX(blueMushroomVec[i]->getStartFrameX());
				IMAGEMANAGER->findImage("�Ķ�����")->setFrameY(blueMushroomVec[i]->getStartFrameY());
			}
			else																		//�Ķ������� ������ ������
			{
				if (blueMushroomVec[i]->_monsterCount % 31 == 0)
				{
					blueMushroomVec[i]->setStartFrameX(0);
					blueMushroomVec[i]->setStartFrameY(0);
					IMAGEMANAGER->findImage("�Ķ�����")->setFrameX(blueMushroomVec[i]->getStartFrameX());
					IMAGEMANAGER->findImage("�Ķ�����")->setFrameY(blueMushroomVec[i]->getStartFrameY());
				}
				else if (blueMushroomVec[i]->_monsterCount % 37 == 0)
				{
					blueMushroomVec[i]->setStartFrameX(1);
					blueMushroomVec[i]->setStartFrameY(0);
					IMAGEMANAGER->findImage("�Ķ�����")->setFrameX(blueMushroomVec[i]->getStartFrameX());
					IMAGEMANAGER->findImage("�Ķ�����")->setFrameY(blueMushroomVec[i]->getStartFrameY());
				}

			}
		}
		else																			//�Ķ������� �������� ����
		{
			if (blueMushroomVec[i]->getIsMove() || blueMushroomVec[i]->getIsChase())	//�Ķ������� �����̰ų� �i�ư���
			{
				blueMushroomVec[i]->setStartFrameY(4);
				IMAGEMANAGER->findImage("�Ķ�����")->setFrameY(blueMushroomVec[i]->getStartFrameY());
				if (blueMushroomVec[i]->_monsterCount % 15 == 0)
				{
					blueMushroomVec[i]->setStartFrameX(blueMushroomVec[i]->getStartFrameX() + 1);
					if (blueMushroomVec[i]->getStartFrameX() > 2)
					{
						blueMushroomVec[i]->setStartFrameX(0);
					}
					IMAGEMANAGER->findImage("�Ķ�����")->setFrameX(blueMushroomVec[i]->getStartFrameX());
				}
			}
			
			else if (blueMushroomVec[i]->getIsHit())									//�Ķ������� ���ݴ��Ҷ�
			{
				blueMushroomVec[i]->setStartFrameX(2);
				blueMushroomVec[i]->setStartFrameY(3);
				IMAGEMANAGER->findImage("�Ķ�����")->setFrameX(blueMushroomVec[i]->getStartFrameX());
				IMAGEMANAGER->findImage("�Ķ�����")->setFrameY(blueMushroomVec[i]->getStartFrameY());
			}
			else if (blueMushroomVec[i]->getIsDie())									//�Ķ������� ������
			{
				blueMushroomVec[i]->setStartFrameY(5);
				IMAGEMANAGER->findImage("�Ķ�����")->setFrameY(blueMushroomVec[i]->getStartFrameY());
				if (blueMushroomVec[i]->_monsterCount % 18 == 0)
				{
					blueMushroomVec[i]->setStartFrameX(blueMushroomVec[i]->getStartFrameX() + 1);
					if (blueMushroomVec[i]->getStartFrameX() > 2)
					{
						blueMushroomVec[i]->setStartFrameX(2);
						blueMushroomVec.erase(blueMushroomVec.begin() + i);
						_deadCount++;
						break;
					}
					IMAGEMANAGER->findImage("�Ķ�����")->setFrameX(blueMushroomVec[i]->getStartFrameX());
				}
			}
			else if (blueMushroomVec[i]->getIsJump())
			{
				blueMushroomVec[i]->setStartFrameX(1);
				blueMushroomVec[i]->setStartFrameY(4);
				IMAGEMANAGER->findImage("�Ķ�����")->setFrameX(blueMushroomVec[i]->getStartFrameX());
				IMAGEMANAGER->findImage("�Ķ�����")->setFrameY(blueMushroomVec[i]->getStartFrameY());
			}
			else 																		//�Ķ������� ������ ������
			{

				if (blueMushroomVec[i]->_monsterCount % 31 == 0)
				{
					blueMushroomVec[i]->setStartFrameX(1);
					blueMushroomVec[i]->setStartFrameY(3);
					IMAGEMANAGER->findImage("�Ķ�����")->setFrameX(blueMushroomVec[i]->getStartFrameX());
					IMAGEMANAGER->findImage("�Ķ�����")->setFrameY(blueMushroomVec[i]->getStartFrameY());

				}
				else if (blueMushroomVec[i]->_monsterCount % 37 == 0)
				{
					blueMushroomVec[i]->setStartFrameX(0);
					blueMushroomVec[i]->setStartFrameY(3);
					IMAGEMANAGER->findImage("�Ķ�����")->setFrameX(blueMushroomVec[i]->getStartFrameX());
					IMAGEMANAGER->findImage("�Ķ�����")->setFrameY(blueMushroomVec[i]->getStartFrameY());
				}
			}
		}
	}
	//��Ȳ����
	for (int i = 0; i < orangeMushroomVec.size();i++)
	{
		orangeMushroomVec[i]->_monsterCount++;
		if (orangeMushroomVec[i]->getIsLeft())												//��Ȳ������ ������ ����
		{
			if (orangeMushroomVec[i]->getIsMove() || orangeMushroomVec[i]->getIsChase())	//��Ȳ������ �����̰ų� �i�ư���
			{
				orangeMushroomVec[i]->setStartFrameY(1);
				IMAGEMANAGER->findImage("��Ȳ����")->setFrameY(orangeMushroomVec[i]->getStartFrameY());
				if (orangeMushroomVec[i]->_monsterCount % 15 == 0)
				{
					orangeMushroomVec[i]->setStartFrameX(orangeMushroomVec[i]->getStartFrameX() + 1);
					if (orangeMushroomVec[i]->getStartFrameX() > 2)
					{
						orangeMushroomVec[i]->setStartFrameX(0);
					}
					IMAGEMANAGER->findImage("��Ȳ����")->setFrameX(orangeMushroomVec[i]->getStartFrameX());
				}
			}
			
			else if (orangeMushroomVec[i]->getIsHit())									//��Ȳ������ ���ݴ��Ҷ�
			{
				orangeMushroomVec[i]->setStartFrameX(2);
				orangeMushroomVec[i]->setStartFrameY(0);
				IMAGEMANAGER->findImage("��Ȳ����")->setFrameX(orangeMushroomVec[i]->getStartFrameX());
				IMAGEMANAGER->findImage("��Ȳ����")->setFrameY(orangeMushroomVec[i]->getStartFrameY());
			}
			else if (orangeMushroomVec[i]->getIsDie())									//��Ȳ������ ������
			{
				orangeMushroomVec[i]->setStartFrameY(2);
				IMAGEMANAGER->findImage("��Ȳ����")->setFrameY(orangeMushroomVec[i]->getStartFrameY());
				if (orangeMushroomVec[i]->_monsterCount % 18 == 0)
				{
					orangeMushroomVec[i]->setStartFrameX(orangeMushroomVec[i]->getStartFrameX() + 1);
					if (orangeMushroomVec[i]->getStartFrameX() > 2)
					{
						orangeMushroomVec[i]->setStartFrameX(2);
						orangeMushroomVec.erase(orangeMushroomVec.begin() + i);
						_deadCount++;
						break;
					}
					IMAGEMANAGER->findImage("��Ȳ����")->setFrameX(orangeMushroomVec[i]->getStartFrameX());
				}
			}
			else if (orangeMushroomVec[i]->getIsJump())
			{
				orangeMushroomVec[i]->setStartFrameX(1);
				orangeMushroomVec[i]->setStartFrameY(1);
				IMAGEMANAGER->findImage("��Ȳ����")->setFrameX(orangeMushroomVec[i]->getStartFrameX());
				IMAGEMANAGER->findImage("��Ȳ����")->setFrameY(orangeMushroomVec[i]->getStartFrameY());
			}
			else 																			//��Ȳ������ ������ ������
			{

				if (orangeMushroomVec[i]->_monsterCount % 31 == 0)
				{
					orangeMushroomVec[i]->setStartFrameX(0);
					orangeMushroomVec[i]->setStartFrameY(0);
					IMAGEMANAGER->findImage("��Ȳ����")->setFrameX(orangeMushroomVec[i]->getStartFrameX());
					IMAGEMANAGER->findImage("��Ȳ����")->setFrameY(orangeMushroomVec[i]->getStartFrameY());
				}
				else if (orangeMushroomVec[i]->_monsterCount % 37 == 0)
				{
					orangeMushroomVec[i]->setStartFrameX(1);
					orangeMushroomVec[i]->setStartFrameY(0);
					IMAGEMANAGER->findImage("��Ȳ����")->setFrameX(orangeMushroomVec[i]->getStartFrameX());
					IMAGEMANAGER->findImage("��Ȳ����")->setFrameY(orangeMushroomVec[i]->getStartFrameY());
				}

			}
		}
		else																				//��Ȳ������ �������� ����
		{
			if (orangeMushroomVec[i]->getIsMove() || orangeMushroomVec[i]->getIsChase())	//��Ȳ������ �����̰ų� �i�ư���
			{
				orangeMushroomVec[i]->setStartFrameY(4);
				IMAGEMANAGER->findImage("��Ȳ����")->setFrameY(orangeMushroomVec[i]->getStartFrameY());
				if (orangeMushroomVec[i]->_monsterCount % 15 == 0)
				{
					orangeMushroomVec[i]->setStartFrameX(orangeMushroomVec[i]->getStartFrameX() + 1);
					if (orangeMushroomVec[i]->getStartFrameX() > 2)
					{
						orangeMushroomVec[i]->setStartFrameX(0);
					}
					IMAGEMANAGER->findImage("��Ȳ����")->setFrameX(orangeMushroomVec[i]->getStartFrameX());
				}
			}
			else if (orangeMushroomVec[i]->getIsHit())									//��Ȳ������ ���ݴ��Ҷ�
			{
				orangeMushroomVec[i]->setStartFrameX(2);
				orangeMushroomVec[i]->setStartFrameY(3);
				IMAGEMANAGER->findImage("��Ȳ����")->setFrameX(orangeMushroomVec[i]->getStartFrameX());
				IMAGEMANAGER->findImage("��Ȳ����")->setFrameY(orangeMushroomVec[i]->getStartFrameY());
			}
			else if (orangeMushroomVec[i]->getIsDie())									//��Ȳ������ ������
			{
				orangeMushroomVec[i]->setStartFrameY(5);
				IMAGEMANAGER->findImage("��Ȳ����")->setFrameY(orangeMushroomVec[i]->getStartFrameY());
				if (orangeMushroomVec[i]->_monsterCount %18 == 0)
				{
					orangeMushroomVec[i]->setStartFrameX(orangeMushroomVec[i]->getStartFrameX() + 1);
					if (orangeMushroomVec[i]->getStartFrameX() >=1)
					{
						orangeMushroomVec[i]->setStartFrameX(2);
						orangeMushroomVec.erase(orangeMushroomVec.begin() + i);
						_deadCount++;
						break;
					}
					IMAGEMANAGER->findImage("��Ȳ����")->setFrameX(orangeMushroomVec[i]->getStartFrameX());
				}
			}
			else if (orangeMushroomVec[i]->getIsJump())
			{
				orangeMushroomVec[i]->setStartFrameX(1);
				orangeMushroomVec[i]->setStartFrameY(4);
				IMAGEMANAGER->findImage("��Ȳ����")->setFrameX(orangeMushroomVec[i]->getStartFrameX());
				IMAGEMANAGER->findImage("��Ȳ����")->setFrameY(orangeMushroomVec[i]->getStartFrameY());
			}
			else																			//��Ȳ������ ������ ������
			{

				if (orangeMushroomVec[i]->_monsterCount % 31 == 0)
				{
					orangeMushroomVec[i]->setStartFrameX(1);
					orangeMushroomVec[i]->setStartFrameY(3);
					IMAGEMANAGER->findImage("��Ȳ����")->setFrameX(orangeMushroomVec[i]->getStartFrameX());
					IMAGEMANAGER->findImage("��Ȳ����")->setFrameY(orangeMushroomVec[i]->getStartFrameY());

				}
				else if (orangeMushroomVec[i]->_monsterCount % 37 == 0)
				{
					orangeMushroomVec[i]->setStartFrameX(0);
					orangeMushroomVec[i]->setStartFrameY(3);
					IMAGEMANAGER->findImage("��Ȳ����")->setFrameX(orangeMushroomVec[i]->getStartFrameX());
					IMAGEMANAGER->findImage("��Ȳ����")->setFrameY(orangeMushroomVec[i]->getStartFrameY());
				}
			}
		}
	}
	//�ӽ���
	if (_mushMom->isreal)
	{
		_mushMom->_monsterCount++;
		_mushMom->_skill.count++;
		if (_mushMom->getIsLeft())											//�ӽ����� ������ ����
		{
			if (_mushMom->getIsMove() || _mushMom->getIsChase())			//�ӽ����� �����̰ų� �i�ư���
			{
				IMAGEMANAGER->findImage("�ӽ���")->setFrameY(1);
				if (_mushMom->_monsterCount % 15 == 0)
				{
					_mushMom->setStartFrameX(_mushMom->getStartFrameX() + 1);
					if (_mushMom->getStartFrameX() > 5)
					{
						_mushMom->setStartFrameX(0);
					}
					IMAGEMANAGER->findImage("�ӽ���")->setFrameX(_mushMom->getStartFrameX());
				}
			}

			else if (_mushMom->getIsHit() && !_mushMom->getIsUsingSkill())		//�ӽ����� ���ݴ��Ҷ�
			{
				IMAGEMANAGER->findImage("�ӽ���")->setFrameX(1);
				IMAGEMANAGER->findImage("�ӽ���")->setFrameY(0);
			}
			else if (_mushMom->getIsDie())										//�ӽ����� ������
			{
				IMAGEMANAGER->findImage("�ӽ���")->setFrameY(3);
				if (_mushMom->_monsterCount % 13 == 0)
				{
					_mushMom->setStartFrameX(_mushMom->getStartFrameX() + 1);
					if (_mushMom->getStartFrameX() > 5)
					{
						_mushMom->setStartFrameX(5);
						_mushMom->isreal = false;
						_deadCount = 0;
					}
					IMAGEMANAGER->findImage("�ӽ���")->setFrameX(_mushMom->getStartFrameX());
				}
			}
			else if (_mushMom->getIsUsingSkill())											//��ų ��� �Ҷ�
			{
				IMAGEMANAGER->findImage("�ӽ���")->setFrameY(2);
				if (_mushMom->_monsterCount % 10 == 0 )
				{
					_mushMom->setStartFrameX(_mushMom->getStartFrameX() + 1);
					if (_mushMom->getStartFrameX() > 7)
					{
						_mushMom->test = 4;
						_mushMom->_monsterRect.top += 80;
						_mushMom->_monsterRect.bottom += 80;
					}
					else if (_mushMom->getStartFrameX() > 5)
					{
						_mushMom->test = 3;
						_mushMom->_monsterRect.top -= 80;
						_mushMom->_monsterRect.bottom -= 80;
					}
					
					if (_mushMom->getStartFrameX() > 8)
					{
						_mushMom->_skill.rc = RectMake(_mushMom->_monsterRect.left - 30, _mushMom->_monsterRect.top + 50, 256, 125);
					}
					if (_mushMom->getStartFrameX() > 9)
					{	
						_mushMom->setStartFrameX(9);	
					}
					IMAGEMANAGER->findImage("�ӽ�����ų")->setFrameY(0);
					if (_mushMom->_skill.count % 3 == 0)
					{
						_mushMom->_skill.frame++;
						if (_mushMom->_skill.frame > 2)
						{
							_mushMom->setIsChase(true);
							_mushMom->setIsUsingSkill(false);
							_mushMom->_skill.skillend = true;
							_mushMom->_skill.frame = 0;
							_mushMom->setStartFrameX(0);
							_mushMom->_skill.rc.left = 1920;
							_mushMom->_skill.rc.right = _mushMom->_skill.rc.left +256;
							_mushMom->_skill.rc.top = 1080;
							_mushMom->_skill.rc.bottom = _mushMom->_skill.rc.left +125;
						}
						IMAGEMANAGER->findImage("�ӽ�����ų")->setFrameX(_mushMom->_skill.frame);
					}
					IMAGEMANAGER->findImage("�ӽ���")->setFrameX(_mushMom->getStartFrameX());
				}
			}
			else															//�ӽ����� ������ ������
			{
				IMAGEMANAGER->findImage("�ӽ���")->setFrameX(0);
				IMAGEMANAGER->findImage("�ӽ���")->setFrameY(0);
			}
		}
		else																			//�ӽ����� �������� ����
		{
			if (_mushMom->getIsMove() || _mushMom->getIsChase())						//�ӽ����� �����̰ų� �i�ư���
			{
				IMAGEMANAGER->findImage("�ӽ���")->setFrameY(5);
				if (_mushMom->_monsterCount % 15 == 0)
				{
					_mushMom->setStartFrameX(_mushMom->getStartFrameX() + 1);
					if (_mushMom->getStartFrameX() >= 4)
					{
						_mushMom->setStartFrameX(0);
					}
					IMAGEMANAGER->findImage("�ӽ���")->setFrameX(_mushMom->getStartFrameX());
				}
			}
			else if (_mushMom->getIsHit() && !_mushMom->getIsUsingSkill())					//�ӽ����� ���ݴ��Ҷ�
			{
				IMAGEMANAGER->findImage("�ӽ���")->setFrameX(1);
				IMAGEMANAGER->findImage("�ӽ���")->setFrameY(4);
			}
			else if (_mushMom->getIsDie())													//�ӽ����� ������
			{
				IMAGEMANAGER->findImage("�ӽ���")->setFrameY(7);
				if (_mushMom->_monsterCount % 13 == 0)
				{
					_mushMom->setStartFrameX(_mushMom->getStartFrameX() + 1);
					if (_mushMom->getStartFrameX() > 5)
					{
						_mushMom->setStartFrameX(5);
						_mushMom->isreal = false;
						_deadCount = 0;
					}
					IMAGEMANAGER->findImage("�ӽ���")->setFrameX(_mushMom->getStartFrameX());
				}
			}
			else if (_mushMom->getIsUsingSkill())											//��ų ����Ҷ�
			{
				IMAGEMANAGER->findImage("�ӽ���")->setFrameY(6);
				if (_mushMom->_monsterCount % 10 == 0)
				{
					_mushMom->setStartFrameX(_mushMom->getStartFrameX() + 1);
					if (_mushMom->getStartFrameX() > 7)
					{
						_mushMom->test = 7;
						_mushMom->_monsterRect.top += 80;
						_mushMom->_monsterRect.bottom += 80;
					}
					else if (_mushMom->getStartFrameX() > 5)
					{
						_mushMom->test = 6;
						_mushMom->_monsterRect.top -= 80;
						_mushMom->_monsterRect.bottom -= 80;
					}
					
					if (_mushMom->getStartFrameX() > 8)
					{
						_mushMom->_skill.rc = RectMake(_mushMom->_monsterRect.left - 30, _mushMom->_monsterRect.top + 50, 256, 125);
					}
					if (_mushMom->getStartFrameX() > 9)
					{	
						_mushMom->setStartFrameX(9);
					}
					IMAGEMANAGER->findImage("�ӽ�����ų")->setFrameY(0);
					if (_mushMom->_skill.count % 3 == 0)
					{
						_mushMom->_skill.frame++;
						if (_mushMom->_skill.frame > 2)
						{
							_mushMom->_skill.frame = 0;
							_mushMom->setIsChase(true);
							_mushMom->setIsUsingSkill(false);
							_mushMom->_skill.skillend = true;
							_mushMom->setStartFrameX(0);
							_mushMom->_skill.rc.left = 1920;
							_mushMom->_skill.rc.right = _mushMom->_skill.rc.left + 256;
							_mushMom->_skill.rc.top = 1080;
							_mushMom->_skill.rc.bottom = _mushMom->_skill.rc.left + 125;
						}
						IMAGEMANAGER->findImage("�ӽ�����ų")->setFrameX(_mushMom->_skill.frame);
					}
					IMAGEMANAGER->findImage("�ӽ���")->setFrameX(_mushMom->getStartFrameX());
				}
			}
			else 																		//�ӽ����� ������ ������
			{
				IMAGEMANAGER->findImage("�ӽ���")->setFrameX(0);
				IMAGEMANAGER->findImage("�ӽ���")->setFrameY(4);
			}
		}
		
	}
}

void mushMomField::monsterIntersect(void)
{
	RECT rcTemp;
	for (int i = 0; i < orangeMushroomVec.size(); i++)												//��Ȳ���� ǥâ�浹
	{
		if (!orangeMushroomVec[i]->getIsDie())
		{
			if (IntersectRect(&rcTemp, &PLAYER->_javelin1._rc, &orangeMushroomVec[i]->_monsterRect))
			{
				orangeMushroomVec[i]->setIsHit(true);
				orangeMushroomVec[i]->setMonsterHp(orangeMushroomVec[i]->getMonsterHp() - 50);
				if (orangeMushroomVec[i]->getMonsterHp() <= 0)
				{
					orangeMushroomVec[i]->setIsDie(true);
				}
				PLAYER->_javelin1._time = 0;
				PLAYER->_javelin1._usingJavelin = false;
				PLAYER->_isAttack = false;		  //���� ��Ȱ��ȭ
				PLAYER->_javelin1._rc.left = 1920;
				PLAYER->_javelin1._rc.right = PLAYER->_javelin1._rc.left + 30;
				PLAYER->_javelin1._rc.top = 1080;
				PLAYER->_javelin1._rc.bottom = PLAYER->_javelin1._rc.top + 30;
			}
			if (IntersectRect(&rcTemp, &PLAYER->_javelin2._rc, &orangeMushroomVec[i]->_monsterRect))
			{
				orangeMushroomVec[i]->setIsHit(true);
				orangeMushroomVec[i]->setMonsterHp(orangeMushroomVec[i]->getMonsterHp() - 50);
				if (orangeMushroomVec[i]->getMonsterHp() <= 0)
				{
					orangeMushroomVec[i]->setIsDie(true);
				}
				LUCKSEVEN->setIsUsing(false);
				PLAYER->_isUsingSkill = false;
				PLAYER->_javelin2._time = 0;
				PLAYER->_javelin2._usingJavelin = false;
				PLAYER->_isAttack = false;		  //���� ��Ȱ��ȭ
				PLAYER->_javelin2._rc.left = 1920;
				PLAYER->_javelin2._rc.right = PLAYER->_javelin2._rc.left + 30;
				PLAYER->_javelin2._rc.top = 1080;
				PLAYER->_javelin2._rc.bottom = PLAYER->_javelin2._rc.top + 30;
			}
			if (IntersectRect(&rcTemp, &SHURIKENBURST->_javelin.rc, &orangeMushroomVec[i]->_monsterRect))				//��Ȳ����, �����˹���Ʈ ǥâ �浹ó��
			{
				orangeMushroomVec[i]->setMonsterHp(orangeMushroomVec[i]->getMonsterHp() - SHURIKENBURST->getDamage());
				orangeMushroomVec[i]->setIsHit(true);
				if (orangeMushroomVec[i]->getMonsterHp() <= 0)
				{
					orangeMushroomVec[i]->setIsDie(true);
				}
			}
			if (IntersectRect(&rcTemp, &WINDTALISMAN->_javelin.rc, &orangeMushroomVec[i]->_monsterRect))				//��Ȳ����, ���� Ż������ ǥâ �浹ó��
			{
				orangeMushroomVec[i]->setMonsterHp(orangeMushroomVec[i]->getMonsterHp() - SHURIKENBURST->getDamage());
				orangeMushroomVec[i]->setIsHit(true);
				if (orangeMushroomVec[i]->getMonsterHp() <= 0)
				{
					orangeMushroomVec[i]->setIsDie(true);
				}
			}
			if (IntersectRect(&rcTemp, &SHADESPLIT->_skillRange, &orangeMushroomVec[i]->_monsterRect))					//��Ȳ����, ���̵彺�ø� ǥâ �浹ó��
			{
				orangeMushroomVec[i]->setMonsterHp(orangeMushroomVec[i]->getMonsterHp() - SHURIKENBURST->getDamage());
				orangeMushroomVec[i]->setIsHit(true);
				if (orangeMushroomVec[i]->getMonsterHp() <= 0)
				{
					orangeMushroomVec[i]->setIsDie(true);
				}
			}
		}
	}
	for (int i = 0; i < blueMushroomVec.size(); i++)												//�Ķ����� ǥâ�浹
	{
		if (!blueMushroomVec[i]->getIsDie())
		{
			if (IntersectRect(&rcTemp, &PLAYER->_javelin1._rc, &blueMushroomVec[i]->_monsterRect))
			{
				blueMushroomVec[i]->setIsHit(true);
				blueMushroomVec[i]->setMonsterHp(blueMushroomVec[i]->getMonsterHp() - 50);
				if (blueMushroomVec[i]->getMonsterHp() <= 0)
				{
					blueMushroomVec[i]->setIsDie(true);
				}
				PLAYER->_javelin1._time = 0;
				PLAYER->_javelin1._usingJavelin = false;
				PLAYER->_isAttack = false;		  //���� ��Ȱ��ȭ
				PLAYER->_javelin1._rc.left = 1920;
				PLAYER->_javelin1._rc.right = PLAYER->_javelin1._rc.left + 30;
				PLAYER->_javelin1._rc.top = 1080;
				PLAYER->_javelin1._rc.bottom = PLAYER->_javelin1._rc.top + 30;
			}
			if (IntersectRect(&rcTemp, &PLAYER->_javelin2._rc, &blueMushroomVec[i]->_monsterRect))
			{
				blueMushroomVec[i]->setIsHit(true);
				blueMushroomVec[i]->setMonsterHp(blueMushroomVec[i]->getMonsterHp() - 50);
				if (blueMushroomVec[i]->getMonsterHp() <= 0)
				{
					blueMushroomVec[i]->setIsDie(true);
				}
				LUCKSEVEN->setIsUsing(false);
				PLAYER->_isUsingSkill = false;
				PLAYER->_javelin2._time = 0;
				PLAYER->_javelin2._usingJavelin = false;
				PLAYER->_isAttack = false;		  //���� ��Ȱ��ȭ
				PLAYER->_javelin2._rc.left = 1920;
				PLAYER->_javelin2._rc.right = PLAYER->_javelin2._rc.left + 30;
				PLAYER->_javelin2._rc.top = 1080;
				PLAYER->_javelin2._rc.bottom = PLAYER->_javelin2._rc.top + 30;
			}
			if (IntersectRect(&rcTemp, &SHURIKENBURST->_javelin.rc, &blueMushroomVec[i]->_monsterRect))					//�Ķ�����, �����˹���Ʈ ǥâ �浹ó��
			{
				blueMushroomVec[i]->setMonsterHp(blueMushroomVec[i]->getMonsterHp() - SHURIKENBURST->getDamage());
				blueMushroomVec[i]->setIsHit(true);
				if (blueMushroomVec[i]->getMonsterHp() <= 0)
				{
					blueMushroomVec[i]->setIsDie(true);
				}
			}
			if (IntersectRect(&rcTemp, &WINDTALISMAN->_javelin.rc, &blueMushroomVec[i]->_monsterRect))					//�Ķ�����, ���� Ż������ ǥâ �浹ó��
			{
				blueMushroomVec[i]->setMonsterHp(blueMushroomVec[i]->getMonsterHp() - WINDTALISMAN->getDamage());
				blueMushroomVec[i]->setIsHit(true);
				if (blueMushroomVec[i]->getMonsterHp() <= 0)
				{
					blueMushroomVec[i]->setIsDie(true);
				}
			}
			if (IntersectRect(&rcTemp, &SHADESPLIT->_skillRange, &blueMushroomVec[i]->_monsterRect))					//�Ķ�����, ���̵彺�ø� �浹ó��
			{
				blueMushroomVec[i]->setMonsterHp(blueMushroomVec[i]->getMonsterHp() - SHADESPLIT->getDamage());
				blueMushroomVec[i]->setIsHit(true);
				if (blueMushroomVec[i]->getMonsterHp() <= 0)
				{
					blueMushroomVec[i]->setIsDie(true);
				}
			}
		}
	}
	if (_mushMom->isreal)																	//�ӽ��� �ǰ�
	{
		if (!_mushMom->getIsDie())
		{
			if (IntersectRect(&rcTemp, &PLAYER->_javelin1._rc, &_mushMom->_monsterRect))
			{
				_mushMom->setIsHit(true);
				bossHp.right--;
				if (bossHp.right - bossHp.left <= 0)
				{
					_mushMom->setIsDie(true);
				}
				PLAYER->_javelin1._time = 0;
				PLAYER->_javelin1._usingJavelin = false;
				PLAYER->_isAttack = false;		  //���� ��Ȱ��ȭ
				PLAYER->_javelin1._rc.left = 1920;
				PLAYER->_javelin1._rc.right = PLAYER->_javelin1._rc.left + 30;
				PLAYER->_javelin1._rc.top = 1080;
				PLAYER->_javelin1._rc.bottom = PLAYER->_javelin1._rc.top + 30;
			}
			if (IntersectRect(&rcTemp, &PLAYER->_javelin2._rc, &_mushMom->_monsterRect))
			{
				_mushMom->setIsHit(true);
				bossHp.right--;
				if (bossHp.right - bossHp.left <= 0)
				{
					_mushMom->setIsDie(true);
				}
				LUCKSEVEN->setIsUsing(false);
				PLAYER->_isUsingSkill = false;
				PLAYER->_javelin2._time = 0;
				PLAYER->_javelin2._usingJavelin = false;
				PLAYER->_isAttack = false;		  //���� ��Ȱ��ȭ
				PLAYER->_javelin2._rc.left = 1920;
				PLAYER->_javelin2._rc.right = PLAYER->_javelin2._rc.left + 30;
				PLAYER->_javelin2._rc.top = 1080;
				PLAYER->_javelin2._rc.bottom = PLAYER->_javelin2._rc.top + 30;
			}
			if (IntersectRect(&rcTemp, &SHURIKENBURST->_javelin.rc, &_mushMom->_monsterRect))
			{
				_mushMom->setIsHit(true);
				bossHp.right--;
				if (bossHp.right - bossHp.left <= 0)
				{
					_mushMom->setIsDie(true);
				}
			}
			if (IntersectRect(&rcTemp, &WINDTALISMAN->_javelin.rc, &_mushMom->_monsterRect))
			{
				_mushMom->setIsHit(true);
				bossHp.right-=2;
				if (bossHp.right - bossHp.left <= 0)
				{
					_mushMom->setIsDie(true);
				}
			}
			if (IntersectRect(&rcTemp, &SHADESPLIT->_skillRange, &_mushMom->_monsterRect))
			{
				_mushMom->setMonsterHp(_mushMom->getMonsterHp() - SHADESPLIT->getDamage());
				_mushMom->setIsHit(true);
				bossHp.right -= 4;
				if (bossHp.right - bossHp.left <= 0)
				{
					_mushMom->setIsDie(true);
				}
			}
		}
	}
	
	for (int i = 0; i < blueMushroomVec.size(); i++)											//�Ķ������� �÷��̾� �浹ó��
	{
		if (IntersectRect(&rcTemp, &PLAYER->_playerRect.rc, &blueMushroomVec[i]->_monsterRect))
		{
			if ((PLAYER->_playerRect.rc.left < blueMushroomVec[i]->_monsterRect.right - 25 || PLAYER->_playerRect.rc.right < blueMushroomVec[i]->_monsterRect.left + 25)
				&& PLAYER->_playerRect.rc.bottom > blueMushroomVec[i]->_monsterRect.top + 25)
			{
				if (!PLAYER->_isHurt)
				{
					PLAYER->_playerRect.hp.left -= 5;
					PLAYER->_playerRect.hp.right -= 5;
					PLAYER->_isHit = true;
				}
			}
		}
		if (PLAYER->_isHit)
		{
			PLAYER->_playerRect.time += 0.03;
			if (PLAYER->_playerRect.rc.left > blueMushroomVec[i]->_monsterRect.left)
			{
				PLAYER->_playerRect.rc.left += 1;
				PLAYER->_playerRect.rc.right += 1;

				PLAYER->_isHurt = true;
			}
			else if (PLAYER->_playerRect.rc.right < blueMushroomVec[i]->_monsterRect.right)
			{
				PLAYER->_playerRect.rc.left -= 1;
				PLAYER->_playerRect.rc.right -= 1;
				PLAYER->_isHurt = true;
			}
			if (!PLAYER->_isJump)
			{
				PLAYER->_playerRect.rc.top = -(sinf(PI / 2) * 1.5 - PLAYER->_playerRect.time) + PLAYER->_playerRect.rc.top;
				PLAYER->_playerRect.rc.bottom = -(sinf(PI / 2) * 1.5 - PLAYER->_playerRect.time) + PLAYER->_playerRect.rc.bottom;
			}
		}
	}

	for (int i = 0; i < orangeMushroomVec.size(); i++)											//��Ȳ������ �÷��̾� �浹ó��
	{
		if (IntersectRect(&rcTemp, &PLAYER->_playerRect.rc, &orangeMushroomVec[i]->_monsterRect))
		{
			if ((PLAYER->_playerRect.rc.left < orangeMushroomVec[i]->_monsterRect.right - 25 || PLAYER->_playerRect.rc.right < orangeMushroomVec[i]->_monsterRect.left + 25)
				&& PLAYER->_playerRect.rc.bottom > orangeMushroomVec[i]->_monsterRect.top + 25)
			{
				if (!PLAYER->_isHurt)
				{
					PLAYER->_playerRect.hp.left -= 3;
					PLAYER->_playerRect.hp.right -= 3;
					PLAYER->_isHit = true;
				}
			}
		}
		if (PLAYER->_isHit)
		{
			PLAYER->_playerRect.time += 0.03;
			if (PLAYER->_playerRect.rc.left > orangeMushroomVec[i]->_monsterRect.left)
			{
				PLAYER->_playerRect.rc.left += 1;
				PLAYER->_playerRect.rc.right += 1;
				PLAYER->_isHurt = true;
			}
			else if (PLAYER->_playerRect.rc.right < orangeMushroomVec[i]->_monsterRect.right)
			{
				PLAYER->_playerRect.rc.left -= 1;
				PLAYER->_playerRect.rc.right -= 1;
				PLAYER->_isHurt = true;
			}
			if (!PLAYER->_isJump)
			{
				PLAYER->_playerRect.rc.top = -(sinf(PI / 2) * 1.5 - PLAYER->_playerRect.time) + PLAYER->_playerRect.rc.top;
				PLAYER->_playerRect.rc.bottom = -(sinf(PI / 2) * 1.5 - PLAYER->_playerRect.time) + PLAYER->_playerRect.rc.bottom;
			}
		}
	}
	if (_mushMom->isreal)
	{
		if (IntersectRect(&rcTemp, &PLAYER->_playerRect.rc, &_mushMom->_monsterRect))									//�ӽ��� �浹ó��
		{
			if (PLAYER->_playerRect.rc.left < _mushMom->_monsterRect.right - 50 || PLAYER->_playerRect.rc.right < _mushMom->_monsterRect.left + 50)
			{
				if (!PLAYER->_isHurt)
				{
					PLAYER->_playerRect.hp.left -= 20;
					PLAYER->_playerRect.hp.right -= 20;
					PLAYER->_isHit = true;
				}
			}
		}
		if (IntersectRect(&rcTemp, &PLAYER->_playerRect.rc, &_mushMom->_skill.rc))
		{
			if (!PLAYER->_isHurt)
			{
				PLAYER->_playerRect.hp.left -= 40;
				PLAYER->_playerRect.hp.right -= 40;
				PLAYER->_isHit = true;
			}
		}
		if (PLAYER->_isHit)
		{
			PLAYER->_playerRect.time += 0.03;
			if (PLAYER->_playerRect.rc.left > _mushMom->_monsterRect.left)
			{
				PLAYER->_playerRect.rc.left += 2;
				PLAYER->_playerRect.rc.right += 2;

				PLAYER->_isHurt = true;
			}
			else if (PLAYER->_playerRect.rc.right < _mushMom->_monsterRect.right)
			{
				PLAYER->_playerRect.rc.left -= 2;
				PLAYER->_playerRect.rc.right -= 2;
				PLAYER->_isHurt = true;
			}
			if (!PLAYER->_isJump)
			{
				PLAYER->_playerRect.rc.top = -(sinf(PI / 2) * 2 - PLAYER->_playerRect.time) + PLAYER->_playerRect.rc.top;
				PLAYER->_playerRect.rc.bottom = -(sinf(PI / 2) * 2 - PLAYER->_playerRect.time) + PLAYER->_playerRect.rc.bottom;
			}
		}
	}
	
	if (PLAYER->_isHit)
	{
		if (PLAYER->_isJump)
		{
			PLAYER->_playerRect.rc.top -= 3;
			PLAYER->_playerRect.rc.bottom -= 3;
			PLAYER->_playerRect.time = 0;
			PLAYER->_isJump = false;
			PLAYER->_jumpCount = 0;
		}
	}
	if (PLAYER->_isHurt)
	{
		PLAYER->_safeTime--;
		if (PLAYER->_safeTime < 0)
		{
			PLAYER->_isHurt = false;
			PLAYER->_safeTime = 100;
		}
	}
}