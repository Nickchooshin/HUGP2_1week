#include "Pattern_Warning.h"
#include "Boss.h"
#include "Hero.h"

#include "D3dDevice.h"

CPattern_Warning::CPattern_Warning(POSITION startPosition, float stayTime, bool bChase) : CPattern(stayTime),
																						  m_startPosition(startPosition),
																						  m_bChase(bChase)
{
}
CPattern_Warning::~CPattern_Warning()
{
}

void CPattern_Warning::Update()
{
	if(m_bChase)
		m_startPosition.x = g_Hero->GetPosition().x ;
	m_pBoss->SetPosition(m_startPosition) ;

	Time() ;
}