#include "ScoreUI.h"
#include "Sprite.h"
#include "NumberUI.h"

#include "Hero.h"

CScoreUI::CScoreUI() : m_fX(0.0f), m_fY(0.0f),
					   m_nType(0)
{
}
CScoreUI::~CScoreUI()
{
	for(int i=0; i<5; i++)
		delete m_pNumberUI[i] ;
}

void CScoreUI::Init(int type)
{
	for(int i=0; i<5; i++)
	{
		m_pNumberUI[i] = new CNumberUI ;
		m_pNumberUI[i]->Init(type) ;
	}
	
	SetNumberPosition() ;
	m_nType = type ;
}

void CScoreUI::SetPosition(float fX, float fY)
{
	m_fX = fX ;
	m_fY = fY ;
	SetNumberPosition() ;
}

void CScoreUI::SetNumber(int nNum)
{
	int temp ;

	for(int i=4; i>=0; i--)
	{
		temp = nNum % 10 ;
		nNum = nNum / 10 ;

		m_pNumberUI[i]->SetNumber(temp) ;
	}
}

void CScoreUI::Update()
{
	SetNumber(g_Hero->GetScore()) ;
}

void CScoreUI::Render()
{
	for(int i=0; i<5; i++)
		m_pNumberUI[i]->Render() ;
}

void CScoreUI::SetNumberPosition()
{
	for(int i=0; i<5; i++)
	{
		float x ;
		if(m_nType==0)
			x = (i-2) * 18.0f ;
		else if(m_nType==1)
			x = (i-2) * 50.0f ;

		m_pNumberUI[i]->SetPosition(m_fX + x, m_fY) ;
	}
}