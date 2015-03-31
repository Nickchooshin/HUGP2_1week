#pragma once

#include "Singleton.h"
#include <map>
#include <string>

class CBoss ;

class BossManager : public Singleton<BossManager>
{
private :
	std::map<std::string, CBoss*> m_BossList ;

public :
	BossManager() ;
	~BossManager() ;

	void SetupBoss(char *strBossName) ;

	void Render() ;
} ;

#define g_BossManager BossManager::GetInstance()