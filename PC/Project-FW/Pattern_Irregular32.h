#pragma once

#include "Pattern.h"
#include <vector>

class CBoss ;

class CPattern_Irregular32 : public CPattern
{
private :
	std::vector<CBoss*> m_BossList ;

	int m_nNum ;

	void (CPattern_Irregular32::*m_pfnEvent)(void) ;

public :
	CPattern_Irregular32() ;
	~CPattern_Irregular32() ;

	void Update() ;

	void Render() ;
private :
	void EventCreate() ;

	void CreateBoss() ;
} ;