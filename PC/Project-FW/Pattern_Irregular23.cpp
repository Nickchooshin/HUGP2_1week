#include "Pattern_Irregular23.h"
#include "Boss.h"
#include "Hero.h"

#include "D3dDevice.h"
#include "BossManager.h"
#include "CollisionManager.h"

CPattern_Irregular23::CPattern_Irregular23() : CPattern(9999.0f),
											   m_nBossNum(0),
											   m_pfnEvent(&CPattern_Irregular23::EventWait)
{
	m_BossPosition[0] = POSITION(140.0f, 80.0f) ;
	m_BossPosition[1] = POSITION(640.0f, 80.0f) ;
	m_BossPosition[2] = POSITION(1140.0f, 80.0f) ;
	m_BossPosition[3] = POSITION(140.0f, 600.0f) ;
	m_BossPosition[4] = POSITION(1140.0f, 600.0f) ;

	for(int i=0; i<5; i++)
	{
		m_pBossArray[i] = g_BossManager->GetBossInstance("obj5") ;
		m_pBossArray[i]->SetPosition(m_BossPosition[i]) ;
	}
}
CPattern_Irregular23::~CPattern_Irregular23()
{
	for(int i=0; i<5; i++)
	{
		if(m_pBossArray[i]!=NULL)
			delete m_pBossArray[i] ;
	}
}

void CPattern_Irregular23::Update()
{	
	const float fTime = g_D3dDevice->GetTime() ;
	m_bLife = false ;

	Time() ;

	for(int i=0; i<5; i++)
	{
		if(m_pBossArray[i]->BeCollision())
		{
			m_bLife = true ;
			m_BossPosition[i] += (m_MoveVector[i] * fTime) ;
			m_pBossArray[i]->SetPosition(m_BossPosition[i]) ;

			if(m_BossPosition[i].x<=-95.0f || m_BossPosition[i].x>=1375.0f || m_BossPosition[i].y<=-50.0f || m_BossPosition[i].y>=770.0f)
				m_pBossArray[i]->SetCollision(false) ;
		}
	}

	if(m_pfnEvent!=NULL)
		(this->*m_pfnEvent)() ;
}

void CPattern_Irregular23::Render()
{
	for(int i=0; i<5; i++)
		m_pBossArray[i]->Render() ;
}

void CPattern_Irregular23::EventWait()
{
	if(m_fTime>=0.5f)
	{
		m_MoveVector[m_nBossNum] = g_Hero->GetPosition() - m_BossPosition[m_nBossNum] ;
		float force = pow(pow(m_MoveVector[m_nBossNum].x, 2) + pow(m_MoveVector[m_nBossNum].y, 2), 0.5f) ;
		m_MoveVector[m_nBossNum] = m_MoveVector[m_nBossNum] * (500.0f / force) ;

		m_fTime = 0.0f ;
		++m_nBossNum ;
		m_pfnEvent = &CPattern_Irregular23::EventShoot ;
		(this->*m_pfnEvent)() ;
	}
}

void CPattern_Irregular23::EventShoot()
{
	if((m_nBossNum<4 && m_fTime>=1.0f) || (m_nBossNum==4 && m_fTime>=0.5f))
	{
		m_MoveVector[m_nBossNum] = g_Hero->GetPosition() - m_BossPosition[m_nBossNum] ;
		float force = pow(pow(m_MoveVector[m_nBossNum].x, 2) + pow(m_MoveVector[m_nBossNum].y, 2), 0.5f) ;
		m_MoveVector[m_nBossNum] = m_MoveVector[m_nBossNum] * (500.0f / force) ;

		m_fTime = 0.0f ;
		++m_nBossNum ;

		if(m_nBossNum>=5)
			m_pfnEvent = NULL ;
	}
}