#include "NumberUI.h"
#include "Sprite.h"

CNumberUI::CNumberUI() : m_fX(0.0f), m_fY(0.0f),
						 m_fWidth(0.0f), m_fHeight(0.0f),
						 m_nNumber(0),
						 m_pSprite(NULL)
{
}
CNumberUI::~CNumberUI()
{
	if(m_pSprite!=NULL)
		delete m_pSprite ;
}

void CNumberUI::Init(int type)
{
	m_pSprite = new CSprite ;

	if(type==0)
	{
		m_fWidth = 20.0f ;
		m_fHeight = 30.0f ;
		m_pSprite->Init(m_fWidth, m_fHeight, "Resource/Image/Game/play_score.png") ;
	}
	else if(type==1)
	{
		m_fWidth = 50.0f ;
		m_fHeight = 80.0f ;
		m_pSprite->Init(m_fWidth, m_fHeight, "Resource/Image/Gameover/rst_score.png") ;
	}
	
	m_pSprite->SetTextureUV(0.0f, 0.0f, m_fWidth, m_fHeight) ;
}

void CNumberUI::SetPosition(float fX, float fY)
{
	m_fX = fX ;
	m_fY = fY ;
}

void CNumberUI::SetNumber(int nNum)
{
	if(nNum<0 || nNum>9)
		return ;

	if(m_nNumber!=nNum)
	{
		m_nNumber = nNum ;

		float u1 = m_fWidth * (float)nNum ;
		float u2 = u1 + m_fWidth ;

		m_pSprite->SetTextureUV(u1, 0.0f, u2, m_fHeight) ;
	}
}

const float CNumberUI::GetWidth() const
{
	return m_fWidth ;
}

void CNumberUI::Render()
{
	m_pSprite->SetPosition(m_fX, m_fY) ;
	m_pSprite->Render() ;
}