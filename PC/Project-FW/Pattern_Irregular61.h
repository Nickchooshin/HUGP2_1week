#pragma once

#include "Pattern.h"
#include "Position.h"
#include <fmod.hpp>

class CBoss ;

class CPattern_Irregular61 : public CPattern
{
private :
	CBoss *m_pBoss2 ;

	POSITION m_Position ;
	VECTOR m_moveVector ;
	float m_fDirection ;
	
	FMOD::Sound *m_pSound[2] ;

	void (CPattern_Irregular61::*m_pfnEvent)(void) ;

public :
	CPattern_Irregular61() ;
	~CPattern_Irregular61() ;

	void Update() ;

	void Render() ;
private :
	void EventMove() ;

	void Acceleration() ;
} ;