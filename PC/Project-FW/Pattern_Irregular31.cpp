#include "Pattern_Irregular31.h"
#include "Boss.h"
#include "Lazer.h"

#include "D3dDevice.h"
#include "BossManager.h"

CPattern_Irregular31::CPattern_Irregular31() : CPattern(9999.0f),
											   m_pfnEvent(&CPattern_Irregular31::EventWait)
{
	const float fWinHeight = g_D3dDevice->GetWinHeight() ;

	m_pBoss = g_BossManager->GetBossInstance("obj1") ;
	m_pBoss->SetPosition(646.0f, fWinHeight-402.0f) ;

	for(int i=0; i<2; i++)
	{
		m_pLazer[i] = new CLazer ;
		m_pLazer[i]->Init() ;
	}

	m_pLazer[0]->SetPosition(635.0f, fWinHeight-287.0f) ;
	m_pLazer[0]->SetLazerPosition(27.f, fWinHeight-646.0f, 620.0f, fWinHeight-646.0f) ;
	m_pLazer[1]->SetPosition(726.0f, fWinHeight-292.0f) ;
	m_pLazer[1]->SetLazerPosition(1252.f, fWinHeight-646.0f, 660.0f, fWinHeight-646.0f) ;
}
CPattern_Irregular31::~CPattern_Irregular31()
{
	for(int i=0; i<2; i++)
	{
		if(m_pLazer[i]!=NULL)
			delete m_pLazer[i] ;
	}
}

void CPattern_Irregular31::Update()
{
	Time() ;

	(this->*m_pfnEvent)() ;
}

void CPattern_Irregular31::Render()
{
	m_pBoss->Render() ;

	for(int i=0; i<2; i++)
		m_pLazer[i]->Render() ;
}

void CPattern_Irregular31::EventWait()
{
	if(m_fTime>=2.0f)
	{
		m_pfnEvent = &CPattern_Irregular31::EventShootLazer ;
		(this->*m_pfnEvent)() ;
	}
}

void CPattern_Irregular31::EventShootLazer()
{
	for(int i=0; i<2; i++)
		m_pLazer[i]->Update() ;

	if(m_fTime>=3.7f)
	{
		m_pfnEvent = &CPattern_Irregular31::EventMoveLazer ;
		(this->*m_pfnEvent)() ;
	}
}

void CPattern_Irregular31::EventMoveLazer()
{
	for(int i=0; i<2; i++)
		m_pLazer[i]->Update() ;

	if(m_fTime>=6.0f)
		m_bLife = false ;
}