#pragma once

#include "Objects.h"
#include "Singleton.h"

class CHero : public CObjects, public Singleton<CHero>
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

#define g_Hero CHero::GetInstance()