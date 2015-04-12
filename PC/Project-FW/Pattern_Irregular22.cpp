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
											   m_pSound(NULL),
											   m_pfnEvent(&CPattern_Irregular22::EventWarning)
{
	m_pWarning = g_BossManager->GetBossInstance("obj3") ;
	m_pWarning->SetPosition(g_Hero->GetPosition().x, 360.0f) ;

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
	if(m_fTime<=0.5f)
		m_pWarning->Render() ;

	if(m_fTime>=0.7f)
		m_pLineEffect->Render() ;
}

void CPattern_Irregular22::EventWarning()
{
	if(m_fTime>=0.5f)
	{
		g_MusicManager->PlayMusic(m_pSound, 1) ;

		m_pfnEvent = &CPattern_Irregular22::EventWaitLineEffect ;
		(this->*m_pfnEvent)() ;
	}
}

void CPattern_Irregular22::EventWaitLineEffect()
{
	if(m_fTime>=0.7f)
	{
		m_pfnEvent = &CPattern_Irregular22::EventLineEffect ;
		(this->*m_pfnEvent)() ;
	}
}

void CPattern_Irregular22::EventLineEffect()
{
	m_pLineEffect->Update() ;

	if(m_fTime>=3.7f)
		m_bLife = false ;
}