#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	_level = 50;
	_maxHp = 500;
	_currnetHp = _maxHp;
	_maxMp =  300;
	_currentMp = _maxMp;
	_damage = RND->getFromIntTo(30, 50);
	_moveCount = 0;
	_jumpCount = 0;
	_safeTime = 100;
	_isLeft = true;
	_isLie = false;
	_isJump = false;
	_isAttack = false;
	_isHit = false;
	_isMove = false;
	_isRopeUsing = false;
	_isLadderUsing = false;
	_isUsingSkill = false;
	_isPlayerMoveMap = true;
	_isHurt = false;
	_isClimbing = false;
	_isDownClimbing = false;
	_isDownJump = false;
	_javelin1._time = 0;
	_javelin1._frame = 0;
	_javelin1._usingJavelin = false;
	_javelin1._angle = PI / 2;
	_javelin2._time = 0;
	_javelin2._frame = 0;
	_javelin2._usingJavelin = false;
	_javelin2._angle = PI / 2;
	_playerRect.rc = RectMake(WINSIZEX - 79, WINSIZEY/2, 79, 85);
	_playerRect.hp = RectMake(WINSIZEX / 2 - 256, WINSIZEY - 19, 107, 16);											//체력 사각형
	_playerRect.mp = RectMake(WINSIZEX / 2 - 148, WINSIZEY - 19, 107, 16);											//마나 사각형
	_playerRect.time = 0;
	_playerRect.angle = PI/2;
	_playerRect.moveFrame = 0;
	_playerRect.attackFrame = 0;
	_playerRect.climbFrame = 0;
	_playerRect.luckySevenFrame = 0;
	_playerRect.surikenFrame = 0;
	_playerRect.windFrame = 0;
	_attack = 2;

	
	return S_OK;
}

void player::playerLevelUp(void)
{
	this->setLevel(this->getLevel() + 1);
	this->setMaxHp(this->getMaxHp() + _level * 5);
	this->setCurrentHp(this->getMaxHp());
	this->setMaxMp(this->getMaxMp() + _level * 3);
	this->setCurrentMp(this->getMaxMp());
}

void player::playerJump(void)
{	
	//_playerRect.time += 0.03;
	if (_jumpCount > 1)					//플래시 점프를 사용할때
	{
		if (_isLeft)
		{
			_playerRect.rc.left -= 7;
			_playerRect.rc.right -= 7;
		}
		else
		{
			_playerRect.rc.left += 7;
			_playerRect.rc.right += 7;
		}
		_playerRect.rc.bottom = -(sinf(_playerRect.angle) *11 - (GRAVITY*_playerRect.time)) + _playerRect.rc.bottom;
		_playerRect.rc.top = -(sinf(_playerRect.angle) * 11 - (GRAVITY*_playerRect.time)) + _playerRect.rc.top;
	}
	else if(_jumpCount < 2 && _jumpCount >= 0)
	{
		_playerRect.rc.bottom = -(sinf(_playerRect.angle) * 15.5 - (GRAVITY*_playerRect.time)) + _playerRect.rc.bottom;
		_playerRect.rc.top = -(sinf(_playerRect.angle) * 15.5 - (GRAVITY*_playerRect.time)) + _playerRect.rc.top;
	}
	else if (_jumpCount < 0)
	{
		_playerRect.rc.bottom = -(sinf(_playerRect.angle) * 8 - (GRAVITY*_playerRect.time)) + _playerRect.rc.bottom;
		_playerRect.rc.top = -(sinf(_playerRect.angle) * 8 - (GRAVITY*_playerRect.time)) + _playerRect.rc.top;
	}

}


void player::flashJump(void)
{
	_playerRect.time = 0;
	this->playerJump();
}

float player::getAngle(float x1, float y1, float x2, float y2)
{
	float x = x2 - x1;
	float y = y2 - y1;
	float d = sqrtf(x * x + y * y);
	float angle = acos(x / d);

	if (y > 0) angle = PI * 2 - angle;

	return angle;
}

float player::getDistance(float x1, float y1, float x2, float y2)
{
	float x = x2 - x1;
	float y = y2 - y1;

	return sqrtf(x * x + y * y);
}