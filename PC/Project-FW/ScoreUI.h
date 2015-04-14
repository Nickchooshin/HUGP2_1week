#pragma once

class CSprite ;
class CNumberUI ;

class CScoreUI
{
private :
	float m_fX, m_fY ;
	CNumberUI *m_pNumberUI[5] ;

	int m_nType ;

public :
	CScoreUI() ;
	~CScoreUI() ;

	void Init(int type) ;

	void SetPosition(float fX, float fY) ;
	void SetNumber(int nNum) ;

	void Update() ;

	void Render() ;
private :
	void SetNumberPosition() ;
} ;