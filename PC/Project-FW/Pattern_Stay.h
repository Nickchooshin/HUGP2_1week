#pragma once

#include "Pattern.h"
#include "Position.h"

class CPattern_Stay : public CPattern
{
private :
	POSITION m_stayPosition ;

public :
	CPattern_Stay(POSITION stayPosition, float stayTime) ;
	~CPattern_Stay() ;

	void Update() ;
} ;