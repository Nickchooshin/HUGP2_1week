#pragma once

#include "Pattern.h"
#include "Position.h"

class CPattern_Drop : public CPattern
{
private :
	POSITION m_startPosition, m_endPosition ;
	VECTOR m_moveVector ;
	float m_fMoveTime ;

public :
	CPattern_Drop(POSITION startPosition, POSITION endPosition, float moveTime, float stayTime) ;
	~CPattern_Drop() ;

	void Update() ;
} ;