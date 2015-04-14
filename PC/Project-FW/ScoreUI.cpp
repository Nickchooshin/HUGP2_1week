#include "ScoreUI.h"
#include "Sprite.h"
#include "NumberUI.h"

CScoreUI::CScoreUI() : m_fX(0.0f), m_fY(0.0f),
					   m_pBackground(NULL),
					   m_pRank(NULL)
{
}
CScoreUI::~CScoreUI()
{
	if(m_pBackground!=NULL)
		delete m_pBackground ;
	if(m_pRank!=NULL)
		delete m_pRank ;

	for(int i=0; i<5; i++)
		delete m_pNumberUI[i] ;
}

void CScoreUI::Init()
{
	m_pBackground = new CSprite ;
	m_pBackground->Init("Resource/Image/Game/play_ui.png") ;
	m_pBackground->SetPosition(m_fX, m_fY) ;

	m_pRank = new CSprite ;
	m_pRank->Init(110.0f, 100.0f, "Resource/Image/Game/play_rank.png") ;
	m_pRank->SetTextureUV(220.0f, 200.0f, 330.0f, 300.0f) ;
	m_pRank->SetPosition(m_fX, m_fY + 25.0f) ;

	for(int i=0; i<5; i++)
	{
		m_pNumberUI[i] = new CNumberUI ;
		m_pNumberUI[i]->Init() ;
	}
	
	SetNumberPosition() ;
}

void CScoreUI::SetPosition(float fX, float fY)
{
	m_fX = fX ;
	m_fY = fY ;
	m_pBackground->SetPosition(m_fX, m_fY) ;
	m_pRank->SetPosition(m_fX, m_fY + 25.0f) ;
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

void CScoreUI::Render()
{
	m_pBackground->Render() ;
	m_pRank->Render() ;

	for(int i=0; i<5; i++)
		m_pNumberUI[i]->Render() ;
}

void CScoreUI::SetNumberPosition()
{
	for(int i=0; i<5; i++)
	{
		float x = (i-2) * 18.0f ;
		m_pNumberUI[i]->SetPosition(m_fX + x, m_fY - 47.0f) ;
	}
}