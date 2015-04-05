#pragma once

#include "Bounding.h"
#include "Position.h"

class CSprite ;

class CObjects
{
protected :
	CSprite *m_pSprite ;
	BBox m_BBox ;
	
	POSITION m_Position ;

public :
	CObjects() ;
	~CObjects() ;

	virtual void Init() = 0 ;

	void SetPosition(POSITION Position) ;
	void SetPosition(float x, float y) ;

	virtual void Update() ;

	virtual void Render() ;
} ;