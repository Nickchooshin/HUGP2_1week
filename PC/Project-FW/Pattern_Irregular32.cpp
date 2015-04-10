#include "Pattern_Irregular32.h"
#include "Boss.h"

#include "D3dDevice.h"
#include "BossManager.h"

CPattern_Irregular32::CPattern_Irregular32() : CPattern(9999.0f),
											   m_nNum(0),
											   m_pfnEvent(&CPattern_Irregular32::EventCreate)
{
}
CPattern_Irregular32::~CPattern_Irregular32()
{
	const int num=m_BossList.size() ;

	for(int i=0; i<num; i++)
		delete m_BossList[i] ;
}

void CPattern_Irregular32::Update()
{
	Time() ;

	(this->*m_pfnEvent)() ;
}

void CPattern_Irregular32::Render()
{
	const int num=m_BossList.size() ;

	for(int i=0; i<num; i++)
		m_BossList[i]->Render() ;
}

void CPattern_Irregular32::EventCreate()
{
	const float fTime = g_D3dDevice->GetTime() ;
	int num=m_BossList.size() ;

	for(int i=0; i<num; i++)
	{
		CBoss *pBoss = m_BossList[i] ;
		POSITION position = pBoss->GetPosition() ;
		position.y -= 200.0f * fTime ;

		if(position.y<=-51.0f)
		{
			m_BossList.erase(m_BossList.begin() + i) ;
			delete pBoss ;
			--i ;
			--num ;
		}
		else
			pBoss->SetPosition(position) ;
	}

	if(m_nNum<3 && m_fTime>=1.0f)
	{
		CreateBoss() ;

		m_fTime = 0.0f ;
		++m_nNum ;
	}
	else if(m_nNum==3 && num==0)
		m_bLife = false ;
}

void CPattern_Irregular32::CreateBoss()
{
	for(int i=0; i<14; i++)
	{
		float width = g_D3dDevice->GetWinWidth() / 5.0f ;
		float width_half = width / 2.0f ;
		float x = (rand()%5) * width + (width/2.0f) ;
		x += (rand()%6-2) * ((width-80)/5) ;
		CBoss *pBoss = g_BossManager->GetBossInstance("obj5") ;
		pBoss->SetPosition(x, 771) ;

		m_BossList.push_back(pBoss) ;
	}
}