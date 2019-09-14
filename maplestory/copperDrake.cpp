#include "stdafx.h"
#include "copperDrake.h"


copperDrake::copperDrake()
{
	random = RND->getInt(2);
	setStartFrameX(0);
	setMonsterHp(700);
	setMonsterAttack(60);
	setDistance(RND->getInt(800));
	setRelax(300);
	hitTime = getRelax() / 15;
	setIsHit(false);
	setIsMove(true);
	setIsLeft(true);
	setIsDie(false);
	setIsChase(false);
	_monsterRect = RectMake(RND->getFromIntTo(0, 1500), 906, 221, 104);
}


copperDrake::~copperDrake()
{
}

void copperDrake::monsterMove(void)
{
	if (getIsMove())
	{
		if (getIsLeft())
		{
			_monsterRect.left--;
			_monsterRect.right--;
		}
		else
		{
			_monsterRect.left++;
			_monsterRect.right++;
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
			if (random % 2 == 0)								//�������� ¦���϶�
			{
				setIsLeft(true);								//�������� �̵�
				random = RND->getInt(2);
			}
			else if (random % 2 == 1)							//Ȧ���̰ų� ���� �����϶�
			{
				setIsLeft(false);								//���������� �̵�
				random = RND->getInt(2);
			}
			setIsMove(true);									//�����δ�
			setRelax(RND->getInt(500));							//�޽Ľð� �缳��
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
