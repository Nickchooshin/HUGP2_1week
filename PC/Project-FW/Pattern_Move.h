#pragma once

#include "Pattern.h"
#include "Position.h"

class CPattern_Move : public CPattern
{
private :
	POSITION m_startPosition, m_endPosition ;
	VECTOR m_moveVector ;

public :
	CPattern_Move(POSITION startPosition, POSITION endPosition, float moveTime) ;
	~CPattern_Move() ;

	void Update() ;
} ;