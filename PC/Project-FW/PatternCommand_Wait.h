#pragma once

#include "PatternCommand.h"

class CPatternCommand_Wait : public CPatternCommand
{
private :
	float m_fTime, m_fDelayTime ;

public :
	CPatternCommand_Wait(float delayTime) ;
	~CPatternCommand_Wait() ;

	void Update() ;
} ;