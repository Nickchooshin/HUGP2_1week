#pragma once

#include "Bounding.h"
#include "Position.h"

class CCollider
{
public :
	CCollider() ;
	CCollider(const CCollider &) ;
	~CCollider() ;

	bool BeCollision(BOUNDING_BOX A, BOUNDING_BOX B) ;
	bool BeCollision(BOUNDING_BOX A, BOUNDING_CIRCLE B) ;
	bool BeCollision(BOUNDING_BOX A, BOUNDING_ELLIPSE B) ;
	bool BeCollision(BOUNDING_BOX A, BOUNDING_LINE B) ;

	bool BeCollision(BOUNDING_LINE A, BOUNDING_LINE B) ;
	bool BeCollision(POSITION A, BOUNDING_CIRCLE B) ;
	bool BeCollision(POSITION A, BOUNDING_ELLIPSE B) ;
} ;