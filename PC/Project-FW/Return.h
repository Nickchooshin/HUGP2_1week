#pragma once

#include "Position.h"

class CBoss ;

class CReturn
{
private :
	CBoss *m_pBoss ;

	POSITION m_Position ;
	POSITION m_startPosition, m_endPosition ;
	VECTOR m_moveVector ;

	float m_fTime ;

	enum State { FORWARD=0, RETURN, END } ;
	State m_State ;

public :
	CReturn() ;
	~CReturn() ;

	void Init() ;

	void SetRoute(POSITION startPosition, POSITION endPosition) ;
	void SetRoute(float startX, float startY, float endX, float endY) ;

	bool BeLife() const ;

	void Update() ;

	void Render() ;
} ;