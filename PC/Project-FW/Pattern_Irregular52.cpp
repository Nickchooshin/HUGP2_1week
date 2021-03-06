#include "Pattern_Irregular52.h"
#include "Boss.h"
#include "Hero.h"
#include "Sprite.h"

#include "D3dDevice.h"
#include "BossManager.h"
#include "MusicManager.h"

CPattern_Irregular52::CPattern_Irregular52() : CPattern(9999.0f),
											   m_pWarning(NULL),
											   m_Position(),
											   m_moveVector(), m_accVector(800.0f, 0.0f),
											   m_pSound(NULL),
											   m_State(CHASE),
											   m_pfnEvent(&CPattern_Irregular52::EventChase)
{
	m_Position = g_Hero->GetPosition() ;
	m_Position.y = 360.0f ;

	m_pWarning = new CSprite ;
	m_pWarning->Init(600.0f, 720.0f, "Resource/Image/warning.png") ;

	m_pBoss = g_BossManager->GetBossInstance("obj4") ;

	m_pSound = g_MusicManager->LoadMusic("Resource/Sound/SE_bss/SE_bss5_04.mp3", false, false) ;
}
CPattern_Irregular52::~CPattern_Irregular52()
{
	if(m_pWarning!=NULL)
		delete m_pWarning ;
}

void CPattern_Irregular52::Update()
{
	Time() ;

	(this->*m_pfnEvent)() ;
}

void CPattern_Irregular52::Render()
{
	if(m_State==CHASE)
		m_pWarning->Render() ;
	else if(m_State==ATTACK)
		m_pBoss->Render() ;
}

void CPattern_Irregular52::EventChase()
{
	const float fTime = g_D3dDevice->GetTime() ;
	POSITION heroPosition = g_Hero->GetPosition() ;

	if(m_Position.x<heroPosition.x)
		m_moveVector += m_accVector * fTime ;
	else if(m_Position.x>heroPosition.x)
		m_moveVector -= m_accVector * fTime ;

	m_Position += m_moveVector * fTime ;
	m_pWarning->SetPosition(m_Position.x, m_Position.y) ;

	if(m_fTime>=4.0f)
	{
		m_State = WAIT ;
		m_fTime = 0.0f ;

		m_pfnEvent = &CPattern_Irregular52::EventWait ;
		(this->*m_pfnEvent)() ;
	}
}

void CPattern_Irregular52::EventWait()
{
	if(m_fTime>=0.3f)
	{
		m_State = ATTACK ;
		m_fTime = 0.0f ;

		g_MusicManager->PlayMusic(m_pSound, 1) ;
		
		m_pfnEvent = &CPattern_Irregular52::EventAttack ;
		(this->*m_pfnEvent)() ;
	}
}

void CPattern_Irregular52::EventAttack()
{
	m_Position.y = 1020.0f + (-1320.0f * (m_fTime/0.6f)) ;
	m_pBoss->SetPosition(m_Position) ;

	if(m_fTime>=0.6f)
		m_bLife = false ;
}