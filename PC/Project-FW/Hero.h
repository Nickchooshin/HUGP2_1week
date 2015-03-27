#pragma once

#include "Objects.h"

class CHero : public CObjects
{
private :
	float m_fSpeed ;
	float m_fJump, m_fGravity ;
	float m_fYVelocity ;

	bool m_bJump ;

public :
	CHero() ;
	~CHero() ;

	void Init() ;

	void Update() ;
private :
	void Move() ;
	void Gravity() ;
} ;