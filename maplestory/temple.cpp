#include "stdafx.h"
#include "temple.h"

HRESULT temple::init(void)
{
	setIsInPlayer(false);
	setIsLeft(false);
	setIsRight(false);
	IMAGEMANAGER->addImage("신전", "Map/신전.bmp", 1920, 1080);																		//배경
	IMAGEMANAGER->addFrameImage("portal", "Map/portal.bmp", 1286, 133, 14, 1, true, RGB(255, 0, 255));								//포탈
	IMAGEMANAGER->addFrameImage("드레이크", "Monster/Drake.bmp", 1331, 606, 6, 6, true, RGB(255, 0, 255));							//드레이크
	IMAGEMANAGER->addFrameImage("카파드레이크", "Monster/CopperDrake.bmp", 1329, 624, 6, 6, true, RGB(255, 0, 255));				//드레이크
	IMAGEMANAGER->addFrameImage("주니어발록", "Monster/주니어발록/balrog.bmp", 5330, 2776, 10, 12, true, RGB(255, 0, 255));			//주니어발록
	IMAGEMANAGER->addFrameImage("메테오", "Monster/주니어발록/메테오.bmp", 978, 133, 6, 1, true, RGB(255, 0, 255));					//메테오
	IMAGEMANAGER->addFrameImage("매직클로", "Monster/주니어발록/매직클로.bmp", 349, 99, 4,1, true, RGB(255, 0, 255));				//파이어볼
	IMAGEMANAGER->addImage("발록체력바", "Monster/UI/발록체력바.bmp", 750, 34, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("빈체력바", "Monster/UI/몬스터빈체력바.bmp", 710, 10);
	bossHp = RectMake(168, 10, 710, 10);
	_field[0] = RectMake(0,1010,1920,50);
	_field[1] = RectMake(0, 290, 230, 30);
	_field[2] = RectMake(160, 330, 230, 30);
	_field[3] = RectMake(450, 280, 170, 30);
	_field[4] = RectMake(0, 560, 230, 30);
	_field[5] = RectMake(620, 490, 190, 30);
	_field[6] = RectMake(950, 370, 20, 30);
	_field[7] = RectMake(1030, 340, 220, 50);
	_field[8] = RectMake(1180, 220, 170, 30);
	_field[9] = RectMake(1410, 95, 210, 30);
	_field[10] = RectMake(1280, 560, 460, 50);
	_field[11] = RectMake(1870, 450, 50, 50);
	//옆으로 못가게 하는 벽들
	_field[12] = RectMake(40, 290, 50, 50);
	_field[13] = RectMake(1800, 490, 30, 50);
	_field[14] = RectMake(1790, 500, 30, 30);
	_field[15] = RectMake(1850, 470, 30, 30);
	_portal.rc = RectMake(50, 150, 92, 133);								//포탈 사각형(머쉬맘 필드 가는길)
	_portal.portalFrame = 0;
	_bgSpeedX = _bgSpeedY = 0;
	_deadCount = 0;
	_JuniorBalrog = new JuniorBalrog;
	return S_OK;
}

void temple::update(void)
{
	RECT rcTemp;
	_count++;
	PLAYER->_playerRect.rc.top += GRAVITY;			//밑으로 중력 작용
	PLAYER->_playerRect.rc.bottom += GRAVITY;
	intersectFeild();								//사각형 충돌
	portalFrame();									//포탈 프레임
	monsterSpawn();									//몬스터 소환
	monsterIntersect();
	monsterFrame();									//몬스터 프레임
	
	PLAYER->_isPlayerMoveMap = true;
	
	if (PLAYER->_playerRect.rc.right > WINSIZEX / 2 + 150 && _bgSpeedX < 967) //오른쪽으로 이동하면 화면이 따라온다
	{
		if (PLAYER->_isPlayerMoveMap)
		{
			_bgSpeedX += 3;
			PLAYER->_playerRect.rc.left -= 3;
			PLAYER->_playerRect.rc.right -= 3;
			for (int i = 0; i < 16; i++)
			{
				_field[i].left -= 3;
				_field[i].right -= 3;
			}
			_portal.rc.left -= 3;
			_portal.rc.right -= 3;
			for (int i = 0; i < drakeVec.size(); i++)
			{
				drakeVec[i]->_monsterRect.left -= 3;
				drakeVec[i]->_monsterRect.right -= 3;
			}
			for (int i = 0; i < copperDrakeVec.size(); i++)
			{
				copperDrakeVec[i]->_monsterRect.left -= 3;
				copperDrakeVec[i]->_monsterRect.right -= 3;
			}

			_JuniorBalrog->_monsterRect.left -= 3;
			_JuniorBalrog->_monsterRect.right -= 3;
			if (PLAYER->_jumpCount > 2 && !PLAYER->_isLeft)
			{
				_bgSpeedX += 7;
				PLAYER->_playerRect.rc.left -= 7;
				PLAYER->_playerRect.rc.right -= 7;
				for (int i = 0; i < 16;i++)					//바닥 이동
				{
					_field[i].left -= 7;
					_field[i].right -= 7;
				}
				for (int i = 0; i < 2; i++)					//포탈도 이동
				{
					_portal.rc.left -= 7;
					_portal.rc.right -= 7;
				}

				for (int i = 0; i < drakeVec.size(); i++)
				{
					drakeVec[i]->_monsterRect.left -= 7;
					drakeVec[i]->_monsterRect.right -= 7;
				}
				for (int i = 0; i < copperDrakeVec.size();i++)
				{
					copperDrakeVec[i]->_monsterRect.left -= 7;
					copperDrakeVec[i]->_monsterRect.right -= 7;
				}
				_JuniorBalrog->_monsterRect.left -= 7;
				_JuniorBalrog->_monsterRect.right -= 7;
			}
		}
		else
		{
			_bgSpeedX += 9;
			PLAYER->_playerRect.rc.left -= 9;
			PLAYER->_playerRect.rc.right -= 9;
			for (int i = 0; i < 16; i++)
			{
				_field[i].left -= 9;
				_field[i].right -= 9;
			}
			_portal.rc.left -= 3;
			_portal.rc.right -= 3;
			for (int i = 0; i < drakeVec.size(); i++)
			{
				drakeVec[i]->_monsterRect.left -= 9;
				drakeVec[i]->_monsterRect.right -= 9;
			}
			for (int i = 0; i < copperDrakeVec.size(); i++)
			{
				copperDrakeVec[i]->_monsterRect.left -= 9;
				copperDrakeVec[i]->_monsterRect.right -= 9;
			}

			_JuniorBalrog->_monsterRect.left -= 9;
			_JuniorBalrog->_monsterRect.right -= 9;
		}
	}
	else if (PLAYER->_playerRect.rc.left < WINSIZEX / 2 - 150 && _bgSpeedX >0)//왼쪽으로 이동하면 화면이 따라온다
	{
		if (PLAYER->_isPlayerMoveMap)
		{
			_bgSpeedX -= 3;
			PLAYER->_playerRect.rc.left += 3;
			PLAYER->_playerRect.rc.right += 3;
			for (int i = 0; i < 16; i++)
			{
				_field[i].left += 3;
				_field[i].right += 3;
			}
			_portal.rc.left += 3;
			_portal.rc.right += 3;
			for (int i = 0; i < drakeVec.size(); i++)
			{
				drakeVec[i]->_monsterRect.left += 3;
				drakeVec[i]->_monsterRect.right += 3;
			}
			for (int i = 0; i < copperDrakeVec.size(); i++)
			{
				copperDrakeVec[i]->_monsterRect.left += 3;
				copperDrakeVec[i]->_monsterRect.right += 3;
			}
			_JuniorBalrog->_monsterRect.left += 3;
			_JuniorBalrog->_monsterRect.right += 3;
			if (PLAYER->_jumpCount > 2 && PLAYER->_isLeft)
			{
				_bgSpeedX -= 7;
				PLAYER->_playerRect.rc.left += 7;
				PLAYER->_playerRect.rc.right += 7;
				for (int i = 0; i < 16;i++)					//바닥 이동
				{
					_field[i].left += 7;
					_field[i].right += 7;
				}
				for (int i = 0; i < 2; i++)					//포탈도 이동
				{
					_portal.rc.left += 7;
					_portal.rc.right += 7;
				}

				for (int i = 0; i < drakeVec.size(); i++)
				{
					drakeVec[i]->_monsterRect.left += 7;
					drakeVec[i]->_monsterRect.right += 7;
				}
				for (int i = 0; i < copperDrakeVec.size();i++)
				{
					copperDrakeVec[i]->_monsterRect.left += 7;
					copperDrakeVec[i]->_monsterRect.right += 7;
				}
				_JuniorBalrog->_monsterRect.left += 7;
				_JuniorBalrog->_monsterRect.right += 7;
			}
		}
		else
		{
			_bgSpeedX -= 9;
			PLAYER->_playerRect.rc.left += 9;
			PLAYER->_playerRect.rc.right += 9;
			for (int i = 0; i < 16; i++)
			{
				_field[i].left += 9;
				_field[i].right += 9;
			}
			_portal.rc.left += 9;
			_portal.rc.right += 9;
			for (int i = 0; i < drakeVec.size(); i++)
			{
				drakeVec[i]->_monsterRect.left += 9;
				drakeVec[i]->_monsterRect.right += 9;
			}
			for (int i = 0; i < copperDrakeVec.size(); i++)
			{
				copperDrakeVec[i]->_monsterRect.left += 9;
				copperDrakeVec[i]->_monsterRect.right += 9;
			}
			_JuniorBalrog->_monsterRect.left += 9;
			_JuniorBalrog->_monsterRect.right += 9;
		}
	}
	else if (PLAYER->_playerRect.rc.bottom > WINSIZEY / 2 + 150 && _bgSpeedY < 445)//아래쪽으로 이동하면 화면이 따라온다
	{
		if (PLAYER->_isPlayerMoveMap)
		{
			_bgSpeedY += 9;
			PLAYER->_playerRect.rc.top -= 9;
			PLAYER->_playerRect.rc.bottom -= 9;
			for (int i = 0; i < 16; i++)
			{
				_field[i].top -= 9;
				_field[i].bottom -= 9;
			}
			_portal.rc.top -= 9;
			_portal.rc.bottom -= 9;
			for (int i = 0; i < drakeVec.size(); i++)
			{
				drakeVec[i]->_monsterRect.top -= 9;
				drakeVec[i]->_monsterRect.bottom -= 9;
			}
			for (int i = 0; i < copperDrakeVec.size(); i++)
			{
				copperDrakeVec[i]->_monsterRect.top -= 9;
				copperDrakeVec[i]->_monsterRect.bottom -= 9;
			}
			_JuniorBalrog->_monsterRect.top -= 9;
			_JuniorBalrog->_monsterRect.bottom -= 9;
		}

	}
	else if (PLAYER->_playerRect.rc.top < WINSIZEY / 2 - 150 && _bgSpeedY >0)//위쪽으로 이동하면 화면이 따라온다
	{
		if (PLAYER->_isPlayerMoveMap)
		{
			_bgSpeedY -= 3;
			PLAYER->_playerRect.rc.top += 3;
			PLAYER->_playerRect.rc.bottom += 3;
			for (int i = 0; i < 16; i++)
			{
				_field[i].top += 3;
				_field[i].bottom += 3;
			}
			_portal.rc.top += 3;
			_portal.rc.bottom += 3;
			for (int i = 0; i < drakeVec.size(); i++)
			{
				drakeVec[i]->_monsterRect.top += 3;
				drakeVec[i]->_monsterRect.bottom += 3;
			}
			for (int i = 0; i < copperDrakeVec.size(); i++)
			{
				copperDrakeVec[i]->_monsterRect.top += 3;
				copperDrakeVec[i]->_monsterRect.bottom += 3;
			}
			_JuniorBalrog->_monsterRect.top += 3;
			_JuniorBalrog->_monsterRect.bottom += 3;
		}
		else
		{
			_bgSpeedY -= 9;
			PLAYER->_playerRect.rc.top += 9;
			PLAYER->_playerRect.rc.bottom += 9;
			for (int i = 0; i < 16; i++)
			{
				_field[i].top += 9;
				_field[i].bottom += 9;
			}
			_portal.rc.top += 9;
			_portal.rc.bottom += 9;
			for (int i = 0; i < drakeVec.size(); i++)
			{
				drakeVec[i]->_monsterRect.top += 9;
				drakeVec[i]->_monsterRect.bottom += 9;
			}
			for (int i = 0; i < copperDrakeVec.size(); i++)
			{
				copperDrakeVec[i]->_monsterRect.top += 9;
				copperDrakeVec[i]->_monsterRect.bottom += 9;
			}
			_JuniorBalrog->_monsterRect.top += 9;
			_JuniorBalrog->_monsterRect.bottom += 9;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (IntersectRect(&rcTemp, &PLAYER->_playerRect.rc, &_portal.rc))
		{
			setIsRight(true);
		}
	}
	if (PLAYER->_moveCount == 1) //헤네시스 사냥터에서 왔으면 포탑위에서 나타남
	{
		PLAYER->_playerRect.rc.left = _portal.rc.left;
		PLAYER->_playerRect.rc.right = PLAYER->_playerRect.rc.left + 79;
		PLAYER->_playerRect.rc.bottom = _portal.rc.top;
		PLAYER->_playerRect.rc.top = PLAYER->_playerRect.rc.bottom - 85;
		PLAYER->_moveCount = 0;
	}
}

void temple::release(void)
{
}

void temple::render(HDC hdc)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	char str[128];
	IMAGEMANAGER->loopRender("신전", getMemDC(), &RectMake(0, 0, 1920, 1080), _bgSpeedX, _bgSpeedY);
	IMAGEMANAGER->frameRender("portal", getMemDC(), _portal.rc.left, _portal.rc.top);
	if (_JuniorBalrog->isreal)
	{
		IMAGEMANAGER->frameRender("메테오", getMemDC(), _JuniorBalrog->_skill[0].rc.left, _JuniorBalrog->_skill[0].rc.top);
		IMAGEMANAGER->frameRender("매직클로", getMemDC(), _JuniorBalrog->_skill[1].rc.left, _JuniorBalrog->_skill[1].rc.top);
		IMAGEMANAGER->frameRender("주니어발록", getMemDC(), _JuniorBalrog->_monsterRect.left, _JuniorBalrog->_monsterRect.top);
		IMAGEMANAGER->render("빈체력바", getMemDC(), 168, 12);
		bossHpColor = CreateSolidBrush(RGB(255, 0, 0));
		FillRect(getMemDC(), &bossHp, bossHpColor);
		IMAGEMANAGER->render("발록체력바", getMemDC(), 130, 8);
	}
	for (int i = 0; i < drakeVec.size();i++)
	{
		IMAGEMANAGER->frameRender("드레이크", getMemDC(), drakeVec[i]->_monsterRect.left, drakeVec[i]->_monsterRect.top, drakeVec[i]->getStartFrameX(), drakeVec[i]->getStartFrameY());
	}
	for (int i = 0; i < copperDrakeVec.size(); i++)
	{
		IMAGEMANAGER->frameRender("카파드레이크", getMemDC(), copperDrakeVec[i]->_monsterRect.left, copperDrakeVec[i]->_monsterRect.top, copperDrakeVec[i]->getStartFrameX(), copperDrakeVec[i]->getStartFrameY());
	}

	this->getBackBuffer()->render(getHDC());
}

void temple::intersectFeild(void)
{
	RECT rcTemp;
	for (int i = 0; i < 12; i++)
	{
		if (IntersectRect(&rcTemp, &PLAYER->_playerRect.rc, &_field[i]))
		{
			PLAYER->_playerRect.rc.bottom = _field[i].top;
			PLAYER->_playerRect.rc.top = PLAYER->_playerRect.rc.bottom - 85;
			PLAYER->_playerRect.time = 0;
			PLAYER->_isJump = false;
			PLAYER->_isHit = false;
			PLAYER->_jumpCount = 0;
		}
	}
	if (IntersectRect(&rcTemp, &PLAYER->_playerRect.rc, &_field[12]))
	{
		PLAYER->_playerRect.rc.left += 3;
		PLAYER->_playerRect.rc.right += 3;
	}
	if (IntersectRect(&rcTemp, &PLAYER->_playerRect.rc, &_field[13]))
	{
		
		if (PLAYER->_playerRect.rc.top < _field[13].top)
		{
			PLAYER->_playerRect.rc.bottom = _field[13].top;
			PLAYER->_playerRect.rc.top = PLAYER->_playerRect.rc.bottom - 85;
			PLAYER->_playerRect.time = 0;
			PLAYER->_isJump = false;
			PLAYER->_isHit = false;
			PLAYER->_jumpCount = 0;
		}
	}
	if (IntersectRect(&rcTemp, &PLAYER->_playerRect.rc, &_field[14]) || IntersectRect(&rcTemp, &PLAYER->_playerRect.rc, &_field[15]))
	{
		PLAYER->_playerRect.rc.left -= 3;
		PLAYER->_playerRect.rc.right -= 3;
	}

}

void temple::portalFrame(void)
{
	IMAGEMANAGER->findImage("portal")->setFrameY(0);
	if (_count % 7 == 0)
	{
		_portal.portalFrame++;
		if (_portal.portalFrame > 13)
		{
			_portal.portalFrame = 0;
		}
		IMAGEMANAGER->findImage("portal")->setFrameX(_portal.portalFrame);
	}
}

void temple::monsterSpawn(void)
{
	if (drakeVec.size() < 5)								//드레이크 소환
	{
		_drake = new drake;
		drakeVec.push_back(_drake);
	}
	if (copperDrakeVec.size() < 5)							//카파드레이크 소환
	{
		_copperDrake = new copperDrake;
		copperDrakeVec.push_back(_copperDrake);
	}
	for (int i = 0; i < copperDrakeVec.size();i++)
	{
		if (drakeVec[i]->_monsterRect.left > _field[0].left && drakeVec[i]->_monsterRect.right < _field[0].right)
		{
			drakeVec[i]->monsterMove();
		}
		else if (drakeVec[i]->_monsterRect.left <= _field[0].left || drakeVec[i]->_monsterRect.right >= _field[0].right)
		{

			if (drakeVec[i]->getIsLeft())
			{
				drakeVec[i]->setIsLeft(false);
				drakeVec[i]->_monsterRect.left += 2;
				drakeVec[i]->_monsterRect.right += 2;
				drakeVec[i]->setDistance(RND->getFromIntTo(50, 150));
			}
			else
			{
				drakeVec[i]->setIsLeft(true);
				drakeVec[i]->_monsterRect.left -= 2;
				drakeVec[i]->_monsterRect.right -= 2;
				drakeVec[i]->setDistance(RND->getFromIntTo(50, 150));
			}
		}
	}
	for (int i = 0; i < copperDrakeVec.size(); i++)
	{
		if (copperDrakeVec[i]->_monsterRect.left > _field[0].left && copperDrakeVec[i]->_monsterRect.right < _field[0].right)
		{
			copperDrakeVec[i]->monsterMove();
		}
		else if (copperDrakeVec[i]->_monsterRect.left <= _field[0].left || copperDrakeVec[i]->_monsterRect.right >= _field[0].right)
		{
			if (copperDrakeVec[i]->getIsLeft())
			{
				copperDrakeVec[i]->setIsLeft(false);
				copperDrakeVec[i]->_monsterRect.left += 2;
				copperDrakeVec[i]->_monsterRect.right += 2;
				copperDrakeVec[i]->setDistance(RND->getFromIntTo(50, 150));
			}
			else
			{
				copperDrakeVec[i]->setIsLeft(true);
				copperDrakeVec[i]->_monsterRect.left -= 2;
				copperDrakeVec[i]->_monsterRect.right -= 2;
				copperDrakeVec[i]->setDistance(RND->getFromIntTo(50, 150));
			}
		}
	}
	if (_deadCount > 9)
	{
		_JuniorBalrog->isreal = true;
	}
	if (_JuniorBalrog->isreal)
	{
		if (_JuniorBalrog->_monsterRect.left > _field[0].left && _JuniorBalrog->_monsterRect.right < _field[0].right)		//주니어발록이 이동할수있는 곳
		{
			_JuniorBalrog->monsterMove();
		}
		else if (_JuniorBalrog->_monsterRect.left <= _field[0].left || _JuniorBalrog->_monsterRect.right >= _field[0].right)
		{
			if (_JuniorBalrog->getIsLeft())
			{
				_JuniorBalrog->setIsLeft(false);
				_JuniorBalrog->_monsterRect.left += 2;
				_JuniorBalrog->_monsterRect.right += 2;
				_JuniorBalrog->setDistance(RND->getFromIntTo(50, 150));
			}
			else
			{
				_JuniorBalrog->setIsLeft(true);
				_JuniorBalrog->_monsterRect.left -= 2;
				_JuniorBalrog->_monsterRect.right -= 2;
				_JuniorBalrog->setDistance(RND->getFromIntTo(50, 150));
			}
		}
		if (PLAYER->_playerRect.rc.left > _JuniorBalrog->_monsterRect.left && PLAYER->_playerRect.rc.right < _JuniorBalrog->_monsterRect.right && PLAYER->_playerRect.rc.top >_JuniorBalrog->_monsterRect.top)
		{
			_JuniorBalrog->usingSkill();
		}
		
		for (int i = 0; i < 2; i++)
		{
			if (_JuniorBalrog->_skill[i].skillEnd)
			{
				_JuniorBalrog->coolDownTime--;
				_JuniorBalrog->_skill[i].rc.left = 1920;
				_JuniorBalrog->_skill[i].rc.right = _JuniorBalrog->_skill[i].rc.left + 163;
				_JuniorBalrog->_skill[i].rc.top = 1080;
				_JuniorBalrog->_skill[i].rc.bottom = _JuniorBalrog->_skill[i].rc.left + 133;
			}
		}
		if (bossHp.right - bossHp.left <= 360)
		{
			_JuniorBalrog->skillSelect = 0;
		}
	}
}

void temple::monsterFrame(void)
{
	for (int i = 0; i < drakeVec.size(); i++)								//드레이크 프레임
	{
		drakeVec[i]->_monsterCount++;
		if (drakeVec[i]->getIsLeft())										//드레이크가 왼쪽을 볼때
		{
			if (drakeVec[i]->getIsMove() || drakeVec[i]->getIsChase())		//드레이크가 움직이거나 쫒을때
			{
				drakeVec[i]->setStartFrameY(1);
				IMAGEMANAGER->findImage("드레이크")->setFrameY(drakeVec[i]->getStartFrameY());
				if (drakeVec[i]->_monsterCount % 15 == 0)
				{
					drakeVec[i]->setStartFrameX(drakeVec[i]->getStartFrameX() + 1);
					if (drakeVec[i]->getStartFrameX() > 3)
					{
						drakeVec[i]->setStartFrameX(0);
					}
					IMAGEMANAGER->findImage("드레이크")->setFrameX(drakeVec[i]->getStartFrameX());
				}
			}
			
			else if (drakeVec[i]->getIsHit())									//드레이크가 공격당할때
			{
				drakeVec[i]->setStartFrameX(1);
				drakeVec[i]->setStartFrameY(0);
				IMAGEMANAGER->findImage("드레이크")->setFrameX(drakeVec[i]->getStartFrameX());
				IMAGEMANAGER->findImage("드레이크")->setFrameY(drakeVec[i]->getStartFrameY());
			}
			else if (drakeVec[i]->getIsDie())									//드레이크가 죽을때
			{
				drakeVec[i]->setStartFrameY(2);
				IMAGEMANAGER->findImage("드레이크")->setFrameY(drakeVec[i]->getStartFrameY());
				if (drakeVec[i]->_monsterCount % 10 == 0)
				{
					drakeVec[i]->setStartFrameX(drakeVec[i]->getStartFrameX() + 1);
					if (drakeVec[i]->getStartFrameX() >5)
					{
						drakeVec[i]->setStartFrameX(5);
						drakeVec.erase(drakeVec.begin() + i);
						_deadCount++;
						break;
					}
					IMAGEMANAGER->findImage("드레이크")->setFrameX(drakeVec[i]->getStartFrameX());
				}
			}
			else															//드레이크가 가만히 있을때
			{
				drakeVec[i]->setStartFrameX(0);
				drakeVec[i]->setStartFrameY(0);
				IMAGEMANAGER->findImage("드레이크")->setFrameX(drakeVec[i]->getStartFrameX());
				IMAGEMANAGER->findImage("드레이크")->setFrameY(drakeVec[i]->getStartFrameY());
			}
		}
		else																//드레이크가 오른쪽을 볼때
		{
			if (drakeVec[i]->getIsMove() || drakeVec[i]->getIsChase())		//드레이크가 움직이거나 쫒을때
			{
				drakeVec[i]->setStartFrameY(4);
				drakeVec[i]->setStartFrameY(drakeVec[i]->getStartFrameY());
				if (drakeVec[i]->_monsterCount % 15 == 0)
				{
					drakeVec[i]->setStartFrameX(drakeVec[i]->getStartFrameX() + 1);
					if (drakeVec[i]->getStartFrameX() > 3)
					{
						drakeVec[i]->setStartFrameX(0);
					}
					IMAGEMANAGER->findImage("드레이크")->setFrameX(drakeVec[i]->getStartFrameX());
				}
			}
			
			else if (drakeVec[i]->getIsHit())									//드레이크가 공격당할때
			{
				drakeVec[i]->setStartFrameX(1);
				drakeVec[i]->setStartFrameY(3);
				IMAGEMANAGER->findImage("드레이크")->setFrameX(drakeVec[i]->getStartFrameX());
				IMAGEMANAGER->findImage("드레이크")->setFrameY(drakeVec[i]->getStartFrameY());
			}
			else if (drakeVec[i]->getIsDie())									//드레이크가 죽을때
			{
				drakeVec[i]->setStartFrameY(5);
				IMAGEMANAGER->findImage("드레이크")->setFrameY(drakeVec[i]->getStartFrameY());
				if (drakeVec[i]->_monsterCount % 10 == 0)
				{
					drakeVec[i]->setStartFrameX(drakeVec[i]->getStartFrameX() + 1);
					if (drakeVec[i]->getStartFrameX() >5)
					{
						drakeVec[i]->setStartFrameX(5);
						drakeVec.erase(drakeVec.begin() + i);
						_deadCount++;
						break;
					}
					IMAGEMANAGER->findImage("드레이크")->setFrameX(drakeVec[i]->getStartFrameX());
				}
			}
			else															//드레이크가 가만히 있을때
			{
				drakeVec[i]->setStartFrameX(0);
				drakeVec[i]->setStartFrameY(3);
				IMAGEMANAGER->findImage("드레이크")->setFrameX(drakeVec[i]->getStartFrameX());
				IMAGEMANAGER->findImage("드레이크")->setFrameY(drakeVec[i]->getStartFrameY());
			}
		}
	}

	for (int i = 0; i < copperDrakeVec.size(); i++)								//카파드레이크 프레임
	{
		copperDrakeVec[i]->_monsterCount++;
		if (copperDrakeVec[i]->getIsLeft())										//카파드레이크가 왼쪽을 볼때
		{
			if (copperDrakeVec[i]->getIsMove() || copperDrakeVec[i]->getIsChase())	//카파드레이크가 움직이거나 쫒을때
			{
				copperDrakeVec[i]->setStartFrameY(1);
				IMAGEMANAGER->findImage("카파드레이크")->setFrameY(copperDrakeVec[i]->getStartFrameY());
				if (copperDrakeVec[i]->_monsterCount % 15 == 0)
				{
					copperDrakeVec[i]->setStartFrameX(copperDrakeVec[i]->getStartFrameX() + 1);
					if (copperDrakeVec[i]->getStartFrameX() > 3)
					{
						copperDrakeVec[i]->setStartFrameX(0);
					}
					IMAGEMANAGER->findImage("카파드레이크")->setFrameX(copperDrakeVec[i]->getStartFrameX());
				}
			}
			
			else if (copperDrakeVec[i]->getIsHit())									//카파드레이크가 공격당할때
			{
				copperDrakeVec[i]->setStartFrameX(1);
				copperDrakeVec[i]->setStartFrameY(0);
				IMAGEMANAGER->findImage("카파드레이크")->setFrameX(copperDrakeVec[i]->getStartFrameX());
				IMAGEMANAGER->findImage("카파드레이크")->setFrameY(copperDrakeVec[i]->getStartFrameY());
			}
			else if (copperDrakeVec[i]->getIsDie())									//카파드레이크가 죽을때
			{
				copperDrakeVec[i]->setStartFrameY(2);
				IMAGEMANAGER->findImage("카파드레이크")->setFrameY(2);
				if (copperDrakeVec[i]->_monsterCount % 10 == 0)
				{
					copperDrakeVec[i]->setStartFrameX(copperDrakeVec[i]->getStartFrameX() + 1);
					if (copperDrakeVec[i]->getStartFrameX() >5)
					{
						copperDrakeVec[i]->setStartFrameX(5);
						copperDrakeVec.erase(copperDrakeVec.begin() + i);
						_deadCount++;
						break;
					}
					IMAGEMANAGER->findImage("카파드레이크")->setFrameX(copperDrakeVec[i]->getStartFrameX());
				}
			}
			else															//카파드레이크가 가만히 있을때
			{
				copperDrakeVec[i]->setStartFrameX(0);
				copperDrakeVec[i]->setStartFrameY(0);
				IMAGEMANAGER->findImage("카파드레이크")->setFrameX(copperDrakeVec[i]->getStartFrameX());
				IMAGEMANAGER->findImage("카파드레이크")->setFrameY(copperDrakeVec[i]->getStartFrameY());
			}
		}
		else																//카파드레이크가 오른쪽을 볼때
		{
			if (copperDrakeVec[i]->getIsMove() || copperDrakeVec[i]->getIsChase())	//카파드레이크가 움직이거나 쫒을때
			{
				copperDrakeVec[i]->setStartFrameY(4);
				IMAGEMANAGER->findImage("카파드레이크")->setFrameY(4);
				if (copperDrakeVec[i]->_monsterCount % 15 == 0)
				{
					copperDrakeVec[i]->setStartFrameX(copperDrakeVec[i]->getStartFrameX() + 1);
					if (copperDrakeVec[i]->getStartFrameX() > 3)
					{
						copperDrakeVec[i]->setStartFrameX(0);
					}
					IMAGEMANAGER->findImage("카파드레이크")->setFrameX(copperDrakeVec[i]->getStartFrameX());
				}
			}
			
			else if (copperDrakeVec[i]->getIsHit())									//카파드레이크가 공격당할때
			{
				copperDrakeVec[i]->setStartFrameX(1);
				copperDrakeVec[i]->setStartFrameY(3);
				IMAGEMANAGER->findImage("카파드레이크")->setFrameX(copperDrakeVec[i]->getStartFrameX());
				IMAGEMANAGER->findImage("카파드레이크")->setFrameY(copperDrakeVec[i]->getStartFrameY());
			}
			else if (copperDrakeVec[i]->getIsDie())									//카파드레이크가 죽을때
			{
				copperDrakeVec[i]->setStartFrameY(5);
				IMAGEMANAGER->findImage("카파드레이크")->setFrameY(5);
				if (copperDrakeVec[i]->_monsterCount % 10 == 0)
				{
					copperDrakeVec[i]->setStartFrameX(copperDrakeVec[i]->getStartFrameX() + 1);
					if (copperDrakeVec[i]->getStartFrameX() >5)
					{
						copperDrakeVec[i]->setStartFrameX(5);
						copperDrakeVec.erase(copperDrakeVec.begin() + i);
						_deadCount++;
						break;
					}
					IMAGEMANAGER->findImage("카파드레이크")->setFrameX(copperDrakeVec[i]->getStartFrameX());
				}
			}
			else															//카파드레이크가 가만히 있을때
			{
				copperDrakeVec[i]->setStartFrameX(0);
				copperDrakeVec[i]->setStartFrameY(3);
				IMAGEMANAGER->findImage("카파드레이크")->setFrameX(copperDrakeVec[i]->getStartFrameX());
				IMAGEMANAGER->findImage("카파드레이크")->setFrameY(copperDrakeVec[i]->getStartFrameY());
			}
		}
	}
	//주니어 발록
	if (_JuniorBalrog->isreal)
	{
		_JuniorBalrog->_monsterCount++;
		for (int i = 0; i < 2;i++)
		{
			_JuniorBalrog->_skill[i].count++;
		}
		if (_JuniorBalrog->getIsLeft())											//주니어발록이 왼쪽을 볼때
		{
			if (_JuniorBalrog->getIsMove() || _JuniorBalrog->getIsChase())			//주니어발록이 움직이거나 쫒아갈때
			{
				IMAGEMANAGER->findImage("주니어발록")->setFrameY(1);
				if (_JuniorBalrog->_monsterCount % 15 == 0)
				{
					_JuniorBalrog->setStartFrameX(_JuniorBalrog->getStartFrameX() + 1);
					if (_JuniorBalrog->getStartFrameX() > 4)
					{
						_JuniorBalrog->setStartFrameX(0);
					}
					IMAGEMANAGER->findImage("주니어발록")->setFrameX(_JuniorBalrog->getStartFrameX());
				}
			}
			else if (_JuniorBalrog->getIsDie())										//주니어발록이 죽을때
			{
				IMAGEMANAGER->findImage("주니어발록")->setFrameY(5);
				if (_JuniorBalrog->_monsterCount % 13 == 0)
				{
					_JuniorBalrog->setStartFrameX(_JuniorBalrog->getStartFrameX() + 1);
					if (_JuniorBalrog->getStartFrameX() > 3)
					{
						_JuniorBalrog->setStartFrameX(3);
						_JuniorBalrog->isreal = false;
						_deadCount = 0;
					}
					IMAGEMANAGER->findImage("주니어발록")->setFrameX(_JuniorBalrog->getStartFrameX());
				}
			}
			else if (_JuniorBalrog->getIsUsingSkill() && _JuniorBalrog->skillSelect == 0 )									//메테오스킬 사용 할때
			{
				_JuniorBalrog->_skill[0].skillEnd = false;
				IMAGEMANAGER->findImage("주니어발록")->setFrameY(2);
				if (_JuniorBalrog->_monsterCount % 6 == 0)
				{
					_JuniorBalrog->setStartFrameX(_JuniorBalrog->getStartFrameX() + 1);
					if (_JuniorBalrog->getStartFrameX() > 9)
					{
						_JuniorBalrog->setStartFrameX(0);
						_JuniorBalrog->setIsUsingSkill(false);
						_JuniorBalrog->setIsChase(true);
						_JuniorBalrog->_skill[0].frame = 0;
						_JuniorBalrog->_skill[0].skillEnd = true;
					}
				}
				IMAGEMANAGER->findImage("주니어발록")->setFrameX(_JuniorBalrog->getStartFrameX());
				IMAGEMANAGER->findImage("메테오")->setFrameY(0);
				if (_JuniorBalrog->_skill[0].count % 2 == 0 && _JuniorBalrog->getStartFrameX() > 5)
				{
					_JuniorBalrog->_skill[0].frame++;
				}
				if (_JuniorBalrog->_skill[0].frame > 6)
				{	
					_JuniorBalrog->coolDownTime = 400;
				}
				IMAGEMANAGER->findImage("메테오")->setFrameX(_JuniorBalrog->_skill[0].frame);
			}
			
			else if (_JuniorBalrog->getIsUsingSkill() && _JuniorBalrog->skillSelect == 1)											//매직클로스킬 사용 할때
			{
				_JuniorBalrog->_skill[1].skillEnd = false;
				IMAGEMANAGER->findImage("주니어발록")->setFrameY(4);
				if (_JuniorBalrog->_monsterCount % 6 == 0)
				{
					_JuniorBalrog->setStartFrameX(_JuniorBalrog->getStartFrameX() + 1);
					if (_JuniorBalrog->getStartFrameX() > 4)
					{
						_JuniorBalrog->setStartFrameX(0);
						_JuniorBalrog->setIsUsingSkill(false);
						_JuniorBalrog->setIsChase(true);
						_JuniorBalrog->_skill[1].frame = 0;
						_JuniorBalrog->_skill[1].skillEnd = true;
					}
					IMAGEMANAGER->findImage("주니어발록")->setFrameX(_JuniorBalrog->getStartFrameX());
				}
				IMAGEMANAGER->findImage("매직클로")->setFrameY(0);
				if (_JuniorBalrog->_skill[1].count % 2 == 0 && _JuniorBalrog->getStartFrameX() > 1)
				{
					_JuniorBalrog->_skill[1].frame++;
				}
				if (_JuniorBalrog->_skill[1].frame > 3)
				{
					_JuniorBalrog->coolDownTime = 400;
				}
				IMAGEMANAGER->findImage("매직클로")->setFrameX(_JuniorBalrog->_skill[1].frame);
			}
			else															//주니어발록이 가만히 있을때
			{
				IMAGEMANAGER->findImage("주니어발록")->setFrameX(0);
				IMAGEMANAGER->findImage("주니어발록")->setFrameY(0);
			}
		}
		else																			//주니어발록이 오른쪽을 볼때
		{
			if (_JuniorBalrog->getIsMove() || _JuniorBalrog->getIsChase())						//주니어발록이 움직이거나 쫒아갈때
			{
				IMAGEMANAGER->findImage("주니어발록")->setFrameY(7);
				if (_JuniorBalrog->_monsterCount % 15 == 0)
				{
					_JuniorBalrog->setStartFrameX(_JuniorBalrog->getStartFrameX() + 1);
					if (_JuniorBalrog->getStartFrameX() > 4)
					{
						_JuniorBalrog->setStartFrameX(0);
					}
					IMAGEMANAGER->findImage("주니어발록")->setFrameX(_JuniorBalrog->getStartFrameX());
				}
			}
			else if (_JuniorBalrog->getIsDie())													//주니어발록이 죽을때
			{
				IMAGEMANAGER->findImage("주니어발록")->setFrameY(11);
				if (_JuniorBalrog->_monsterCount % 13 == 0)
				{
					_JuniorBalrog->setStartFrameX(_JuniorBalrog->getStartFrameX() + 1);
					if (_JuniorBalrog->getStartFrameX() > 3)
					{
						_JuniorBalrog->setStartFrameX(3);
						_JuniorBalrog->isreal = false;
						_deadCount = 0;
					}
					IMAGEMANAGER->findImage("주니어발록")->setFrameX(_JuniorBalrog->getStartFrameX());
				}
			}
			else if (_JuniorBalrog->getIsUsingSkill() && _JuniorBalrog->skillSelect == 0)									//메테오스킬 사용 할때
			{
				_JuniorBalrog->_skill[0].skillEnd = false;
				IMAGEMANAGER->findImage("주니어발록")->setFrameY(2);
				if (_JuniorBalrog->_monsterCount % 6 == 0)
				{
					_JuniorBalrog->setStartFrameX(_JuniorBalrog->getStartFrameX() + 1);
					if (_JuniorBalrog->getStartFrameX() > 9)
					{
						_JuniorBalrog->setStartFrameX(0);
						_JuniorBalrog->setIsUsingSkill(false);
						_JuniorBalrog->setIsChase(true);
						_JuniorBalrog->_skill[0].frame = 0;
						_JuniorBalrog->_skill[0].skillEnd = true;
					}
				}
				IMAGEMANAGER->findImage("주니어발록")->setFrameX(_JuniorBalrog->getStartFrameX());
				IMAGEMANAGER->findImage("메테오")->setFrameY(0);
				if (_JuniorBalrog->_skill[0].count % 2 == 0 && _JuniorBalrog->getStartFrameX() > 5)
				{
					_JuniorBalrog->_skill[0].frame++;
				}
				if (_JuniorBalrog->_skill[0].frame > 6)
				{
					_JuniorBalrog->coolDownTime = 400;
				}
				IMAGEMANAGER->findImage("메테오")->setFrameX(_JuniorBalrog->_skill[0].frame);

			}
			else if (_JuniorBalrog->getIsUsingSkill() && _JuniorBalrog->skillSelect == 1 )											//매직클로스킬 사용 할때
			{
				_JuniorBalrog->_skill[1].skillEnd = false;
				IMAGEMANAGER->findImage("주니어발록")->setFrameY(10);
				if (_JuniorBalrog->_monsterCount % 6 == 0)
				{
					_JuniorBalrog->setStartFrameX(_JuniorBalrog->getStartFrameX() + 1);
					if (_JuniorBalrog->getStartFrameX() > 4)
					{
						_JuniorBalrog->setStartFrameX(0);
						_JuniorBalrog->setIsUsingSkill(false);
						_JuniorBalrog->setIsChase(true);
						_JuniorBalrog->_skill[1].frame = 0;
						_JuniorBalrog->_skill[1].skillEnd = true;
					}
					IMAGEMANAGER->findImage("주니어발록")->setFrameX(_JuniorBalrog->getStartFrameX());
				}
				IMAGEMANAGER->findImage("매직클로")->setFrameY(0);
				if (_JuniorBalrog->_skill[1].count % 2 == 0 && _JuniorBalrog->getStartFrameX() > 1)
				{
					_JuniorBalrog->_skill[1].frame++;
				}
				if (_JuniorBalrog->_skill[1].frame > 3)
				{
					_JuniorBalrog->coolDownTime = 400;
				}
				IMAGEMANAGER->findImage("매직클로")->setFrameX(_JuniorBalrog->_skill[1].frame);
			}
			else 																		//주니어발록이 가만히 있을때
			{
				IMAGEMANAGER->findImage("주니어발록")->setFrameX(0);
				IMAGEMANAGER->findImage("주니어발록")->setFrameY(6);
			}
			
		}
		
	}
}

void temple::monsterIntersect(void)
{
	RECT rcTemp;
	for (int i = 0; i < drakeVec.size(); i++)												//드레이크 표창충돌
	{
		if (!drakeVec[i]->getIsDie())
		{
			if (IntersectRect(&rcTemp, &PLAYER->_javelin1._rc, &drakeVec[i]->_monsterRect))
			{
				drakeVec[i]->setIsHit(true);
				drakeVec[i]->setMonsterHp(drakeVec[i]->getMonsterHp() - 50);
				if (drakeVec[i]->getMonsterHp() <= 0)
				{
					drakeVec[i]->setIsDie(true);
				}
				PLAYER->_javelin1._time = 0;
				PLAYER->_javelin1._usingJavelin = false;
				PLAYER->_isAttack = false;		  //공격 비활성화
				PLAYER->_javelin1._rc.left = 1920;
				PLAYER->_javelin1._rc.right = PLAYER->_javelin1._rc.left + 30;
				PLAYER->_javelin1._rc.top = 1080;
				PLAYER->_javelin1._rc.bottom = PLAYER->_javelin1._rc.top + 30;
			}
			if (IntersectRect(&rcTemp, &PLAYER->_javelin2._rc, &drakeVec[i]->_monsterRect))
			{
				drakeVec[i]->setIsHit(true);
				drakeVec[i]->setMonsterHp(drakeVec[i]->getMonsterHp() - 50);
				if (drakeVec[i]->getMonsterHp() <= 0)
				{
					drakeVec[i]->setIsDie(true);
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
			if (IntersectRect(&rcTemp, &SHURIKENBURST->_javelin.rc, &drakeVec[i]->_monsterRect))		//드레이크, 슈리켄버스트 표창 충돌처리
			{
				drakeVec[i]->setMonsterHp(drakeVec[i]->getMonsterHp() - SHURIKENBURST->getDamage());
				drakeVec[i]->setIsHit(true);														
				if (drakeVec[i]->getMonsterHp() <= 0)
				{
					drakeVec[i]->setIsDie(true);
				}
			}																						
			if (IntersectRect(&rcTemp, &WINDTALISMAN->_javelin.rc, &drakeVec[i]->_monsterRect))			//드레이크, 윈드 탈리스만 표창 충돌처리
			{
				drakeVec[i]->setMonsterHp(drakeVec[i]->getMonsterHp() - WINDTALISMAN->getDamage());
				drakeVec[i]->setIsHit(true);														
				if (drakeVec[i]->getMonsterHp() <= 0)
				{
					drakeVec[i]->setIsDie(true);
				}
			}
			if (IntersectRect(&rcTemp, &SHADESPLIT->_skillRange, &drakeVec[i]->_monsterRect))			//드레이크, 쉐이드스플릿 충돌처리
			{
				drakeVec[i]->setMonsterHp(drakeVec[i]->getMonsterHp() - SHADESPLIT->getDamage());
				drakeVec[i]->setIsHit(true);
				if (drakeVec[i]->getMonsterHp() <= 0)
				{
					drakeVec[i]->setIsDie(true);
				}
			}
		}
	}
	for (int i = 0; i < copperDrakeVec.size(); i++)												//카파드레이크 표창충돌
	{
		if (!copperDrakeVec[i]->getIsDie())
		{
			if (IntersectRect(&rcTemp, &PLAYER->_javelin1._rc, &copperDrakeVec[i]->_monsterRect))
			{
				copperDrakeVec[i]->setIsHit(true);
				copperDrakeVec[i]->setMonsterHp(copperDrakeVec[i]->getMonsterHp() - 50);
				if (copperDrakeVec[i]->getMonsterHp() <= 0)
				{
					copperDrakeVec[i]->setIsDie(true);
				}
				PLAYER->_javelin1._time = 0;
				PLAYER->_javelin1._usingJavelin = false;
				PLAYER->_isAttack = false;		  //공격 비활성화
				PLAYER->_javelin1._rc.left = 1920;
				PLAYER->_javelin1._rc.right = PLAYER->_javelin1._rc.left + 30;
				PLAYER->_javelin1._rc.top = 1080;
				PLAYER->_javelin1._rc.bottom = PLAYER->_javelin1._rc.top + 30;
			}
			if (IntersectRect(&rcTemp, &PLAYER->_javelin2._rc, &copperDrakeVec[i]->_monsterRect))
			{
				copperDrakeVec[i]->setIsHit(true);
				copperDrakeVec[i]->setMonsterHp(copperDrakeVec[i]->getMonsterHp() - 50);
				if (copperDrakeVec[i]->getMonsterHp() <= 0)
				{
					copperDrakeVec[i]->setIsDie(true);
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
			if (IntersectRect(&rcTemp, &SHURIKENBURST->_javelin.rc, &copperDrakeVec[i]->_monsterRect))				//카파드레이크, 슈리켄버스트 표창 충돌처리
			{
				copperDrakeVec[i]->setMonsterHp(copperDrakeVec[i]->getMonsterHp() - SHURIKENBURST->getDamage());
				copperDrakeVec[i]->setIsHit(true);
				if (copperDrakeVec[i]->getMonsterHp() <= 0)
				{
					copperDrakeVec[i]->setIsDie(true);															
				}
			}
			if (IntersectRect(&rcTemp, &WINDTALISMAN->_javelin.rc, &copperDrakeVec[i]->_monsterRect))				//카파드레이크, 윈드 탈리스만 표창 충돌처리
			{
				copperDrakeVec[i]->setMonsterHp(copperDrakeVec[i]->getMonsterHp() - WINDTALISMAN->getDamage());
				copperDrakeVec[i]->setIsHit(true);
				if (copperDrakeVec[i]->getMonsterHp() <= 0)
				{
					copperDrakeVec[i]->setIsDie(true);
				}
			}
			if (IntersectRect(&rcTemp, &SHADESPLIT->_skillRange, &copperDrakeVec[i]->_monsterRect))					//카파드레이크, 쉐이드스플릿 충돌처리
			{
				copperDrakeVec[i]->setMonsterHp(copperDrakeVec[i]->getMonsterHp() - SHADESPLIT->getDamage());
				copperDrakeVec[i]->setIsHit(true);
				if (copperDrakeVec[i]->getMonsterHp() <= 0)
				{
					copperDrakeVec[i]->setIsDie(true);
				}
			}
		}
	}
	if (_JuniorBalrog->isreal)																	//주니어발록 피격
	{
		if (!_JuniorBalrog->getIsDie())
		{
			if (IntersectRect(&rcTemp, &PLAYER->_javelin1._rc, &_JuniorBalrog->_monsterRect))
			{
				_JuniorBalrog->setIsHit(true);
				_JuniorBalrog->setMonsterHp(_JuniorBalrog->getMonsterHp() - 50);
				if (_JuniorBalrog->getMonsterHp() <= 0)
				{
					_JuniorBalrog->setIsDie(true);
				}
				PLAYER->_javelin1._time = 0;
				PLAYER->_javelin1._usingJavelin = false;
				PLAYER->_isAttack = false;		  //공격 비활성화
				PLAYER->_javelin1._rc.left = 1920;
				PLAYER->_javelin1._rc.right = PLAYER->_javelin1._rc.left + 30;
				PLAYER->_javelin1._rc.top = 1080;
				PLAYER->_javelin1._rc.bottom = PLAYER->_javelin1._rc.top + 30;
			}
			if (IntersectRect(&rcTemp, &PLAYER->_javelin2._rc, &_JuniorBalrog->_monsterRect))
			{
				_JuniorBalrog->setIsHit(true);
				bossHp.right--;
				if (bossHp.right- bossHp.left <= 0)
				{
					_JuniorBalrog->setIsDie(true);
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
			if (IntersectRect(&rcTemp, &SHURIKENBURST->_javelin.rc, &_JuniorBalrog->_monsterRect))
			{
				_JuniorBalrog->setIsHit(true);
				bossHp.right -= 2;
				if (bossHp.right - bossHp.left <= 0)
				{
					_JuniorBalrog->setIsDie(true);
				}
			}
			if (IntersectRect(&rcTemp, &WINDTALISMAN->_javelin.rc, &_JuniorBalrog->_monsterRect))
			{
				_JuniorBalrog->setIsHit(true);
				bossHp.right -= 4;
				if (bossHp.right - bossHp.left <= 0)
				{
					_JuniorBalrog->setIsDie(true);
				}
			}
			if (IntersectRect(&rcTemp, &SHADESPLIT->_skillRange, &_JuniorBalrog->_monsterRect))
			{
				_JuniorBalrog->setIsHit(true);
				bossHp.right -= 5;
				if (bossHp.right - bossHp.left <= 0)
				{
					_JuniorBalrog->setIsDie(true);
				}
			}
		}
	}
	for (int i = 0; i < drakeVec.size(); i++)											//드레이크와 플레이어 충돌처리
	{
		if (IntersectRect(&rcTemp, &PLAYER->_playerRect.rc, &drakeVec[i]->_monsterRect))
		{
			if (PLAYER->_playerRect.rc.left < drakeVec[i]->_monsterRect.right - 75 || PLAYER->_playerRect.rc.right < drakeVec[i]->_monsterRect.left + 75)
			{
				if (!PLAYER->_isHurt)
				{
					PLAYER->_playerRect.hp.left -= 10;
					PLAYER->_playerRect.hp.right -= 10;
					PLAYER->_isHit = true;
				}
			}
		}
		if (PLAYER->_isHit)
		{
			PLAYER->_playerRect.time += 0.03;
			if (PLAYER->_playerRect.rc.left > drakeVec[i]->_monsterRect.left)
			{
				PLAYER->_playerRect.rc.left += 1;
				PLAYER->_playerRect.rc.right += 1;

				PLAYER->_isHurt = true;
			}
			else if (PLAYER->_playerRect.rc.right < drakeVec[i]->_monsterRect.right)
			{
				PLAYER->_playerRect.rc.left -= 1;
				PLAYER->_playerRect.rc.right -= 1;
				PLAYER->_isHurt = true;
			}
			if (!PLAYER->_isJump)
			{
				PLAYER->_playerRect.rc.top = -(sinf(PI / 2) * 2 - PLAYER->_playerRect.time) + PLAYER->_playerRect.rc.top;
				PLAYER->_playerRect.rc.bottom = -(sinf(PI / 2) * 2 - PLAYER->_playerRect.time) + PLAYER->_playerRect.rc.bottom;
			}
		}
	}

	for (int i = 0; i < copperDrakeVec.size(); i++)											//카파드레이크와 플레이어 충돌처리
	{
		if (IntersectRect(&rcTemp, &PLAYER->_playerRect.rc, &copperDrakeVec[i]->_monsterRect))
		{
			if (PLAYER->_playerRect.rc.left < copperDrakeVec[i]->_monsterRect.right - 75 || PLAYER->_playerRect.rc.right < copperDrakeVec[i]->_monsterRect.left + 75)
			{
				if (!PLAYER->_isHurt)
				{
					PLAYER->_playerRect.hp.left -= 15;
					PLAYER->_playerRect.hp.right -= 15;
					PLAYER->_isHit = true;
				}
			}
		}
		if (PLAYER->_isHit)
		{
			PLAYER->_playerRect.time += 0.03;

			if (PLAYER->_playerRect.rc.left > copperDrakeVec[i]->_monsterRect.left)
			{
				PLAYER->_playerRect.rc.left += 1;
				PLAYER->_playerRect.rc.right += 1;

				PLAYER->_isHurt = true;
			}
			else if (PLAYER->_playerRect.rc.right < copperDrakeVec[i]->_monsterRect.right)
			{
				PLAYER->_playerRect.rc.left -= 1;
				PLAYER->_playerRect.rc.right -= 1;
				PLAYER->_isHurt = true;
			}
			if (!PLAYER->_isJump)
			{
				PLAYER->_playerRect.rc.top = -(sinf(PI / 2) * 2 - PLAYER->_playerRect.time) + PLAYER->_playerRect.rc.top;
				PLAYER->_playerRect.rc.bottom = -(sinf(PI / 2) * 2 - PLAYER->_playerRect.time) + PLAYER->_playerRect.rc.bottom;
			}
		}
	}
	if (_JuniorBalrog->isreal)
	{
		if (IntersectRect(&rcTemp, &PLAYER->_playerRect.rc, &_JuniorBalrog->_monsterRect))
		{
			if ((PLAYER->_playerRect.rc.left < _JuniorBalrog->_monsterRect.right - 150 && PLAYER->_playerRect.rc.right > _JuniorBalrog->_monsterRect.right - 150) ||
				(PLAYER->_playerRect.rc.right > _JuniorBalrog->_monsterRect.left + 150 && PLAYER->_playerRect.rc.left < _JuniorBalrog->_monsterRect.left + 150))
			{
				if (!PLAYER->_isHurt)
				{
					PLAYER->_playerRect.hp.left -= 15;
					PLAYER->_playerRect.hp.right -= 15;
					PLAYER->_isHit = true;
				}
			}
		}
		if (PLAYER->_isHit)
		{
			PLAYER->_playerRect.time += 0.03;
			if (PLAYER->_playerRect.rc.left > _JuniorBalrog->_monsterRect.left)
			{
				PLAYER->_playerRect.rc.left += 1;
				PLAYER->_playerRect.rc.right += 1;

				PLAYER->_isHurt = true;
			}
			else if (PLAYER->_playerRect.rc.right < _JuniorBalrog->_monsterRect.right)
			{
				PLAYER->_playerRect.rc.left -= 1;
				PLAYER->_playerRect.rc.right -= 1;
				PLAYER->_isHurt = true;
			}
			if (!PLAYER->_isJump)
			{
				PLAYER->_playerRect.rc.top = -(sinf(PI / 2) * 2 - PLAYER->_playerRect.time) + PLAYER->_playerRect.rc.top;
				PLAYER->_playerRect.rc.bottom = -(sinf(PI / 2) * 2 - PLAYER->_playerRect.time) + PLAYER->_playerRect.rc.bottom;
			}
		}
	}
	if (IntersectRect(&rcTemp, &PLAYER->_playerRect.rc, &_JuniorBalrog->_skill[0].rc))
	{
		if (!PLAYER->_isHurt)
		{
			PLAYER->_playerRect.hp.left -= 3;
			PLAYER->_playerRect.hp.right -= 3;
			PLAYER->_isHit = true;
		}
	}
	else if (IntersectRect(&rcTemp, &PLAYER->_playerRect.rc, &_JuniorBalrog->_skill[1].rc))
	{
		if (!PLAYER->_isHurt)
		{
			PLAYER->_playerRect.hp.left -= 2;
			PLAYER->_playerRect.hp.right -= 2;
			PLAYER->_isHit = true;
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
		PLAYER->_isHit = false;
		PLAYER->_safeTime--;
		if (PLAYER->_safeTime < 0)
		{
			PLAYER->_isHurt = false;
			PLAYER->_safeTime = 100;
		}
	}
}
