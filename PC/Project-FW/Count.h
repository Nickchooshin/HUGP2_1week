#pragma once

#include "MusicManager.h"

class CSprite ;

class CCount
{
private :
	CSprite *m_pSprite ;

	int m_nNum ;
	float m_fTime ;
	bool m_bStart, m_bLife ;
	
	FMOD::Sound *m_pSECount, *m_pSEStart ;

public :
	CCount() ;
	~CCount() ;

	void Init() ;

	void SetPosition(float x, float y) ;

	const bool BeLife() const ;

	void Update() ;

	void Render() ;
} ;