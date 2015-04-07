#pragma once

#include "Pattern.h"
#include "Position.h"

class CPattern_Warning : public CPattern
{
private :
	POSITION m_startPosition ;
	bool m_bChase ;

public :
	CPattern_Warning(POSITION startPosition, float stayTime, bool bChase) ;
	~CPattern_Warning() ;

	void Update() ;
} ;