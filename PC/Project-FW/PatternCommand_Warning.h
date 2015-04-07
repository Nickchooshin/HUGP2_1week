#pragma once

#include "PatternCommand.h"
#include "Position.h"
#include <string>

class CPatternCommand_Warning : public CPatternCommand
{
private :
	char m_axis ;
	float m_fWidth, m_fHeight ;
	POSITION m_startPosition ;
	float m_fStayTime ;

public :
	CPatternCommand_Warning(float width, float height, POSITION stayPosition, float stayTime) ;
	CPatternCommand_Warning(char axis, float width, float height, float stayAxis, float stayTime) ;
	CPatternCommand_Warning(float width, float height, float stayAxis, float stayTime) ;
	~CPatternCommand_Warning() ;

	void Update() ;
} ;