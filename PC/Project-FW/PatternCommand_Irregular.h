#pragma once

#include "PatternCommand.h"
#include "Position.h"
#include <string>

class CPatternCommand_Irregular : public CPatternCommand
{
private :
	std::string m_strName ;

public :
	CPatternCommand_Irregular(std::string strName) ;
	~CPatternCommand_Irregular() ;

	void Update() ;
} ;