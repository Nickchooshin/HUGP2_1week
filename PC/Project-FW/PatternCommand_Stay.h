#pragma once

#include "PatternCommand.h"
#include "Position.h"
#include <string>

class CPatternCommand_Stay : public CPatternCommand
{
private :
	std::string m_strName ;
	POSITION m_stayPosition ;
	float m_fTime, m_fStayTime ;

public :
	CPatternCommand_Stay(std::string strName, POSITION stayPosition, float stayTime) ;
	virtual ~CPatternCommand_Stay() ;

	void Update() ;
} ;