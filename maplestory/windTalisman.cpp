#include "stdafx.h"
#include "windTalisman.h"

HRESULT windTalisman::init()
{
	_skillRange = RectMake(-100, -300, 327, 211);
	_skillCount = 0;
	_javelin.startLeft = 0;
	_javelin.startRight = 2;
	_javelin.count = 0;
	setStartLeft(0);
	setStartRight(9);
	setDamage(RND->getFromIntTo(PLAYER->getDamage() * 3, PLAYER->getDamage() * 4));
	setMana(0);
	setIsPossible(true);
	setIsUsing(false);
	return S_OK;
}

void windTalisman::usingSkill(void)
{
	if (!getIsUsing())
	{
		setStartLeft(0);
		setStartRight(9);
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
		_skillRange.left = PLAYER->_playerRect.rc.right - 327;
		_skillRange.right = _skillRange.left + 327;
		_skillRange.top = PLAYER->_playerRect.rc.bottom - 181;
		_skillRange.bottom =_skillRange.top + 211;
	}
	else
	{
		_skillRange.left = PLAYER->_playerRect.rc.left;
		_skillRange.right =_skillRange.left + 327;
		_skillRange.top = PLAYER->_playerRect.rc.bottom - 181;
		_skillRange.bottom = _skillRange.top + 211;
	}
}

void windTalisman::possibleSkill(void)
{
	if (PLAYER->_playerRect.mp.left <= WINSIZEX / 2 - 245)
	{
		setIsPossible(false);
	}
	else
	{
		setIsPossible(true);
	}
}