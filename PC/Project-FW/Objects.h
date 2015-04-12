#pragma once

#include "Position.h"
#include "Bounding.h"

class CSprite ;

class CObjects
{
protected :
	CSprite *m_pSprite ;
	IBounding *m_pBounding ;
	
	POSITION m_Position ;
	bool m_bCollision ;

public :
	CObjects() ;
	~CObjects() ;

	virtual void Init() = 0 ;

	void SetPosition(POSITION Position) ;
	void SetPosition(float x, float y) ;
	void SetBounding(IBounding *pBounding) ;
	void SetCollision(bool bCollision) ;

	POSITION GetPosition() const ;
	IBounding* GetBounding() const ;
	bool BeCollision() const ;

	virtual void Update() ;

	virtual void Render() ;
} ;