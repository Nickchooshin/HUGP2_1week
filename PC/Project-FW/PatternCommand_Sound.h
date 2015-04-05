#pragma once

#include "PatternCommand.h"
#include <string>

class CPatternCommand_Sound : public CPatternCommand
{
private :
	std::string m_strName ;

public :
	CPatternCommand_Sound(std::string strName) ;
	virtual ~CPatternCommand_Sound() ;

	void Update() ;
} ;