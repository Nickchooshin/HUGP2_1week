#pragma once

#include "Pattern.h"
#include "Position.h"

class CBoss ;

class CPattern_Irregular23 : public CPattern
{
private :
	CBoss *m_pBossArray[5] ;
	POSITION m_BossPosition[5] ;
	VECTOR m_MoveVector[5] ;
	int m_nBossNum ;

	void (CPattern_Irregular23::*m_pfnEvent)(void) ;

public :
	CPattern_Irregular23() ;
	~CPattern_Irregular23() ;

	void Update() ;

	void Render() ;
private :
	void EventWait() ;
	void EventShoot() ;
} ;