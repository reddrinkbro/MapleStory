#include "stdafx.h"
#include "shadeSplit.h"


HRESULT shadeSplit::init()
{
	_skillRange = RectMake(1920, 1080, 656, 381);
	_skillCount = 0;
	setStartLeft(0);
	setStartRight(9);
	setDamage(RND->getFromFloatTo(PLAYER->getDamage() * 5, PLAYER->getDamage() * 6));
	setMana(0);
	setIsPossible(true);
	setIsUsing(false);
	return S_OK;
}

void shadeSplit::usingSkill(void)
{
	if (!getIsUsing())
	{
		setStartLeft(0);
		setStartRight(9);
	}
	if (getIsPossible())
	{
		PLAYER->setCurrentMp(PLAYER->getCurrentMp() - getMana());
		setIsUsing(true);
	}
	if (PLAYER->_isLeft)
	{
		_skillRange.left = PLAYER->_playerRect.rc.right - 626;
		_skillRange.right = _skillRange.left + 656;
		_skillRange.top = PLAYER->_playerRect.rc.bottom - 266;
		_skillRange.bottom =_skillRange.top + 381;
	}
	else
	{
		_skillRange.left = PLAYER->_playerRect.rc.left;
		_skillRange.right = _skillRange.left + 656;
		_skillRange.top = PLAYER->_playerRect.rc.bottom - 266;
		_skillRange.bottom = _skillRange.top + 381;
	}
}

void shadeSplit::possibleSkill(void)
{
	if (PLAYER->_playerRect.mp.left < WINSIZEX / 2 - 225)
	{
		setIsPossible(false);
	}
	else
	{
		setIsPossible(true);
	}
	
}
