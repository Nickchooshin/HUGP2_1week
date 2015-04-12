#include "Pattern_Irregular61.h"
#include "Boss.h"

#include "D3dDevice.h"
#include "BossManager.h"
#include "CollisionManager.h"
#include "MusicManager.h"

CPattern_Irregular61::CPattern_Irregular61() : CPattern(9999.0f),
											   m_pBoss2(NULL),
											   m_Position(70.0f, 120.0f),
											   m_moveVector(400.0f, 0.0f),
											   m_fDirection(1.0f),
											   m_pfnEvent(&CPattern_Irregular61::EventMove)
{
	m_pBoss = g_BossManager->GetBossInstance("obj2") ;
	m_pBoss2 = g_BossManager->GetBossInstance("obj2") ;

	m_pBoss->SetPosition(70.0f, 120.0f) ;
	m_pBoss2->SetPosition(1210.0f, 120.0f) ;

	m_pSound[0] = g_MusicManager->LoadMusic("Resource/Sound/SE_bss6_04.mp3", false, false) ;
	m_pSound[1] = g_MusicManager->LoadMusic("Resource/Sound/SE_bss6_05.mp3", false, false) ;
}
CPattern_Irregular61::~CPattern_Irregular61()
{
	if(m_pBoss2!=NULL)
		delete m_pBoss2 ;
}

void CPattern_Irregular61::Update()
{
	Time() ;

	(this->*m_pfnEvent)() ;
}

void CPattern_Irregular61::Render()
{
	m_pBoss->Render() ;
	m_pBoss2->Render() ;
}

void CPattern_Irregular61::EventMove()
{
	const float fTime = g_D3dDevice->GetTime() ;
	const float fWinWidth = g_D3dDevice->GetWinWidth() ;

	m_Position += m_moveVector * m_fDirection * fTime ;
	if(m_Position.x<=35.0f || m_Position.x>=1245.0f)
	{
		const float fWinWidth_Half = fWinWidth / 2.0f ;
		const float ScreenX = (fWinWidth_Half - 35.0f) * m_fDirection + fWinWidth_Half ;
		m_Position.x = ScreenX ;
		m_fDirection = -m_fDirection ;
	}

	const float x = (fWinWidth - m_Position.x) ;
	m_pBoss->SetPosition(m_Position) ;
	m_pBoss2->SetPosition(x, m_Position.y) ;

	if(m_moveVector.x<600.0f && m_fTime>=2.0f)
		Acceleration() ;
}

void CPattern_Irregular61::Acceleration()
{
	m_moveVector.x += 100.0f ;
	m_fTime -= 2.0f ;

	if(m_moveVector.x==500.0f)
		g_MusicManager->PlayMusic(m_pSound[0], 1) ;
	else if(m_moveVector.x==600.0f)
		g_MusicManager->PlayMusic(m_pSound[1], 1) ;
}