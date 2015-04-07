#include "LineEffect.h"
#include "Sprite.h"

#include "D3dDevice.h"

CLineEffect::CLineEffect() : m_pSprite(NULL),
							 m_fCreateTime(0.05f),
							 m_fTime(0.0f)
{
	m_pSprite = new CSprite ;
	m_pSprite->Init("Resource/Image/Boss/obj_bss2_04.png") ;
}
CLineEffect::~CLineEffect()
{
	if(m_pSprite!=NULL)
		delete m_pSprite ;
}

void CLineEffect::Update()
{
	const float fTime = g_D3dDevice->GetTime() ;
	int num=m_LinePosition.size() ;

	for(int i=0; i<num; i++)
	{
		POSITION &pos = m_LinePosition[i] ;
		if(pos.x>=1280.0f)
		{
			m_LinePosition.erase(m_LinePosition.begin() + i) ;
			--i ;
			--num ;
		}
		else
			pos.x += 3000.0f * fTime ;
	}

	CreateLineEffect() ;
}

void CLineEffect::Render()
{
	const int num=m_LinePosition.size() ;

	for(int i=0; i<num; i++)
	{
		const POSITION pos = m_LinePosition[i] ;
		m_pSprite->SetPosition(pos.x, pos.y) ;
		m_pSprite->Render() ;
	}
}

void CLineEffect::CreateLineEffect()
{
	while(m_fTime>=m_fCreateTime)
	{
		const float fWinHeight = g_D3dDevice->GetWinHeight() ;
		const float fLineHeight = fWinHeight / 60.0f ;
		const float fLineY = (rand()%60) * fLineHeight + (fLineHeight / 2.0f) ;

		POSITION pos(0.0f, fLineY) ;
		m_LinePosition.push_back(pos) ;

		m_fTime -= m_fCreateTime ;
	}

	m_fTime += g_D3dDevice->GetTime() ;
}