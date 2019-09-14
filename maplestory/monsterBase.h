#pragma once
class monsterBase
{
private:
	int _monsterHp;			//몬스터 체력
	int _monsterAtk;		//몬스터 공격력
	int _startFrameX;		//몬스터 X프레임 시작
	int _startFrameY;		//몬스터 Y프레임 시작
	int _distance;			//몬스터가 이동한거리
	int _relax;				//몬스터 휴식시간
	bool _isHit;			//몬스터가 피해를 입었는지 확인
	bool _isLeft;			//몬스터 보는방향
	bool _isMove;			//몬스터가 움직이는지
	bool _isChase;			//플레이어를 쫒는지
	bool _isDie;			//몬스터가 죽었는지
public:
	RECT _monsterRect;		//몬스터 사각형
	int _monsterCount;		//몬스터 카운트
	int getMonsterHp() { return _monsterHp; }
	void setMonsterHp(int monsterHp) { _monsterHp = monsterHp; }
	int getMonsterAttack() { return _monsterAtk; }
	void setMonsterAttack(int monsterAtk) { _monsterAtk = monsterAtk; }
	int getStartFrameX() { return _startFrameX; }
	void setStartFrameX(int startFrameX) { _startFrameX = startFrameX; }
	int getStartFrameY() { return _startFrameY; }
	void setStartFrameY(int startFrameY) { _startFrameY = startFrameY; }
	int getDistance() { return _distance; }
	void setDistance(int distance) { _distance = distance; }
	int getRelax() { return _relax; }
	void setRelax(int relax) { _relax = relax; }
	bool getIsHit() { return _isHit; }
	void setIsHit(bool isHit) { _isHit = isHit; }
	bool getIsLeft() { return _isLeft; }
	void setIsLeft(bool isLeft) { _isLeft = isLeft; }
	bool getIsMove() { return _isMove; }
	void setIsMove(bool isMove) { _isMove = isMove; }
	bool getIsChase() { return _isChase; }
	void setIsChase(bool isChase) { _isChase = isChase; }
	bool getIsDie() { return _isDie; }
	void setIsDie(bool isDie) { _isDie = isDie; }

	virtual void monsterMove(void);				//몬스터 이동함수
	monsterBase();
	~monsterBase();
};

