#pragma once

#include "Objects.h"

class CBoss : public CObjects
{
protected :
	bool m_bLife, m_bCollision ;

public :
	CBoss() ;
	CBoss(const CBoss *pBoss) ;
	~CBoss() ;

	void Init() ;

	void SetImage(char *strImage) ;
	void SetImage(float fWidth, float fHeight, char *strImage) ;
	void SetBoundingBox(BBOX Box) ;
	void SetCollision(bool bCollision) ;

	bool BeCollision() const ;
} ;