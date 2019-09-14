#include "stdafx.h"
#include "huntingGround.h"



HRESULT huntingGround::init()
{
	setIsInPlayer(true);
	setIsLeft(false);
	setIsRight(false);
	IMAGEMANAGER->addImage("헤네시스사냥터", "Map/헤네시스.bmp", 1920, 1080);											//배경
	IMAGEMANAGER->addFrameImage("portal", "Map/portal.bmp", 1286, 133, 14, 1, true, RGB(255, 0, 255));					//포탈
	IMAGEMANAGER->addFrameImage("portal", "Map/portal.bmp", 1286, 133, 14, 1, true, RGB(255, 0, 255));					//포탈
	IMAGEMANAGER->addFrameImage("스텀프", "Monster/stump.bmp", 215, 395, 3, 6, true, RGB(255, 0, 255));					//스텀프
	IMAGEMANAGER->addFrameImage("스텀프1", "Monster/stump.bmp", 215, 395, 3, 6, true, RGB(255, 0, 255));				//스텀프
	IMAGEMANAGER->addFrameImage("엑스스텀프", "Monster/AxeStump.bmp", 315, 576, 4, 6, true, RGB(255, 0, 255));			//엑스스텀프
	_portal[0].rc = RectMake(1760, 790, 92, 133);																		//포탈 사각형(시작지점 가는길)
	_portal[1].rc = RectMake(80, 790, 92, 133);																			//포탈 사각형(머쉬맘필드 가는길)
	_field[0].rc = RectMake(0, 910, 1920, 50);
	_field[1].rc = RectMake(420, 550, 1500, 30);
	_field[2].rc = RectMake(560, 190, 885, 30);
	_field[3].rc = RectMake(1530, 190, 390, 30);
	_field[4].rc = RectMake(400, 815, 90, 30);
	_field[5].rc = RectMake(150, 650, 140, 30);
	_field[6].rc = RectMake(150, 730, 140, 30);
	_field[7].rc = RectMake(520, 460, 90, 30);
	_field[8].rc = RectMake(280, 380, 140, 30);
	_field[9].rc = RectMake(280, 280, 140, 30);
	_field[10].rc = RectMake(928, 530, 10, 230);
	_field[11].rc = RectMake(1483, 180, 10, 220);
	for (int i = 0; i < 2;i++)
	{
		_portal[i].portalFrame = 0;
	}
	
	_bgSpeedX = _bgSpeedY = 0;
	_count = 0;
	test = 0;
	return S_OK;
}



void huntingGround::update(void)
{
	PLAYER->_playerRect.rc.top += GRAVITY;			//밑으로 중력 작용
	PLAYER->_playerRect.rc.bottom += GRAVITY;
	RECT rcTemp1;
	
	portalFrame();
	intersectFeild();
	monsterSpawn();
	monsterIntersect();
	monsterFrame();
	
	if (_bgSpeedX > 964 && _bgSpeedY > 400 || _bgSpeedY >400 && _bgSpeedX > 0)	//처음 입장했을때 화면이 플레이어가 있는곳으로 이동한후 화면을 비춘다
	{
		PLAYER->_isPlayerMoveMap = true;
	}
	if (PLAYER->_playerRect.rc.right > WINSIZEX / 2 + 150 && _bgSpeedX <967) //오른쪽으로 이동하면 화면이 따라온다
	{
		if (PLAYER->_isPlayerMoveMap)
		{
			_bgSpeedX += 3;
			PLAYER->_playerRect.rc.left -= 3;
			PLAYER->_playerRect.rc.right -= 3;
			for (int i = 0; i < 12;i++)					//바닥 이동
			{
				_field[i].rc.left -= 3;
				_field[i].rc.right -= 3;
			}
			for (int i = 0; i < 2; i++)					//포탈도 이동
			{
				_portal[i].rc.left -= 3;
				_portal[i].rc.right -= 3;
			}

			for (int i = 0; i < stumpVec.size(); i++)
			{
				stumpVec[i]->_monsterRect.left -= 3;
				stumpVec[i]->_monsterRect.right -= 3;
			}
			for (int i = 0; i < axeStumpVec.size();i++)
			{
				axeStumpVec[i]->_monsterRect.left -= 3;
				axeStumpVec[i]->_monsterRect.right -= 3;
			}
			if (PLAYER->_jumpCount > 2 && !PLAYER->_isLeft)
			{
				_bgSpeedX += 7;
				PLAYER->_playerRect.rc.left -= 7;
				PLAYER->_playerRect.rc.right -= 7;
				for (int i = 0; i < 12;i++)					//바닥 이동
				{
					_field[i].rc.left -= 7;
					_field[i].rc.right -= 7;
				}
				for (int i = 0; i < 2; i++)					//포탈도 이동
				{
					_portal[i].rc.left -= 7;
					_portal[i].rc.right -= 7;
				}

				for (int i = 0; i < stumpVec.size(); i++)
				{
					stumpVec[i]->_monsterRect.left -= 7;
					stumpVec[i]->_monsterRect.right -= 7;
				}
				for (int i = 0; i < axeStumpVec.size();i++)
				{
					axeStumpVec[i]->_monsterRect.left -= 7;
					axeStumpVec[i]->_monsterRect.right -= 7;
				}
			}
		}
		
		// 처음 맵에 입장했을때
		else
		{
			_bgSpeedX += 9;
			PLAYER->_playerRect.rc.left -= 9;
			PLAYER->_playerRect.rc.right -= 9;
			for (int i = 0; i < 12;i++)
			{
				_field[i].rc.left -= 9;
				_field[i].rc.right -= 9;
			}
			for (int i = 0; i < 2; i++)					//포탈도 이동
			{
				_portal[i].rc.left -= 9;
				_portal[i].rc.right -= 9;
			}
			for (int i = 0; i < stumpVec.size(); i++)
			{
				stumpVec[i]->_monsterRect.left -= 9;
				stumpVec[i]->_monsterRect.right -= 9;
			}
			for (int i = 0; i < axeStumpVec.size();i++)
			{
				axeStumpVec[i]->_monsterRect.left -= 9;
				axeStumpVec[i]->_monsterRect.right -= 9;
			}
		}
	}
	else if (PLAYER->_playerRect.rc.left < WINSIZEX / 2 - 150 && _bgSpeedX >0)//왼쪽으로 이동하면 화면이 따라온다
	{
		
		if (PLAYER->_isPlayerMoveMap)
		{
			_bgSpeedX -= 3;
			PLAYER->_playerRect.rc.left += 3;
			PLAYER->_playerRect.rc.right += 3;
			for (int i = 0; i < 12;i++)
			{
				_field[i].rc.left += 3;
				_field[i].rc.right += 3;
			}
			for (int i = 0; i < 2; i++)
			{
				_portal[i].rc.left += 3;
				_portal[i].rc.right += 3;
			}
			for (int i = 0; i < stumpVec.size(); i++)
			{
				stumpVec[i]->_monsterRect.left += 3;
				stumpVec[i]->_monsterRect.right += 3;
			}
			for (int i = 0; i < axeStumpVec.size();i++)
			{
				axeStumpVec[i]->_monsterRect.left += 3;
				axeStumpVec[i]->_monsterRect.right += 3;
			}
			if (PLAYER->_jumpCount > 2 && PLAYER->_isLeft)
			{
				_bgSpeedX -= 7;
				PLAYER->_playerRect.rc.left += 7;
				PLAYER->_playerRect.rc.right += 7;
				for (int i = 0; i < 12;i++)					//바닥 이동
				{
					_field[i].rc.left += 7;
					_field[i].rc.right += 7;
				}
				for (int i = 0; i < 2; i++)					//포탈도 이동
				{
					_portal[i].rc.left += 7;
					_portal[i].rc.right += 7;
				}

				for (int i = 0; i < stumpVec.size(); i++)
				{
					stumpVec[i]->_monsterRect.left += 7;
					stumpVec[i]->_monsterRect.right += 7;
				}
				for (int i = 0; i < axeStumpVec.size();i++)
				{
					axeStumpVec[i]->_monsterRect.left += 7;
					axeStumpVec[i]->_monsterRect.right += 7;
				}
			}
		}
		// 처음 맵에 입장했을때
		else
		{
			_bgSpeedX -= 9;
			PLAYER->_playerRect.rc.left += 9;
			PLAYER->_playerRect.rc.right += 9;
			for (int i = 0; i < 12;i++)
			{
				_field[i].rc.left += 9;
				_field[i].rc.right += 9;
			}
			for (int i = 0; i < 2; i++)
			{
				_portal[i].rc.left += 9;
				_portal[i].rc.right += 9;
			}
			for (int i = 0; i < stumpVec.size(); i++)
			{
				stumpVec[i]->_monsterRect.left += 9;
				stumpVec[i]->_monsterRect.right += 9;
			}
			for (int i = 0; i < axeStumpVec.size();i++)
			{
				axeStumpVec[i]->_monsterRect.left += 9;
				axeStumpVec[i]->_monsterRect.right += 9;
			}
		}
	}
	else if (PLAYER->_playerRect.rc.bottom > WINSIZEY / 2 + 150 && _bgSpeedY < 445)//아래쪽으로 이동하면 화면이 따라온다
	{
		
		_bgSpeedY += 9;
		PLAYER->_playerRect.rc.top -= 6;
		PLAYER->_playerRect.rc.bottom -= 6;
		for (int i = 0; i < 12;i++)
		{
			_field[i].rc.top -= 9;
			_field[i].rc.bottom -= 9;
		}
		for (int i = 0; i < 2; i++)
		{
			_portal[i].rc.top -= 9;
			_portal[i].rc.bottom -= 9;
		}
		for (int i = 0; i < stumpVec.size(); i++)
		{
			stumpVec[i]->_monsterRect.top -= 9;
			stumpVec[i]->_monsterRect.bottom -= 9;
		}
		for (int i = 0; i < axeStumpVec.size();i++)
		{
			axeStumpVec[i]->_monsterRect.top -= 9;
			axeStumpVec[i]->_monsterRect.bottom -= 9;
		}
		
	}
	else if (PLAYER->_playerRect.rc.top < WINSIZEY / 2 - 150 && _bgSpeedY >0)//위쪽으로 이동하면 화면이 따라온다
	{
		if (PLAYER->_isPlayerMoveMap)
		{
			_bgSpeedY -= 3;
			PLAYER->_playerRect.rc.top += 3;
			PLAYER->_playerRect.rc.bottom += 3;
			for (int i = 0; i < 12;i++)
			{
				_field[i].rc.top += 3;
				_field[i].rc.bottom += 3;
			}
			for (int i = 0; i < 2; i++)
			{
				_portal[i].rc.top += 3;
				_portal[i].rc.bottom += 3;
			}
			for (int i = 0; i < stumpVec.size(); i++)
			{
				stumpVec[i]->_monsterRect.top += 3;
				stumpVec[i]->_monsterRect.bottom += 3;
			}
			for (int i = 0; i < axeStumpVec.size();i++)
			{
				axeStumpVec[i]->_monsterRect.top += 3;
				axeStumpVec[i]->_monsterRect.bottom += 3;
			}
		}
		// 처음 맵에 입장했을때
		else
		{
			_bgSpeedY -= 9;
			PLAYER->_playerRect.rc.top -= 9;
			PLAYER->_playerRect.rc.bottom -= 9;
			for (int i = 0; i < 12;i++)
			{
				_field[i].rc.top += 9;
				_field[i].rc.bottom += 9;
			}
			for (int i = 0; i < 2; i++)
			{
				_portal[i].rc.top += 9;
				_portal[i].rc.bottom += 9;
			}
			for (int i = 0; i < stumpVec.size(); i++)
			{
				stumpVec[i]->_monsterRect.top += 9;
				stumpVec[i]->_monsterRect.bottom += 9;
			}
			for (int i = 0; i < axeStumpVec.size();i++)
			{
				axeStumpVec[i]->_monsterRect.top += 9;
				axeStumpVec[i]->_monsterRect.bottom += 9;
			}
		}
	}
	RECT rcTemp;
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (IntersectRect(&rcTemp, &PLAYER->_playerRect.rc, &_portal[0].rc))
		{
			setIsRight(true);
		}
		if (IntersectRect(&rcTemp, &PLAYER->_playerRect.rc, &_portal[1].rc))
		{
			setIsLeft(true);
		}
	}
	if (PLAYER->_moveCount == 1)//시작점에서 왔으면 포탑위에서 나타남
	{
		PLAYER->_playerRect.rc.left = _portal[0].rc.left;
		PLAYER->_playerRect.rc.right = PLAYER->_playerRect.rc.left + 79;
		PLAYER->_playerRect.rc.bottom = _portal[0].rc.top;
		PLAYER->_playerRect.rc.top = PLAYER->_playerRect.rc.bottom - 85;
		PLAYER->_moveCount = 0;
	}
	else if (PLAYER->_moveCount == -1)//머쉬맘필드에서 왔으면 포탑위에서 나타남
	{
		PLAYER->_playerRect.rc.left = _portal[1].rc.left;
		PLAYER->_playerRect.rc.right = PLAYER->_playerRect.rc.left + 79;
		PLAYER->_playerRect.rc.bottom = _portal[1].rc.top;
		PLAYER->_playerRect.rc.top = PLAYER->_playerRect.rc.bottom - 85;
		PLAYER->_moveCount = 0;
	}
}

void huntingGround::release(void)
{
}

void huntingGround::render(HDC hdc)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	char str[128];
	IMAGEMANAGER->loopRender("헤네시스사냥터", getMemDC(), &RectMake(0, 0, 1920, 1080), _bgSpeedX, _bgSpeedY);
	for (int i = 0; i < 2; i++)
	{
		IMAGEMANAGER->frameRender("portal", getMemDC(), _portal[i].rc.left, _portal[i].rc.top);
	}
	
	for (int i = 0; i < stumpVec.size();i++)
	{
		IMAGEMANAGER->frameRender("스텀프", getMemDC(), stumpVec[i]->_monsterRect.left, stumpVec[i]->_monsterRect.top,stumpVec[i]->getStartFrameX(),stumpVec[i]->getStartFrameY());
		
	}
	for (int i = 0; i < axeStumpVec.size();i++)
	{
		IMAGEMANAGER->frameRender("엑스스텀프", getMemDC(), axeStumpVec[i]->_monsterRect.left, axeStumpVec[i]->_monsterRect.top,axeStumpVec[i]->getStartFrameX(),axeStumpVec[i]->getStartFrameY());
	}
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		for (int i = 0;i < 12;i++)
		{
			Rectangle(getMemDC(), _field[i].rc.left, _field[i].rc.top, _field[i].rc.right, _field[i].rc.bottom);
		}
	}
	this->getBackBuffer()->render(getHDC());
}

void huntingGround::portalFrame(void)						// 포탈 프레임 설정
{
	_count++;
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

void huntingGround::intersectFeild(void)						//바닥과 충돌관련
{
	RECT rcTemp;
	
	if (IntersectRect(&rcTemp, &PLAYER->_playerRect.rc, &_field[0].rc))
	{
		PLAYER->_playerRect.rc.bottom = _field[0].rc.top;
		PLAYER->_playerRect.rc.top = PLAYER->_playerRect.rc.bottom - 85;
		PLAYER->_playerRect.time = 0;
		PLAYER->_isJump = false;
		PLAYER->_isHit = false;
		PLAYER->_jumpCount = 0;
		PLAYER->_isRopeUsing = false;
	}
	
	for (int i = 1; i < 4; i++)
	{
		if (IntersectRect(&rcTemp, &PLAYER->_playerRect.rc, &_field[i].rc) && !PLAYER->_isRopeUsing && PLAYER->_jumpCount>=0)
		{
			PLAYER->_playerRect.rc.bottom = _field[i].rc.top;
			PLAYER->_playerRect.rc.top = PLAYER->_playerRect.rc.bottom - 85;
			PLAYER->_playerRect.time = 0;
			PLAYER->_isJump = false;
			PLAYER->_isHit = false;
			PLAYER->_jumpCount = 0;
		}
		
	}
	for (int i = 4; i < 10; i++)
	{
		if (IntersectRect(&rcTemp, &PLAYER->_playerRect.rc, &_field[i].rc))
		{
 			if (PLAYER->_playerRect.rc.bottom < _field[i].rc.top + 10 && PLAYER->_playerRect.rc.top < _field[i].rc.top && PLAYER->_jumpCount >= 0)
			{
				
				PLAYER->_playerRect.rc.bottom = _field[i].rc.top;
				PLAYER->_playerRect.rc.top = PLAYER->_playerRect.rc.bottom - 85;
				PLAYER->_playerRect.time = 0;
				PLAYER->_isJump = false;
				PLAYER->_isHit = false;
				PLAYER->_jumpCount = 0;
				PLAYER->_isRopeUsing = false;
			}
			
		}
	}
	for (int i = 10; i < 12; i++)
	{
		if (IntersectRect(&rcTemp, &PLAYER->_playerRect.rc, &_field[i].rc))
		{
			if (PLAYER->_playerRect.rc.left + (PLAYER->_playerRect.rc.right - PLAYER->_playerRect.rc.left) / 2 -10 < _field[i].rc.left &&
				PLAYER->_playerRect.rc.left + (PLAYER->_playerRect.rc.right - PLAYER->_playerRect.rc.left) / 2 +10 > _field[i].rc.right &&
				(PLAYER->_isClimbing ||PLAYER->_isDownClimbing))
			{
				PLAYER->_isRopeUsing = true;
				PLAYER->_playerRect.time = 0;
				PLAYER->_jumpCount = 0;
				PLAYER->_isJump = false;
			}
		}
	}
	if (PLAYER->_isRopeUsing && PLAYER->_isClimbing)
	{
		PLAYER->_playerRect.rc.top -= 12;
		PLAYER->_playerRect.rc.bottom -= 12;
	}
	else if (PLAYER->_isRopeUsing && !PLAYER->_isClimbing && !PLAYER->_isDownClimbing)
	{
		PLAYER->_playerRect.rc.top -= 9;
		PLAYER->_playerRect.rc.bottom -= 9;
	}
	else if (PLAYER->_isRopeUsing && PLAYER->_isDownClimbing)
	{
		PLAYER->_playerRect.rc.top -= 6;
		PLAYER->_playerRect.rc.bottom -= 6;
	}
	

	if (PLAYER->_playerRect.rc.left<_field[10].rc.left - 35 ||
		(PLAYER->_playerRect.rc.right>_field[10].rc.right + 35 && PLAYER->_playerRect.rc.right<_field[2].rc.right) ||
		PLAYER->_playerRect.rc.top > _field[11].rc.bottom && PLAYER->_playerRect.rc.bottom < _field[1].rc.top)
	{
		PLAYER->_isRopeUsing = false;
	}
	if ((PLAYER->_playerRect.rc.left <_field[2].rc.right && PLAYER->_playerRect.rc.left > _field[10].rc.right + 35) ||
		PLAYER->_playerRect.rc.right > _field[3].rc.left || PLAYER->_playerRect.rc.bottom < _field[2].rc.top)
	{
		PLAYER->_isRopeUsing = false;
	}
	for (int i = 0; i < stumpVec.size();i++)
	{
		if (stumpVec[i]->_monsterRect.top > _field[0].rc.top)
		{
			stumpVec[i]->_monsterRect.top = _field[0].rc.top-66;
			stumpVec[i]->_monsterRect.bottom = stumpVec[i]->_monsterRect.top + 66;
		}
	}
	for (int i = 0; i < axeStumpVec.size();i++)
	{
		if (axeStumpVec[i]->_monsterRect.bottom > _field[1].rc.top)
		{
			axeStumpVec[i]->_monsterRect.bottom = _field[1].rc.top;
			axeStumpVec[i]->_monsterRect.top = axeStumpVec[i]->_monsterRect.bottom - 96;
			
		}
	}
}

void huntingGround::monsterSpawn(void)						//몬스터 소환
{

	if (stumpVec.size() < 8)								//스텀프 소환
	{
		_stump = new stump;
		stumpVec.push_back(_stump);
	}
	if (axeStumpVec.size() < 3)
	{
		_axeStump = new AxeStump;
		_axeStump->_monsterRect.bottom = _field[1].rc.top;
		_axeStump->_monsterRect.top = _axeStump->_monsterRect.bottom -96;
		axeStumpVec.push_back(_axeStump);
	}
	for (int i = 0; i < stumpVec.size();i++)
	{
		if (stumpVec[i]->_monsterRect.left > _field[0].rc.left && stumpVec[i]->_monsterRect.right < _field[0].rc.right)
		{
			stumpVec[i]->monsterMove();
		}
		else if (stumpVec[i]->_monsterRect.left <= _field[0].rc.left || stumpVec[i]->_monsterRect.right >= _field[0].rc.right)
		{

			if (stumpVec[i]->getIsLeft())
			{
				stumpVec[i]->setIsLeft(false);
				stumpVec[i]->_monsterRect.left += 2;
				stumpVec[i]->_monsterRect.right += 2;
				stumpVec[i]->setDistance(RND->getFromIntTo(50, 150));
			}
			else
			{
				stumpVec[i]->setIsLeft(true);
				stumpVec[i]->_monsterRect.left -= 2;
				stumpVec[i]->_monsterRect.right -= 2;
				stumpVec[i]->setDistance(RND->getFromIntTo(50, 150));
			}
		}
	}
	for (int i= 0; i < axeStumpVec.size(); i++)
	{
		if (axeStumpVec[i]->_monsterRect.left > _field[1].rc.left && axeStumpVec[i]->_monsterRect.right < _field[1].rc.right)
		{
			axeStumpVec[i]->monsterMove();
		}
		else if (axeStumpVec[i]->_monsterRect.left <= _field[1].rc.left || axeStumpVec[i]->_monsterRect.right >= _field[1].rc.right)
		{
			if (axeStumpVec[i]->getIsLeft())
			{
				axeStumpVec[i]->setIsLeft(false);
				axeStumpVec[i]->_monsterRect.left+=2;
				axeStumpVec[i]->_monsterRect.right+=2;
				axeStumpVec[i]->setDistance(RND->getFromIntTo(50, 150));
			}
			else
			{
				axeStumpVec[i]->setIsLeft(true);
				axeStumpVec[i]->_monsterRect.left -= 2;
				axeStumpVec[i]->_monsterRect.right -= 2;
				axeStumpVec[i]->setDistance(RND->getFromIntTo(50, 150));
			}
		}
	}
	
}

void huntingGround::monsterDie(void)
{

}

void huntingGround::monsterFrame(void)
{
	for (int i = 0; i < stumpVec.size(); i++)								//스텀프 프레임
	{
		stumpVec[i]->_monsterCount++;
		if (stumpVec[i]->getIsLeft())										//스텀프가 왼쪽을 볼때
		{
			if (stumpVec[i]->getIsMove() || stumpVec[i]->getIsChase())		//스텀프가 움직이거나 쫒을때
			{
				stumpVec[i]->setStartFrameY(1);
				IMAGEMANAGER->findImage("스텀프")->setFrameY(stumpVec[i]->getStartFrameY());
				if (stumpVec[i]->_monsterCount % 15 == 0)
				{
					stumpVec[i]->setStartFrameX(stumpVec[i]->getStartFrameX() + 1);
					if (stumpVec[i]->getStartFrameX() > 2)
					{
						stumpVec[i]->setStartFrameX(0);
					}
					IMAGEMANAGER->findImage("스텀프")->setFrameX(stumpVec[i]->getStartFrameX());
				}
			}
			else if (stumpVec[i]->getIsHit())									//스텀프가 공격당할때
			{
				stumpVec[i]->setStartFrameX(1);
				stumpVec[i]->setStartFrameY(0);
				IMAGEMANAGER->findImage("스텀프")->setFrameX(stumpVec[i]->getStartFrameX());
				IMAGEMANAGER->findImage("스텀프")->setFrameY(stumpVec[i]->getStartFrameY());
			}
			else if (stumpVec[i]->getIsDie())									//스텀프가 죽을때
			{
				stumpVec[i]->setStartFrameY(2);
				IMAGEMANAGER->findImage("스텀프")->setFrameY(stumpVec[i]->getStartFrameY());
				if (stumpVec[i]->_monsterCount % 15 == 0)
				{
					stumpVec[i]->setStartFrameX(stumpVec[i]->getStartFrameX() + 1);
					if (stumpVec[i]->getStartFrameX() > 2)
					{
						stumpVec[i]->setStartFrameX(2);
						stumpVec.erase(stumpVec.begin() + i);
						break;
					}
					IMAGEMANAGER->findImage("스텀프")->setFrameX(stumpVec[i]->getStartFrameX());
				}
			}
			else															//스텀프가 가만히 있을때
			{
				stumpVec[i]->setStartFrameX(0);
				stumpVec[i]->setStartFrameY(0);
				IMAGEMANAGER->findImage("스텀프")->setFrameX(stumpVec[i]->getStartFrameX());
				IMAGEMANAGER->findImage("스텀프")->setFrameY(stumpVec[i]->getStartFrameY());
			}
		}
		else																//스텀프가 오른쪽을 볼때
		{
			if (stumpVec[i]->getIsMove() || stumpVec[i]->getIsChase())		//스텀프가 움직이거나 쫒을때
			{
				stumpVec[i]->setStartFrameY(4);
				stumpVec[i]->setStartFrameY(stumpVec[i]->getStartFrameY());
				if (stumpVec[i]->_monsterCount % 15 == 0)
				{
					stumpVec[i]->setStartFrameX(stumpVec[i]->getStartFrameX() + 1);
					if (stumpVec[i]->getStartFrameX() > 2)
					{
						stumpVec[i]->setStartFrameX(0);
					}
					IMAGEMANAGER->findImage("스텀프")->setFrameX(stumpVec[i]->getStartFrameX());
				}
			}
			else if (stumpVec[i]->getIsHit())									//스텀프가 공격당할때
			{
				stumpVec[i]->setStartFrameX(1);
				stumpVec[i]->setStartFrameY(3);
				IMAGEMANAGER->findImage("스텀프")->setFrameX(stumpVec[i]->getStartFrameX());
				IMAGEMANAGER->findImage("스텀프")->setFrameY(stumpVec[i]->getStartFrameY());
			}
			else if (stumpVec[i]->getIsDie())									//스텀프가 죽을때
			{
				stumpVec[i]->setStartFrameY(5);
				IMAGEMANAGER->findImage("스텀프")->setFrameY(stumpVec[i]->getStartFrameY());
				if (stumpVec[i]->_monsterCount % 15 == 0)
				{
					stumpVec[i]->setStartFrameX(stumpVec[i]->getStartFrameX() + 1);
					if (stumpVec[i]->getStartFrameX() >2)
					{
						stumpVec[i]->setStartFrameX(2);
						stumpVec.erase(stumpVec.begin() + i);
						break;
					}
					IMAGEMANAGER->findImage("스텀프")->setFrameX(stumpVec[i]->getStartFrameX());
				}
			}
			else															//스텀프가 가만히 있을때
			{
				stumpVec[i]->setStartFrameX(0);
				stumpVec[i]->setStartFrameY(3);
				IMAGEMANAGER->findImage("스텀프")->setFrameX(stumpVec[i]->getStartFrameX());
				IMAGEMANAGER->findImage("스텀프")->setFrameY(stumpVec[i]->getStartFrameY());
			}
		}
	}
	
	for (int i = 0; i < axeStumpVec.size(); i++)								//엑스스텀프 프레임
	{
		axeStumpVec[i]->_monsterCount++;
		if (axeStumpVec[i]->getIsLeft())										//엑스스텀프가 왼쪽을 볼때
		{
			if (axeStumpVec[i]->getIsMove() || axeStumpVec[i]->getIsChase())		//엑스스텀프가 움직이거나 쫒을때
			{
				axeStumpVec[i]->setStartFrameY(1);
				IMAGEMANAGER->findImage("엑스스텀프")->setFrameY(axeStumpVec[i]->getStartFrameY());
				if (axeStumpVec[i]->_monsterCount % 15 == 0)
				{
					axeStumpVec[i]->setStartFrameX(axeStumpVec[i]->getStartFrameX() + 1);
					if (axeStumpVec[i]->getStartFrameX() > 2)
					{
						axeStumpVec[i]->setStartFrameX(0);
					}
					IMAGEMANAGER->findImage("엑스스텀프")->setFrameX(axeStumpVec[i]->getStartFrameX());
				}
			}
			else if (axeStumpVec[i]->getIsHit())									//엑스스텀프가 공격당할때
			{
				axeStumpVec[i]->setStartFrameX(1);
				axeStumpVec[i]->setStartFrameY(0);
				IMAGEMANAGER->findImage("엑스스텀프")->setFrameX(axeStumpVec[i]->getStartFrameX());
				IMAGEMANAGER->findImage("엑스스텀프")->setFrameY(axeStumpVec[i]->getStartFrameY());
			}
			else if (axeStumpVec[i]->getIsDie())									//엑스스텀프가 죽을때
			{
				axeStumpVec[i]->setStartFrameY(2);
				IMAGEMANAGER->findImage("엑스스텀프")->setFrameY(2);
				if (axeStumpVec[i]->_monsterCount % 15 == 0)
				{
					axeStumpVec[i]->setStartFrameX(axeStumpVec[i]->getStartFrameX() + 1);
					if (axeStumpVec[i]->getStartFrameX() > 3)
					{
						axeStumpVec[i]->setStartFrameX(3);
						axeStumpVec.erase(axeStumpVec.begin() + i);
						break;
					}
					IMAGEMANAGER->findImage("엑스스텀프")->setFrameX(axeStumpVec[i]->getStartFrameX());
				}
			}
			else															//엑스스텀프가 가만히 있을때
			{
				axeStumpVec[i]->setStartFrameX(0);
				axeStumpVec[i]->setStartFrameY(0);
				IMAGEMANAGER->findImage("엑스스텀프")->setFrameX(axeStumpVec[i]->getStartFrameX());
				IMAGEMANAGER->findImage("엑스스텀프")->setFrameY(axeStumpVec[i]->getStartFrameY());
			}
		}
		else																//엑스스텀프가 오른쪽을 볼때
		{
			if (axeStumpVec[i]->getIsMove() || axeStumpVec[i]->getIsChase())//엑스스텀프가 움직이거나 쫒을때
			{
				axeStumpVec[i]->setStartFrameY(4);
				IMAGEMANAGER->findImage("엑스스텀프")->setFrameY(4);
				if (axeStumpVec[i]->_monsterCount % 15 == 0)
				{
					axeStumpVec[i]->setStartFrameX(axeStumpVec[i]->getStartFrameX() + 1);
					if (axeStumpVec[i]->getStartFrameX() > 2)
					{
						axeStumpVec[i]->setStartFrameX(0);
					}
					IMAGEMANAGER->findImage("엑스스텀프")->setFrameX(axeStumpVec[i]->getStartFrameX());
				}
			}
			
			else if (axeStumpVec[i]->getIsHit())									//엑스스텀프가 공격당할때
			{
				axeStumpVec[i]->setStartFrameX(1);
				axeStumpVec[i]->setStartFrameY(3);
				IMAGEMANAGER->findImage("엑스스텀프")->setFrameX(axeStumpVec[i]->getStartFrameX());
				IMAGEMANAGER->findImage("엑스스텀프")->setFrameY(axeStumpVec[i]->getStartFrameY());
			}
			else if (axeStumpVec[i]->getIsDie())									//엑스스텀프가 죽을때
			{
				axeStumpVec[i]->setStartFrameY(5);
				IMAGEMANAGER->findImage("엑스스텀프")->setFrameY(5);
				if (axeStumpVec[i]->_monsterCount % 15 == 0)
				{
					axeStumpVec[i]->setStartFrameX(axeStumpVec[i]->getStartFrameX() + 1);
					if (axeStumpVec[i]->getStartFrameX() > 3)
					{
						axeStumpVec[i]->setStartFrameX(3);
						axeStumpVec.erase(axeStumpVec.begin() + i);
						break;
					}
					IMAGEMANAGER->findImage("엑스스텀프")->setFrameX(axeStumpVec[i]->getStartFrameX());
				}
			}
			else															//엑스스텀프가 가만히 있을때
			{
				axeStumpVec[i]->setStartFrameX(0);
				axeStumpVec[i]->setStartFrameY(3);
				IMAGEMANAGER->findImage("엑스스텀프")->setFrameX(axeStumpVec[i]->getStartFrameX());
				IMAGEMANAGER->findImage("엑스스텀프")->setFrameY(axeStumpVec[i]->getStartFrameY());
			}
		}
	}
}

void huntingGround::monsterIntersect(void)
{
	RECT rcTemp;
	
	for (int i = 0; i < stumpVec.size(); i++)
	{
		if (!stumpVec[i]->getIsDie())
		{
			if (IntersectRect(&rcTemp, &PLAYER->_javelin1._rc, &stumpVec[i]->_monsterRect))
			{
				stumpVec[i]->setIsHit(true);
				stumpVec[i]->setMonsterHp(stumpVec[i]->getMonsterHp() - 50);
				if (stumpVec[i]->getMonsterHp() <= 0)
				{
					stumpVec[i]->setIsDie(true);
				}
				PLAYER->_javelin1._time = 0;
				PLAYER->_javelin1._usingJavelin = false;
				PLAYER->_javelin1._rc.left = 1920;
				PLAYER->_javelin1._rc.right = PLAYER->_javelin1._rc.left + 30;
				PLAYER->_javelin1._rc.top = 1080;
				PLAYER->_javelin1._rc.bottom = PLAYER->_javelin1._rc.top + 30;
				if(!LUCKSEVEN->getIsUsing())PLAYER->_isAttack = false;		  //공격 비활성화
			}
			if (IntersectRect(&rcTemp, &PLAYER->_javelin2._rc, &stumpVec[i]->_monsterRect))
			{
				stumpVec[i]->setIsHit(true);
				test = 1;
				stumpVec[i]->setMonsterHp(stumpVec[i]->getMonsterHp() - 50);
				if (stumpVec[i]->getMonsterHp() <= 0)
				{
					stumpVec[i]->setIsDie(true);
				}
				LUCKSEVEN->setIsUsing(false);
				PLAYER->_isUsingSkill = false;
				PLAYER->_javelin2._time = 0;
				PLAYER->_javelin2._usingJavelin = false;
				PLAYER->_isAttack = false;		  //공격 비활성화
				PLAYER->_javelin2._rc.left = 1920;
				PLAYER->_javelin2._rc.right = PLAYER->_javelin2._rc.left + 30;
				PLAYER->_javelin2._rc.top = 1080;
				PLAYER->_javelin2._rc.bottom = PLAYER->_javelin2._rc.top + 30;
			}
			if (IntersectRect(&rcTemp, &SHURIKENBURST->_javelin.rc, &stumpVec[i]->_monsterRect))	
			{																							//스텀프, 슈리켄버스트 표창 충돌처리
				stumpVec[i]->setMonsterHp(stumpVec[i]->getMonsterHp() - SHURIKENBURST->getDamage());
				stumpVec[i]->setIsHit(true);
				if (stumpVec[i]->getMonsterHp() <= 0)
				{
					stumpVec[i]->setIsDie(true);
				}
			}
			if (IntersectRect(&rcTemp, &WINDTALISMAN->_javelin.rc, &stumpVec[i]->_monsterRect))			//스텀프, 윈드 탈리스만 표창 충돌처리
			{
				stumpVec[i]->setMonsterHp(stumpVec[i]->getMonsterHp() - WINDTALISMAN->getDamage());
				stumpVec[i]->setIsHit(true);
				if (stumpVec[i]->getMonsterHp() <= 0)
				{
					stumpVec[i]->setIsDie(true);
				}
			}
			if (IntersectRect(&rcTemp, &SHADESPLIT->_skillRange, &stumpVec[i]->_monsterRect))			//스텀프, 쉐이드스플릿 충돌처리
			{
				stumpVec[i]->setMonsterHp(stumpVec[i]->getMonsterHp() - SHADESPLIT->getDamage());
				stumpVec[i]->setIsHit(true);
				if (stumpVec[i]->getMonsterHp() <= 0)
				{
					stumpVec[i]->setIsDie(true);
				}
			}
		}
	}
	
	for (int i = 0; i < axeStumpVec.size(); i++)
	{
		if (!axeStumpVec[i]->getIsDie())
		{
			if (IntersectRect(&rcTemp, &PLAYER->_javelin1._rc, &axeStumpVec[i]->_monsterRect))
			{
				axeStumpVec[i]->setIsHit(true);
				axeStumpVec[i]->setMonsterHp(axeStumpVec[i]->getMonsterHp() - 50);
				if (axeStumpVec[i]->getMonsterHp() <= 0)
				{
					axeStumpVec[i]->setIsDie(true);
				}
				PLAYER->_javelin1._time = 0;
				PLAYER->_javelin1._usingJavelin = false;
				PLAYER->_isAttack = false;		  //공격 비활성화
				PLAYER->_javelin1._rc.left = 1920;
				PLAYER->_javelin1._rc.right = PLAYER->_javelin1._rc.left + 30;
				PLAYER->_javelin1._rc.top = 1080;
				PLAYER->_javelin1._rc.bottom = PLAYER->_javelin1._rc.top + 30;
			}
			if (IntersectRect(&rcTemp, &PLAYER->_javelin2._rc, &axeStumpVec[i]->_monsterRect))
			{
				axeStumpVec[i]->setIsHit(true);
				axeStumpVec[i]->setMonsterHp(axeStumpVec[i]->getMonsterHp() - 50);
				if (axeStumpVec[i]->getMonsterHp() <= 0)
				{
					axeStumpVec[i]->setIsDie(true);
				}
				LUCKSEVEN->setIsUsing(false);
				PLAYER->_isUsingSkill = false;
				PLAYER->_javelin2._time = 0;
				PLAYER->_javelin2._usingJavelin = false;
				PLAYER->_isAttack = false;		  //공격 비활성화
				PLAYER->_javelin2._rc.left = 1920;
				PLAYER->_javelin2._rc.right = PLAYER->_javelin2._rc.left + 30;
				PLAYER->_javelin2._rc.top = 1080;
				PLAYER->_javelin2._rc.bottom = PLAYER->_javelin2._rc.top + 30;
			}
			if (IntersectRect(&rcTemp, &SHURIKENBURST->_javelin.rc, &axeStumpVec[i]->_monsterRect))				//엑스스텀프, 슈리켄버스트 표창 충돌처리
			{
				axeStumpVec[i]->setMonsterHp(axeStumpVec[i]->getMonsterHp() - SHURIKENBURST->getDamage());
				axeStumpVec[i]->setIsHit(true);
				if (axeStumpVec[i]->getMonsterHp() <= 0)
				{
					axeStumpVec[i]->setIsDie(true);
				}
			}
			if (IntersectRect(&rcTemp, &WINDTALISMAN->_javelin.rc, &axeStumpVec[i]->_monsterRect))				//엑스스텀프, 윈드 탈리스만 표창 충돌처리
			{
				axeStumpVec[i]->setMonsterHp(axeStumpVec[i]->getMonsterHp() - WINDTALISMAN->getDamage());
				axeStumpVec[i]->setIsHit(true);
				if (axeStumpVec[i]->getMonsterHp() <= 0)
				{
					axeStumpVec[i]->setIsDie(true);
				}
			}
			if (IntersectRect(&rcTemp, &SHADESPLIT->_skillRange, &axeStumpVec[i]->_monsterRect))				//엑스스텀프, 쉐이드스플릿 충돌처리
			{
				axeStumpVec[i]->setMonsterHp(axeStumpVec[i]->getMonsterHp() - SHADESPLIT->getDamage());
				axeStumpVec[i]->setIsHit(true);
				if (axeStumpVec[i]->getMonsterHp() <= 0)
				{
					axeStumpVec[i]->setIsDie(true);
				}
			}
		}
	}
	for (int i = 0; i < stumpVec.size(); i++)											//스텀프와 플레이어 충돌처리
	{
		if (IntersectRect(&rcTemp, &PLAYER->_playerRect.rc, &stumpVec[i]->_monsterRect))
		{
			if ((PLAYER->_playerRect.rc.left < stumpVec[i]->_monsterRect.right - 25 || PLAYER->_playerRect.rc.right < stumpVec[i]->_monsterRect.left + 25)
				&& PLAYER->_playerRect.rc.bottom > stumpVec[i]->_monsterRect.top + 25)
			{
				if (!PLAYER->_isHurt)
				{
					PLAYER->_playerRect.hp.left --;
					PLAYER->_playerRect.hp.right --;
					PLAYER->_isHit = true;
				}
			}
		}
		if (PLAYER->_isHit)
		{
			PLAYER->_playerRect.time += 0.03;
			if (PLAYER->_playerRect.rc.left > stumpVec[i]->_monsterRect.left)
			{
				PLAYER->_playerRect.rc.left += 1;
				PLAYER->_playerRect.rc.right += 1;

				PLAYER->_isHurt = true;
			}
			else if (PLAYER->_playerRect.rc.right < stumpVec[i]->_monsterRect.right)
			{
				PLAYER->_playerRect.rc.left -= 1;
				PLAYER->_playerRect.rc.right -= 1;
				PLAYER->_isHurt = true;
			}
			if(!PLAYER->_isJump)
			{
				PLAYER->_playerRect.rc.top = -(sinf(PI / 2) * 2 - PLAYER->_playerRect.time) + PLAYER->_playerRect.rc.top;
				PLAYER->_playerRect.rc.bottom = -(sinf(PI / 2) * 2 - PLAYER->_playerRect.time) + PLAYER->_playerRect.rc.bottom;
			}
		}
	}
	
	for (int i = 0; i < axeStumpVec.size(); i++)											//엑스스텀프와 플레이어 충돌처리
	{
		if (IntersectRect(&rcTemp, &PLAYER->_playerRect.rc, &axeStumpVec[i]->_monsterRect))
		{
			if ((PLAYER->_playerRect.rc.left < axeStumpVec[i]->_monsterRect.right - 25 || PLAYER->_playerRect.rc.right < axeStumpVec[i]->_monsterRect.left + 25)
				||  PLAYER->_playerRect.rc.bottom > axeStumpVec[i]->_monsterRect.top + 25)
			{
				if (!PLAYER->_isHurt)
				{
					PLAYER->_playerRect.hp.left-=3;
					PLAYER->_playerRect.hp.right-=3;
					PLAYER->_isHit = true;
				}
			}
		}
		if (PLAYER->_isHit)
		{
			PLAYER->_playerRect.time += 0.03;
			if (PLAYER->_playerRect.rc.left > axeStumpVec[i]->_monsterRect.left)
			{
				PLAYER->_playerRect.rc.left += 1;
				PLAYER->_playerRect.rc.right += 1;

				PLAYER->_isHurt = true;
			}
			else if (PLAYER->_playerRect.rc.right < axeStumpVec[i]->_monsterRect.right)
			{
				PLAYER->_playerRect.rc.left -= 1;
				PLAYER->_playerRect.rc.right -= 1;
				PLAYER->_isHurt = true;
			}
			if (!PLAYER->_isJump)
			{
				PLAYER->_playerRect.rc.top = -(sinf(PI / 2) * 2 - PLAYER->_playerRect.time) + PLAYER->_playerRect.rc.top;
				PLAYER->_playerRect.rc.bottom = -(sinf(PI / 2) * 2 -PLAYER->_playerRect.time) + PLAYER->_playerRect.rc.bottom;
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
