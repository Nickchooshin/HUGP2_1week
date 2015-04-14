#include "Pattern_Irregular62.h"
#include "Boss.h"
#include "Hero.h"
#include "Sprite.h"

#include "D3dDevice.h"
#include "BossManager.h"

CPattern_Irregular62::CPattern_Irregular62() : CPattern(9999.0f),
											   m_pWarning(NULL),
											   m_Position(0.0f, 360.0f),
											   m_State(CHASE),
											   m_pfnEvent(&CPattern_Irregular62::EventChase)
{
	m_pBoss = g_BossManager->GetBossInstance("obj3") ;

	m_pWarning = new CSprite ;
	m_pWarning->Init(300.0f, 720.0f, "Resource/Image/warning.png") ;
}
CPattern_Irregular62::~CPattern_Irregular62()
{
	if(m_pWarning!=NULL)
		delete m_pWarning ;
}

void CPattern_Irregular62::Update()
{
	Time() ;

	(this->*m_pfnEvent)() ;
}

void CPattern_Irregular62::Render()
{
	if(m_State==CHASE)
		m_pWarning->Render() ;
	else if(m_State==ATTACK)
		m_pBoss->Render() ;
}

void CPattern_Irregular62::EventChase()
{
	if(m_fTime<=1.8f)
	{
		m_Position.x = g_Hero->GetPosition().x ;
		m_pWarning->SetPosition(m_Position.x, m_Position.y) ;
	}

	if(m_fTime>=2.0f)
	{
		m_State = ATTACK ;
		m_fTime = 0.0f ;

		m_pfnEvent = &CPattern_Irregular62::EventAttack ;
		(this->*m_pfnEvent)() ;
	}
}

void CPattern_Irregular62::EventAttack()
{
	m_Position.y = 945.0f + (-1170 * (m_fTime/0.9f)) ;
	m_pBoss->SetPosition(m_Position) ;

	if(m_Position.y<=-225.0f)
		m_bLife = false ;
}