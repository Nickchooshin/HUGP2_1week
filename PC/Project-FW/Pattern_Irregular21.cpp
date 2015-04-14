#include "Pattern_Irregular21.h"
#include "Boss.h"
#include "Sprite.h"
#include "Hero.h"

#include "D3dDevice.h"
#include "BossManager.h"
#include "CollisionManager.h"
#include "MusicManager.h"

CPattern_Irregular21::CPattern_Irregular21() : CPattern(9999.0f),
											   m_fX(0.0f),
											   m_fMoveVector(-1200.0f),
											   m_nDropNum(0),
											   m_pWarning(NULL),
											   m_pSound(NULL),
											   m_State(CHASE),
											   m_pfnEvent(&CPattern_Irregular21::EventChase)
{
	const float fWinHeight = g_D3dDevice->GetWinHeight() ;

	m_fX = g_Hero->GetPosition().x ;

	for(int i=0; i<3; i++)
	{
		m_bDrop[i] = false ;
		m_pDropBoss[i] = g_BossManager->GetBossInstance("obj2") ;
		m_pDropBoss[i]->SetPosition(0.0f, 870.0f) ;
	}

	m_pWarning = new CSprite ;
	m_pWarning->Init(300.0f, 720.0f, "Resource/Image/warning.png") ;
	m_pWarning->SetPosition(m_fX, fWinHeight / 2.0f) ;

	m_pSound = g_MusicManager->LoadMusic("Resource/Sound/SE_bss/SE_bss2_02.mp3", false, false) ;
}
CPattern_Irregular21::~CPattern_Irregular21()
{
	for(int i=0; i<3; i++)
		delete m_pDropBoss[i] ;

	delete m_pWarning ;
}

void CPattern_Irregular21::Update()
{
	Time() ;

	const float fTime = g_D3dDevice->GetTime() ;

	for(int i=0; i<m_nDropNum; i++)
	{
		if(!m_bDrop[i])
		{
			float x = m_pDropBoss[i]->GetPosition().x ;
			float y = m_pDropBoss[i]->GetPosition().y ;

			y += m_fMoveVector * fTime ;
			if(y<=200.0f)
			{
				y = 200.0f ;
				m_bDrop[i] = true ;
				g_MusicManager->PlayMusic(m_pSound, 1) ;
			}

			m_pDropBoss[i]->SetPosition(x, y) ;
		}
	}

	(this->*m_pfnEvent)() ;
}

void CPattern_Irregular21::Render()
{
	for(int i=0; i<m_nDropNum; i++)
		m_pDropBoss[i]->Render() ;

	if(m_State==CHASE)
		m_pWarning->Render() ;
}

void CPattern_Irregular21::EventChase()
{
	m_fX = g_Hero->GetPosition().x ;
	m_pWarning->SetPosition(m_fX, m_pWarning->GetPosition().y) ;

	if(m_fTime>=1.5f)
	{
		m_fTime = 0.0f ;
		m_State = OTHER ;

		m_pfnEvent = &CPattern_Irregular21::EventWait ;
		(this->*m_pfnEvent)() ;
	}
}

void CPattern_Irregular21::EventWait()
{
	if(m_fTime>=0.2f)
	{
		m_fTime = 0.0f ;
		m_pDropBoss[m_nDropNum]->SetPosition(m_fX, 870.0f) ;
		++m_nDropNum ;
		
		if(m_nDropNum<3)
			m_pfnEvent = &CPattern_Irregular21::EventDrop ;
		else
			m_pfnEvent = &CPattern_Irregular21::EventRelease ;
		(this->*m_pfnEvent)() ;
	}
}

void CPattern_Irregular21::EventDrop()
{
	if(m_fTime>=0.5f)
	{
		m_fTime = 0.0f ;
		m_State = CHASE ;

		m_pfnEvent = &CPattern_Irregular21::EventChase ;
		(this->*m_pfnEvent)() ;
	}
}

void CPattern_Irregular21::EventRelease()
{
	if(m_fTime>=2.1f)
		m_bLife = false ;
}