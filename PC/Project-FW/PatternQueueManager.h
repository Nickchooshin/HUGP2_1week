#pragma once

#include "Singleton.h"
#include "DataLoader.h"
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

	void Clear() ;

	void Update() ;
private :
	void CommandWait(CDataLoader &DataLoader) ;
	void CommandMove(CDataLoader &DataLoader) ;
	void CommandDrop(CDataLoader &DataLoader) ;
	void CommandStay(CDataLoader &DataLoader) ;
	void CommandSound(CDataLoader &DataLoader) ;
	void CommandShake(CDataLoader &DataLoader) ;
	void CommandWarning(CDataLoader &DataLoader) ;
	void CommandIrregular(CDataLoader &DataLoader) ;
} ;

#define g_PatternQueueManager CPatternQueueManager::GetInstance()