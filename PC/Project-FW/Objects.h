#pragma once

#include "Bounding.h"

class CSprite ;

class CObjects
{
protected :
	CSprite *m_pSprite ;
	BBox m_BBox ;
	
	float m_fX, m_fY ;

public :
	CObjects() ;
	~CObjects() ;

	virtual void Init() = 0 ;

	void SetPosition(float X, float Y) ;

	virtual void Update() ;

	virtual void Render() ;
} ;