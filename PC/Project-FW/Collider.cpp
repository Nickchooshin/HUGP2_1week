#include "Collider.h"
#include <math.h>

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

bool CCollider::BeCollision(BOUNDING_BOX A, BOUNDING_CIRCLE B)
{
	POSITION vertex[4] = { POSITION(A._left, A._top), POSITION(A._right, A._top),
						   POSITION(A._left, A._bottom), POSITION(A._right, A._bottom) } ;

	for(int i=0; i<4; i++)
	{
		if(BeCollision(vertex[i], B))
			return true ;
	}

	return false ;
}

bool CCollider::BeCollision(BOUNDING_BOX A, BOUNDING_ELLIPSE B)
{
	POSITION vertex[4] = { POSITION(A._left, A._top), POSITION(A._right, A._top),
						   POSITION(A._left, A._bottom), POSITION(A._right, A._bottom) } ;

	for(int i=0; i<4; i++)
	{
		if(BeCollision(vertex[i], B))
			return true ;
	}

	return false ;
}

bool CCollider::BeCollision(BOUNDING_BOX A, BOUNDING_LINE B)
{
	BOUNDING_LINE Line[4] = { BOUNDING_LINE(A._left, A._top, A._right, A._top),
							  BOUNDING_LINE(A._right, A._top, A._right, A._bottom),
							  BOUNDING_LINE(A._right, A._bottom, A._left, A._bottom),
							  BOUNDING_LINE(A._left, A._bottom, A._left, A._top) } ;

	for(int i=0; i<4; i++)
	{
		if(BeCollision(Line[i], B))
			return true ;
	}

	return false ;
}

bool CCollider::BeCollision(BOUNDING_LINE A, BOUNDING_LINE B)
{
	float den ;
	float u, v ;

	den = ((A._x2-A._x1)*(B._y2-B._y1)-(B._x2-B._x1)*(A._y2-A._y1)) ;
	u = ((B._x2-B._x1)*(A._y1-B._y1)-(B._y2-B._y1)*(A._x1-B._x1)) / den ;
	v = ((A._x2-A._x1)*(A._y1-B._y1)-(A._y2-A._y1)*(A._x1-B._x1)) / den ;

	if( (u>0.0f && u<1.0f) &&
		(v>0.0f && v<1.0f) )
		return true ;

	return false ;
}

bool CCollider::BeCollision(POSITION A, BOUNDING_CIRCLE B)
{
	float x = B._x - A.x ;
	float y = B._y - A.y ;
	float distance = sqrt(pow(x, 2.0f) + pow(y, 2.0f)) ;

	if(distance<=B._radius)
		return true ;

	return false ;
}

bool CCollider::BeCollision(POSITION A, BOUNDING_ELLIPSE B)
{
	float x = B._x - A.x ;
	float y = B._y - A.y ;
	float temp = (pow(x, 2.0f) / pow(B._a, 2.0f)) + (pow(y, 2.0f) / pow(B._b, 2.0f)) ;

	if(temp<=1.0f)
		return true ;

	return false ;
}