#include "stdafx.h"
#include "shurikenBurst.h"

HRESULT shurikenBurst::init()
{
	_skillRange = RectMake(-100, -200, 373, 195);
	_skillCount = 0;
	_javelin.startLeft = 0;
	_javelin.startRight = 2;
	_javelin.count = 0;
	setStartLeft(0);
	setStartRight(6);
	setDamage(RND->getFromIntTo(PLAYER->getDamage() * 2, PLAYER->getDamage() * 3));
	setMana(0);
	setIsPossible(true);
	setIsUsing(false);
	return S_OK;
}

void shurikenBurst::usingSkill(void)
{
	if (!getIsUsing())
	{
		setStartLeft(0);
		setStartRight(6);
		_javelin.startLeft = 0;
		_javelin.startRight = 2;
	}
	if (getIsPossible())
	{
		PLAYER->setCurrentMp(PLAYER->getCurrentMp() - getMana());
		setIsUsing(true);
	}
	if (PLAYER->_isLeft)
	{
		_skillRange.right = PLAYER->_playerRect.rc.right + 100;
		_skillRange.left = _skillRange.right - 373;
		_skillRange.top = PLAYER->_playerRect.rc.bottom - 125;
		_skillRange.bottom = _skillRange.top + 195;
	}
	else
	{
		_skillRange.left = PLAYER->_playerRect.rc.left - 100;
		_skillRange.right = _skillRange.left + 373;
		_skillRange.top = PLAYER->_playerRect.rc.bottom - 125;
		_skillRange.bottom = _skillRange.top + 195;
	}
}

void shurikenBurst::possibleSkill(void)
{
	if (PLAYER->_playerRect.mp.left < WINSIZEX / 2 - 250)
	{
		setIsPossible(false);
	}
	else
	{
		setIsPossible(true);
	}
}