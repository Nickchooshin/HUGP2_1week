#pragma once

#include "Singleton.h"
#include <queue>

class CPatternCommand ;

class CPatternQueueManager : public Singleton<CPatternQueueManager>
{
private :
	std::queue<CPatternCommand*> m_CommandQueue ;
	CPatternCommand *m_pNowCommand ;
	bool m_bQueueEnd ;

public :
	CPatternQueueManager() ;
	~CPatternQueueManager() ;

	bool LoadScript(char *filename) ;

	const bool BeQueueEnd() const ;

	void ClearQueue() ;

	void Update() ;
} ;

#define g_PatternQueueManager CPatternQueueManager::GetInstance()