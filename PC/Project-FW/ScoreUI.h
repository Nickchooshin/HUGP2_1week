#pragma once

class CSprite ;
class CNumberUI ;

class CScoreUI
{
private :
	float m_fX, m_fY ;
	CSprite *m_pBackground ;
	CSprite *m_pRank ;
	CNumberUI *m_pNumberUI[5] ;

public :
	CScoreUI() ;
	~CScoreUI() ;

	void Init() ;

	void SetPosition(float fX, float fY) ;
	void SetNumber(int nNum) ;

	void Render() ;
private :
	void SetNumberPosition() ;
} ;