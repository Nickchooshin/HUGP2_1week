#pragma once

class CBoss ;

class CPattern
{
protected :
	CBoss *m_pBoss ;
	float m_fTime, m_fTargetTime ;

	bool m_bLife ;

public :
	CPattern() ;
	CPattern(float targetTime) ;
	virtual ~CPattern() ;

	void SetBoss(CBoss *pBoss) ;

	virtual void Update() = 0 ;

	virtual void Render() ;

	const bool BeLife() const ;
protected :
	void Time() ;
} ;