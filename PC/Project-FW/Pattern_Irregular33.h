#pragma once

#include "Pattern.h"
#include "Position.h"
#include <vector>

class CSprite ;
class CReturn ;

class CPattern_Irregular33 : public CPattern
{
private :
	CSprite *m_pWarning ;
	std::vector<CReturn*> m_ReturnList ;
	float m_fHeroX ;

	int m_nNum ;
	bool m_bWarning ;

	void (CPattern_Irregular33::*m_pfnEvent)(void) ;

public :
	CPattern_Irregular33() ;
	~CPattern_Irregular33() ;

	void Update() ;

	void Render() ;
private :
	void EventWarning() ;
	void EventMove() ;
} ;