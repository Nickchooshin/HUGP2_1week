#include "Pattern_Irregular22.h"
#include "Boss.h"
#include "LineEffect.h"
#include "Hero.h"

#include "D3dDevice.h"
#include "BossManager.h"
#include "CollisionManager.h"
#include "MusicManager.h"

CPattern_Irregular22::CPattern_Irregular22() : CPattern(9999.0f),
											   m_pWarning(NULL),
											   m_pLineEffect(NULL),
											   m_fX(0.0f),
											   m_pSound(NULL),
											   m_pfnEvent(&CPattern_Irregular22::EventWarning)
{
	m_fX = g_Hero->GetPosition().x ;

	m_pWarning = g_BossManager->GetBossInstance("obj3") ;
	m_pWarning->SetPosition(m_fX, 360.0f) ;

	m_pLineEffect = new CLineEffect ;

	m_pSound = g_MusicManager->LoadMusic("Resource/Sound/SE_bss/SE_bss2_04.mp3", false, false) ;
}
CPattern_Irregular22::~CPattern_Irregular22()
{
	if(m_pWarning!=NULL)
		delete m_pWarning ;
	if(m_pLineEffect!=NULL)
		delete m_pLineEffect ;
}

void CPattern_Irregular22::Update()
{
	Time() ;

	(this->*m_pfnEvent)() ;
}

void CPattern_Irregular22::Render()
{
	if(m_fTime<=1.0f)
		m_pWarning->Render() ;

	if(m_fTime>=1.2f)
		m_pLineEffect->Render() ;
}

void CPattern_Irregular22::EventWarning()
{
	if(m_fTime>=1.0f)
	{
		g_MusicManager->PlayMusic(m_pSound, 1) ;

		m_pfnEvent = &CPattern_Irregular22::EventWaitLineEffect ;
		(this->*m_pfnEvent)() ;
	}
}

void CPattern_Irregular22::EventWaitLineEffect()
{
	if(m_fTime>=1.2f)
	{
		m_pfnEvent = &CPattern_Irregular22::EventLineEffect ;
		(this->*m_pfnEvent)() ;
	}
}

void CPattern_Irregular22::EventLineEffect()
{
	m_pLineEffect->Update() ;

	POSITION position = g_Hero->GetPosition() ;
	if(position.x-20.0f<m_fX-65.0f || position.x+20.0f>m_fX+65.0f)
		g_Hero->Dead() ;

	if(m_fTime>=4.2f)
		m_bLife = false ;
}