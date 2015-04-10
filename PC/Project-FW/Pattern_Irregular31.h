#pragma once

#include "Pattern.h"

class CBoss ;
class CLazer ;

class CPattern_Irregular31 : public CPattern
{
private :
	CLazer *m_pLazer[2] ;

	void (CPattern_Irregular31::*m_pfnEvent)(void) ;

public :
	CPattern_Irregular31() ;
	~CPattern_Irregular31() ;

	void Update() ;

	void Render() ;
private :
	void EventWait() ;
	void EventShootLazer() ;
	void EventMoveLazer() ;
} ;