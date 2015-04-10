#pragma once

#include "Objects.h"

class CLazer : public CObjects
{
private :
	POSITION m_LazerPosition, m_endLazerPosition ;
	VECTOR m_LazerVector ;

	float m_fLength, m_fDegree ;

public :
	CLazer() ;
	~CLazer() ;

	void Init() ;

	void SetLazerPosition(POSITION startPosition, POSITION endPosition) ;
	void SetLazerPosition(float startX, float startY, float endX, float endY) ;

	void Update() ;
private :
	void Degree() ;
	void Length() ;
} ;