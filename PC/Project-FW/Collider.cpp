#include "Collider.h"

CCollider::CCollider()
{
}
CCollider::~CCollider()
{
}

bool CCollider::BeCollision(BOUNDING_BOX A, BOUNDING_BOX B)
{
	if( A._left < B._right && A._right > B._left &&
		A._top > B._bottom && A._bottom < B._top )
		return true ;

	return false ;
}

/*bool CCollider::BeCollision(BOUNDING_BOX Box, BOUNDING_CIRCLE Circle)
{
}*/

bool CCollider::BeCollision(BOUNDING_BOX A, BOUNDING_LINE B)
{
	BOUNDING_LINE ALine[4] ;

	ALine[0] = BOUNDING_LINE(A._left, A._top, A._right, A._top) ;
	ALine[1] = BOUNDING_LINE(A._right, A._top, A._right, A._bottom) ;
	ALine[2] = BOUNDING_LINE(A._right, A._bottom, A._left, A._bottom) ;
	ALine[3] = BOUNDING_LINE(A._left, A._bottom, A._left, A._top) ;

	for(int i=0; i<4; i++)
	{
		if(!BeCollision(ALine[i], B))
			return false ;
	}

	return true ;
}

bool CCollider::BeCollision(BOUNDING_LINE A, BOUNDING_LINE B)
{
	float u, v ;

	u = ((B._x2-B._x1)*(A._y1-B._y1)-(B._y2-B._y1)*(A._x1-B._x1)) / ((A._x2-A._x1)*(B._y2-B._y1)-(B._x2-B._x1)*(A._y2-A._y1)) ;
	v = ((A._x2-A._x1)*(A._y1-B._y1)-(A._y2-A._y1)*(A._x1-B._x1)) / ((A._x2-A._x1)*(B._y2-B._y1)-(B._x2-B._x1)*(A._y2-A._y1)) ;

	if( (u>0.0f && u<1.0f) &&
		(v>0.0f && v<1.0f) )
		return true ;

	return false ;
}