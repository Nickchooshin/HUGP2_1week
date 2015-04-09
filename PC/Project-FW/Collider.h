#pragma once

#include "Bounding.h"

class CCollider
{
public :
	CCollider() ;
	CCollider(const CCollider &) ;
	~CCollider() ;

	bool BeCollision(BOUNDING_BOX A, BOUNDING_BOX B) ;
	//bool BeCollision(BOUNDING_BOX Box, BOUNDING_CIRCLE Circle) ;
	bool BeCollision(BOUNDING_BOX A, BOUNDING_LINE B) ;

	bool BeCollision(BOUNDING_LINE A, BOUNDING_LINE B) ;
} ;