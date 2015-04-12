#pragma once

#include "Pattern.h"
#include "Position.h"
#include <fmod.hpp>

class CSprite ;

class CPattern_Irregular52 : public CPattern
{
private :
	CSprite *m_pWarning ;
	POSITION m_Position ;
	VECTOR m_moveVector, m_accVector ;

	FMOD::Sound *m_pSound ;

	enum State { CHASE=0, WAIT, ATTACK } ;
	State m_State ;

	void (CPattern_Irregular52::*m_pfnEvent)(void) ;

public :
	CPattern_Irregular52() ;
	~CPattern_Irregular52() ;

	void Update() ;

	void Render() ;
private :
	void EventChase() ;
	void EventWait() ;
	void EventAttack() ;
} ;