#include "stdafx.h"
#include "JuniorBalrog.h"


JuniorBalrog::JuniorBalrog()
{
	random = RND->getInt(2);
	setStartFrameX(0);
	setMonsterHp(100000000);
	setMonsterAttack(50);
	setDistance(RND->getInt(800));
	setRelax(300);
	hitTime = getRelax() / 15;
	skillSelect = 1;
	isreal = false;
	setIsHit(false);
	setIsMove(true);
	setIsLeft(false);
	setIsDie(false);
	setIsChase(false);
	setIsUsingSkill(false);
	_monsterRect = RectMake(RND->getFromIntTo(0, WINSIZEX), 809, 533, 231);
	for (int i = 0;i < 2;i++)
	{
		_skill[i].count = 0;
		_skill[i].frame = 0;
		_skill[i].skillUse = false;			//��ų ���
		_skill[i].skillEnd = true;			//��ų ��Ÿ�� ����
	}
	coolDownTime = 400;
	_skill[0].rc = RectMake(1920, 1080, 163, 133);
	_skill[1].rc = RectMake(1920, 1080, 87, 99);
}


JuniorBalrog::~JuniorBalrog()
{

}



void JuniorBalrog::monsterMove(void)
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

void JuniorBalrog::usingSkill(void)
{
	setIsMove(false);
	setIsChase(false);
	setIsHit(false);
	
	if (PLAYER->_playerRect.rc.left > _monsterRect.left && PLAYER->_playerRect.rc.right < _monsterRect.right )
	{
		if (coolDownTime <= 0 && skillSelect == 0)
		{
			setIsUsingSkill(true);
			if (getStartFrameX() > 5)
			{
				_skill[skillSelect].rc.left = PLAYER->_playerRect.rc.left;
				_skill[skillSelect].rc.right = _skill[skillSelect].rc.left + 163;
				_skill[skillSelect].rc.top = PLAYER->_playerRect.rc.top - 50;
				_skill[skillSelect].rc.bottom = _skill[skillSelect].rc.bottom + 133;
			}
		}
		if (coolDownTime <= 0 && skillSelect == 1)
		{
			setIsUsingSkill(true);
			if (getStartFrameX() > 0)
			{
				_skill[skillSelect].rc.left = PLAYER->_playerRect.rc.left;
				_skill[skillSelect].rc.right = _skill[skillSelect].rc.left + 74;
				_skill[skillSelect].rc.top = PLAYER->_playerRect.rc.top;
				_skill[skillSelect].rc.bottom = _skill[skillSelect].rc.bottom + 122;
			}
		}
	}

	
}

