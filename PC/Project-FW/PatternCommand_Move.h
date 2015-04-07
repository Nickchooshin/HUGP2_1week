#pragma once

#include "PatternCommand.h"
#include "Position.h"
#include <string>

class CPatternCommand_Move : public CPatternCommand
{
private :
	char m_axis ;
	std::string m_strName ;
	POSITION m_startPosition, m_endPosition ;
	float m_fMoveTime ;

public :
	CPatternCommand_Move(std::string strName, POSITION startPosition, POSITION endPosition, float moveTime) ;
	CPatternCommand_Move(char axis, std::string strName, float startAxis, float endAxis, float moveTime) ;
	~CPatternCommand_Move() ;

	void Update() ;
} ;