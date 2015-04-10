#include "Pattern_Irregular33.h"
#include "Boss.h"
#include "Return.h"
#include "Sprite.h"
#include "Hero.h"

#include "D3dDevice.h"
#include "BossManager.h"

CPattern_Irregular33::CPattern_Irregular33() : CPattern(9999.0f),
											   m_pWarning(NULL),
											   m_fHeroX(0.0f),
											   m_nNum(0),
											   m_bWarning(false),
											   m_pfnEvent(&CPattern_Irregular33::EventWarning)
{
	m_pBoss = g_BossManager->GetBossInstance("obj6") ;

	m_pWarning = new CSprite ;
	m_pWarning->Init(100.0f, 300.0f, "Resource/Image/warning.png") ;

	m_fHeroX = g_Hero->GetPosition().x ;
}
CPattern_Irregular33::~CPattern_Irregular33()
{
	if(m_pWarning!=NULL)
		delete m_pWarning ;

	const int num=m_ReturnList.size() ;

	for(int i=0; i<num; i++)
		delete m_ReturnList[i] ;
}

void CPattern_Irregular33::Update()
{
	Time() ;

	if(m_nNum<4)
		(this->*m_pfnEvent)() ;

	int num=m_ReturnList.size() ;

	for(int i=0; i<num; i++)
	{
		CReturn *pReturn = m_ReturnList[i] ;
		pReturn->Update() ;
		if(pReturn->BeLife())
		{
			m_ReturnList.erase(m_ReturnList.begin() + i) ;
			delete pReturn ;
			--i ;
			--num ;
		}
	}

	if(m_nNum==4 && num==0)
		m_bLife = false ;
}

void CPattern_Irregular33::Render()
{
	const float fWinHeight = g_D3dDevice->GetWinHeight() ;

	if(m_bWarning)
	{
		m_pWarning->SetPosition(m_fHeroX, fWinHeight-570.0f) ;
		m_pWarning->Render() ;
	}

	const int num=m_ReturnList.size() ;

	for(int i=0; i<num; i++)
		m_ReturnList[i]->Render() ;
}

void CPattern_Irregular33::EventWarning()
{
	m_bWarning = true ;

	if(m_fTime>=0.3f)
	{
		m_fTime = 0.0f ;
		m_bWarning = false ;

		m_pfnEvent = &CPattern_Irregular33::EventMove ;
	}
}

void CPattern_Irregular33::EventMove()
{
	if(m_fTime>=0.2f)
	{
		const float fWinHeight = g_D3dDevice->GetWinHeight() ;

		CReturn *pReturn = new CReturn ;
		pReturn->Init() ;
		pReturn->SetRoute(m_fHeroX, -74.0f, m_fHeroX, fWinHeight-494.0f) ;
		m_ReturnList.push_back(pReturn) ;
		
		m_fTime = 0.0f ;
		m_fHeroX = g_Hero->GetPosition().x ;
		++m_nNum ;

		m_pfnEvent = &CPattern_Irregular33::EventWarning ;
	}
}