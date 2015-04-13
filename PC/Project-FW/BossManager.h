#pragma once

#include "Singleton.h"
#include <map>
#include <vector>
#include <queue>
#include <string>

class CBoss ;
class CPattern ;

class BossManager : public Singleton<BossManager>
{
private :
	std::map<std::string, CBoss*> m_BossList ;
	std::vector<CPattern*> m_PatternList ;

public :
	BossManager() ;
	~BossManager() ;

	void SetupBoss(char *strBossName) ;
	void AddPattern(CPattern *pPattern) ;

	CBoss* GetBossInstance(std::string name) ;

	void Update() ;

	void Render() ;
private :
	void ClearBoss() ;
	void ClearPattern() ;
} ;

#define g_BossManager BossManager::GetInstance()