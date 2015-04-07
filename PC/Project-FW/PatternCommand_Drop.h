#pragma once

#include "PatternCommand.h"
#include "Position.h"
#include <string>

class CPatternCommand_Drop : public CPatternCommand
{
private :
	char m_axis ;
	std::string m_strName ;
	POSITION m_startPosition, m_endPosition ;
	float m_fMoveTime, m_fStayTime ;

public :
	CPatternCommand_Drop(std::string strName, POSITION startPosition, POSITION endPosition, float moveTime, float stayTime) ;
	CPatternCommand_Drop(char axis, std::string strName, float startAxis, float endAxis, float moveTime, float stayTime) ;
	~CPatternCommand_Drop() ;

	void Update() ;
} ;