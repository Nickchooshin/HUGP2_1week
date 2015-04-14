#pragma once

class CSprite ;

class CNumberUI
{
private :
	float m_fX, m_fY ;
	float m_fWidth, m_fHeight ;
	int m_nNumber ;
	CSprite *m_pSprite ;

public :
	CNumberUI() ;
	~CNumberUI() ;

	void Init() ;
	
	void SetPosition(float fX, float fY) ;
	void SetNumber(int nNum) ;

	const float GetWidth() const ;

	void Render() ;
} ;