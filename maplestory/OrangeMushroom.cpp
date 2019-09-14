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
		if (getDistance() < 0)									//�̵��Ÿ��� 0���� �ǰų� ���� �������� �������
		{
			setIsMove(false);									//������ ����
			setDistance(RND->getInt(800));						//�̵��Ÿ� �缳��
		}
	}
	else
	{
		setRelax(getRelax() - 1);								//�޽Ľð� ����
		if (getRelax() < 0)										//�޽��� ������
		{
			if (getIsLeft())									//�����̾�����
			{
				setIsLeft(false);								//���������� �̵�
			}
			else												//�������̾�����
			{
				setIsLeft(true);								//���������̵�
			}
			jumpCount = 1;
			setIsMove(true);									//�����δ�
			setRelax(300);										//�޽Ľð� �缳��
		}
	}
	if (getIsHit())													//�¾�����
	{
		setIsMove(false);
		if (PLAYER->_playerRect.rc.left > _monsterRect.left)		//�÷��̾ �����ʿ� �ִٸ�
		{
			_monsterRect.left--;
			_monsterRect.right--;
			setIsLeft(false);										//�������� ����
		}
		else if (PLAYER->_playerRect.rc.right < _monsterRect.right)	//�÷��̾ ���ʿ� �ִٸ�
		{
			_monsterRect.left++;
			_monsterRect.right++;
			setIsLeft(true);										//�������� ����
		}
		setIsChase(false);
		setRelax(getRelax() - hitTime);
		if (getRelax() < 0)
		{
			setIsHit(false);
			setIsChase(true);										//�÷��̾ �i�´�
		}
	}
	if (getIsChase())
	{
		setRelax(300);
		if (PLAYER->_playerRect.rc.left > _monsterRect.left)		//�÷��̾ �����ʿ� �ִٸ�
		{
			_monsterRect.left++;
			_monsterRect.right++;
			setIsLeft(false);
		}
		else if (PLAYER->_playerRect.rc.right < _monsterRect.right)	//�÷��̾ ���ʿ� �ִٸ�
		{
			_monsterRect.left--;
			_monsterRect.right--;
			setIsLeft(true);
		}
		if (getIsHit())
		{
			if (PLAYER->_playerRect.rc.left > _monsterRect.left)		//�÷��̾ �����ʿ� �ִٸ�
			{
				_monsterRect.left -= 2;
				_monsterRect.right -= 2;
			}
			else if (PLAYER->_playerRect.rc.right < _monsterRect.right)	//�÷��̾ ���ʿ� �ִٸ�
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