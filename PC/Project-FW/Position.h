#pragma once

typedef struct POSITION
{
public :
	float x, y ;

public :
	POSITION() ;
	POSITION(float X, float Y) ;
	POSITION(const POSITION &p) ;
	~POSITION() ;

	POSITION operator + (const POSITION& p) const ;
	POSITION operator - (const POSITION& p) const ;
	POSITION operator * (float f) const ;
	POSITION operator / (float f) const ;

	POSITION& operator += (const POSITION& p) ;
	POSITION& operator -= (const POSITION& p) ;
	POSITION& operator *= (float f) ;
	POSITION& operator /= (float f) ;

	bool operator == (const POSITION& p) const ;
	bool operator != (const POSITION& p) const ;
} VECTOR ;