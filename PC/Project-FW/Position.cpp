#include "Position.h"

POSITION::POSITION() : x(0.0f), y(0.0f)
{
}
POSITION::POSITION(float X, float Y) : x(X), y(Y)
{
}
POSITION::POSITION(const POSITION &p) : x(p.x), y(p.y)
{
}
POSITION::~POSITION()
{
}

POSITION POSITION::operator + (const POSITION& p) const
{
	POSITION temp(*this) ;

	temp.x += p.x ;
	temp.y += p.y ;

	return temp ;
}

POSITION POSITION::operator - (const POSITION& p) const
{
	POSITION temp(*this) ;

	temp.x -= p.x ;
	temp.y -= p.y ;

	return temp ;
}

POSITION POSITION::operator * (float f) const
{
	POSITION temp(*this) ;

	temp.x *= f ;
	temp.y *= f ;

	return temp ;
}

POSITION POSITION::operator / (float f) const
{
	POSITION temp(*this) ;

	temp.x /= f ;
	temp.y /= f ;

	return temp ;
}

POSITION& POSITION::operator += (const POSITION& p)
{
	*this = *this + p ;

	return *this ;
}

POSITION& POSITION::operator -= (const POSITION& p)
{
	*this = *this - p ;

	return *this ;
}

POSITION& POSITION::operator *= (float f)
{
	*this = *this * f ;

	return *this ;
}

POSITION& POSITION::operator /= (float f)
{
	*this = *this / f ;

	return *this ;
}

bool POSITION::operator == (const POSITION& p) const
{
	if(x==p.x && y==p.y)
		return true ;

	return false ;
}

bool POSITION::operator != (const POSITION& p) const
{
	if(x!=p.x && y!=p.y)
		return true ;

	return false ;
}