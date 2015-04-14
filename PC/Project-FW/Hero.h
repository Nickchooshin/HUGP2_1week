#pragma once

#include "Objects.h"
#include "Singleton.h"

class CHero : public CObjects, public Singleton<CHero>
{
private :
	float m_fSpeed ;
	float m_fJump, m_fGravity ;
	float m_fYVelocity ;

	bool m_bJump, m_bDead ;

	long m_lStartTime, m_lEndTime ;
	bool m_bStart ;

public :
	CHero() ;
	~CHero() ;

	void Init() ;

	const int GetScore() const ;
	const int GetRank() const ;
	const bool BeDead() const ;
	
	void Dead() ;
	void Clear() ;

	void Update() ;
private :
	void Move() ;
	void Gravity() ;
} ;

#define g_Hero CHero::GetInstance()