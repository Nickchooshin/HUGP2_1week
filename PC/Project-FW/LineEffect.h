#pragma once

#include "Position.h"
#include <vector>

class CSprite ;

class CLineEffect
{
private :
	CSprite *m_pSprite ;
	std::vector<POSITION> m_LinePosition ;

	const float m_fCreateTime ;
	float m_fTime ;

public :
	CLineEffect() ;
	~CLineEffect() ;

	void Update() ;

	void Render() ;
private :
	void CreateLineEffect() ;
} ;