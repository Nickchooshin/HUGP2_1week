#pragma once

#include "Pattern.h"
#include <fmod.hpp>

class CBoss ;
class CLineEffect ;

class CPattern_Irregular22 : public CPattern
{
private :
	CBoss *m_pWarning ;
	CLineEffect *m_pLineEffect ;
	float m_fX ;

	FMOD::Sound *m_pSound ;

	void (CPattern_Irregular22::*m_pfnEvent)(void) ;

public :
	CPattern_Irregular22() ;
	~CPattern_Irregular22() ;

	void Update() ;

	void Render() ;
private :
	void EventWarning() ;
	void EventWaitLineEffect() ;
	void EventLineEffect() ;
} ;