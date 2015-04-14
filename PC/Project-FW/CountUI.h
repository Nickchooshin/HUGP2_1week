#pragma once

#include "MusicManager.h"

class CSprite ;

class CCountUI
{
private :
	CSprite *m_pSprite ;

	int m_nNum ;
	float m_fTime ;
	bool m_bStart ;
	bool m_bCount, m_bLife ;
	
	FMOD::Sound *m_pSECount, *m_pSEStart ;

public :
	CCountUI() ;
	~CCountUI() ;

	void Init() ;

	void SetPosition(float x, float y) ;
	
	const bool BeCount() const ;
	const bool BeLife() const ;

	void Update() ;

	void Render() ;
} ;