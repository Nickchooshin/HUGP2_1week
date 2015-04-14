#pragma once

#include "Pattern.h"
#include <fmod.hpp>

class CBoss ;
class CSprite ;

class CPattern_Irregular21 : public CPattern
{
private :
	float m_fX ;
	float m_fMoveVector ;
	int m_nDropNum ;
	bool m_bDrop[3] ;

	CBoss *m_pDropBoss[3] ;
	CSprite *m_pWarning ;

	FMOD::Sound *m_pSound ;

	enum State { CHASE=0, OTHER } ;
	State m_State ;

	void (CPattern_Irregular21::*m_pfnEvent)(void) ;

public :
	CPattern_Irregular21() ;
	~CPattern_Irregular21() ;

	void Update() ;

	void Render() ;
private :
	void EventChase() ;
	void EventWait() ;
	void EventDrop() ;
	void EventRelease() ;
} ;