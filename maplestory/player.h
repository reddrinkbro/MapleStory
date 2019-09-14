#pragma once
#include "singletonBase.h"

struct playerRect
{
	RECT rc;
	RECT hp;
	RECT mp;
	RECT exp;
	float angle;
	int moveFrame;					//움직일떄 사용하는 프레임
	int attackFrame;				//공격할때 사용하는 프레임
	int climbFrame;					//기어오를때 사용하는 프레임
	int luckySevenFrame;			//럭키세븐사용할때 사용하는 프레임
	int surikenFrame;				//슈리켄버스트 사용할때 사용하는 프레임
	int windFrame;					//윈드탈리스만 사용할때 사용하는 프레임
	float time;						// 점프하는 시간
};
struct javelin
{
	RECT _rc;
	float _angle;					// 표창 각도
	int _frame;						// 표창 프레임
	float _time;					// 표창 유지되는 시간
	bool _usingJavelin;				// 표창 사용하는지 확인
};
class player : public singletonBase<player>
{
private:
	int _currnetHp;		//현재 체력
	int _maxHp;			//최대 체력
	int _currentMp;		//현재 마나
	int _maxMp;			//최대 마나
	int _damage;		//데미지
	int _level;			//플레이어 레벨
public:
	HRESULT init();
	playerRect _playerRect;			// 플레이어 구조체
	javelin _javelin1;				// 표창구조체
	javelin _javelin2;				// 표창구조체
	int _attack;					// 플레이어 어택 프레임 선택
	int _count; 					// 프레임 카운트
	int _moveCount;					// 맵이동시 확인할 변수 (높은 맵 키값에서 낮은 키값으로 이동할때 -1, 낮은키값에서 높은 키값으로 이동할때 1, 맵이동후 0으로 초기화)
	int _jumpCount;					// 플래시 점프 사용하기 위한 변수
	int _safeTime;					// 공격당하고 무적시간
	bool _isLeft; 					// 플레이어 좌우 상태 확인
	bool _isLie; 					// 플레이어가 엎드렸는지 확인
	bool _isJump; 					// 플레이어 점프상태 확인
	bool _isAttack;					// 플레이어 공격상태 확인
	bool _isHit; 					// 플레이어 피격상태 확인
	bool _isMove; 					// 플레이어 움직임 상태 확인
	bool _isRopeUsing;				// 플레이어 로프를 사용중인지 확인
	bool _isLadderUsing;			// 플레이어 사다리 사용중인지 확인
	bool _isUsingSkill;				// 플레이어 스킬사용상태
	bool _isPlayerMoveMap;			// 플레이어 맵 이동 확인
	bool _isHurt;					// 플레이어가 공격 당했는지
	bool _isClimbing;				// 플레이어가 사다리나 로프에 있는지 확인
	bool _isDownClimbing;			// 플레이어가 사다리나 로프에 있는지 확인
	bool _isDownJump;				// 플레이어가 밑으로 사다리나 로프를 사용하는지 확인
	int getCurrentHp() { return _currnetHp; }
	void setCurrentHp(int currnetHp) { _currnetHp = currnetHp; }	// 현재 체력 Get Set
	int getMaxHp() { return _maxHp; }
	void setMaxHp(int maxHp) { _maxHp = maxHp; }					// 최대 체력 Get Set
	int getCurrentMp() { return _currentMp; }
	void setCurrentMp(int currnetMp) { _currentMp = currnetMp;}		// 현재 마나 Get Set
	int getMaxMp() { return _maxMp; }
	void setMaxMp(int maxMp) { _maxMp = maxMp; }					// 최대 마나 Get Set
	int getDamage() { return _damage; }
	void setDamage(int damage) { _damage = damage; }				// 데미지 Get Set
	int getLevel() { return _level; }
	void setLevel(int level) { _level = level; }					// 현재 레벨 Get Set
	
	void playerLevelUp(void);										// 플레이어 레벨업
	void playerJump(void);											//플레이어 점프
	float getAngle(float x1, float y1, float x2, float y2);			//각도 계산
	float getDistance(float x1, float y1, float x2, float y2);		//거리계산
	void flashJump(void);											//플레이어 플래시점프

	player(){}
	~player(){}
	
};

