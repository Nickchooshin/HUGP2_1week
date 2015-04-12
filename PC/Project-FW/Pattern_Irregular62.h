#pragma once

#include "Pattern.h"
#include "Position.h"

class CBoss ;
class CSprite ;

class CPattern_Irregular62 : public CPattern
{
private :
	CSprite *m_pWarning ;
	POSITION m_Position ;
	
	enum State { CHASE=0, ATTACK } ;
	State m_State ;

	void (CPattern_Irregular62::*m_pfnEvent)(void) ;

public :
	CPattern_Irregular62() ;
	~CPattern_Irregular62() ;

	void Update() ;

	void Render() ;
private :
	void EventChase() ;
	void EventAttack() ;
} ;