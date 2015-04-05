#pragma once

#include "PatternCommand.h"
#include "Position.h"
#include <string>

class CPatternCommand_Move : public CPatternCommand
{
private :
	std::string m_strName ;
	POSITION m_startPosition, m_endPosition ;
	float m_fTime, m_fMoveTime ;

public :
	CPatternCommand_Move(std::string strName, POSITION startPosition, POSITION endPosition, float moveTime) ;
	virtual ~CPatternCommand_Move() ;

	void Update() ;
} ;