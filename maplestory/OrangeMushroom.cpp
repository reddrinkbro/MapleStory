#include "stdafx.h"
#include "OrangeMushroom.h"

OrangeMushroom::OrangeMushroom()
{
	random = RND->getInt(2);
	angle = PI / 2;
	jumpCount = 1;
	setTime(0);
	setIsJump(false);
	setStartFrameX(0);
	setMonsterHp(120);
	setMonsterAttack(20);
	setDistance(RND->getInt(800));
	setRelax(300);
	hitTime = getRelax() / 15;
	setIsHit(false);
	setIsMove(true);
	setIsLeft(true);
	setIsDie(false);
	setIsChase(false);
	_monsterRect = RectMake(RND->getFromIntTo(0, 1500), 978, 69, 72);
}


OrangeMushroom::~OrangeMushroom()
{
}


void OrangeMushroom::monsterMove(void)
{
	if (getIsMove())
	{
		if (getIsLeft())
		{
			_monsterRect.left--;
			_monsterRect.right--;
			if (getDistance() < 150 && jumpCount == 1)
			{
				setIsJump(true);
			}
		}
		else
		{
			_monsterRect.left++;
			_monsterRect.right++;
			if (getDistance() < 150 && jumpCount == 1)
			{
				setIsJump(true);
			}
		}
		setDistance(getDistance() - 1);
		if (getDistance() < 0)									//이동거리가 0으로 되거나 제일 왼쪽으로 갔을경우
		{
			setIsMove(false);									//움직임 멈춤
			setDistance(RND->getInt(800));						//이동거리 재설정
		}
	}
	else
	{
		setRelax(getRelax() - 1);								//휴식시간 감소
		if (getRelax() < 0)										//휴식이 끝나면
		{
			if (getIsLeft())									//왼쪽이었으면
			{
				setIsLeft(false);								//오른쪽으로 이동
			}
			else												//오른쪽이었으면
			{
				setIsLeft(true);								//왼쪽으로이동
			}
			jumpCount = 1;
			setIsMove(true);									//움직인다
			setRelax(300);										//휴식시간 재설정
		}
	}
	if (getIsHit())													//맞았을때
	{
		setIsMove(false);
		if (PLAYER->_playerRect.rc.left > _monsterRect.left)		//플레이어가 오른쪽에 있다면
		{
			_monsterRect.left--;
			_monsterRect.right--;
			setIsLeft(false);										//오른쪽을 본다
		}
		else if (PLAYER->_playerRect.rc.right < _monsterRect.right)	//플레이어가 왼쪽에 있다면
		{
			_monsterRect.left++;
			_monsterRect.right++;
			setIsLeft(true);										//오른쪽을 본다
		}
		setIsChase(false);
		setRelax(getRelax() - hitTime);
		if (getRelax() < 0)
		{
			setIsHit(false);
			setIsChase(true);										//플레이어를 쫒는다
		}
	}
	if (getIsChase())
	{
		setRelax(300);
		if (PLAYER->_playerRect.rc.left > _monsterRect.left)		//플레이어가 오른쪽에 있다면
		{
			_monsterRect.left++;
			_monsterRect.right++;
			setIsLeft(false);
		}
		else if (PLAYER->_playerRect.rc.right < _monsterRect.right)	//플레이어가 왼쪽에 있다면
		{
			_monsterRect.left--;
			_monsterRect.right--;
			setIsLeft(true);
		}
		if (getIsHit())
		{
			if (PLAYER->_playerRect.rc.left > _monsterRect.left)		//플레이어가 오른쪽에 있다면
			{
				_monsterRect.left -= 2;
				_monsterRect.right -= 2;
			}
			else if (PLAYER->_playerRect.rc.right < _monsterRect.right)	//플레이어가 왼쪽에 있다면
			{
				_monsterRect.left += 2;
				_monsterRect.right += 2;
			}
		}
	}
	if (getIsDie())
	{
		setIsMove(false);
		setIsChase(false);
		setIsHit(false);
	}
}

void OrangeMushroom::jump()
{
	_monsterRect.top = -(sinf(angle) * 15.8 - (GRAVITY*getTime())) + _monsterRect.top;
	_monsterRect.bottom = -(sinf(angle) * 15.8 - (GRAVITY*getTime())) + _monsterRect.bottom;
	jumpCount--;
}