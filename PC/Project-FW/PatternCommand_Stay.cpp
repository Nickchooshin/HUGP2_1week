#include "PatternCommand_Stay.h"
#include "Pattern_Stay.h"
#include "BossManager.h"

CPatternCommand_Stay::CPatternCommand_Stay(std::string strName, POSITION stayPosition, float stayTime) : m_strName(strName),
																										 m_stayPosition(stayPosition),
																										 m_fTime(0.0f), m_fStayTime(stayTime)
{
}
CPatternCommand_Stay::~CPatternCommand_Stay()
{
}

void CPatternCommand_Stay::Update()
{
	CPattern *pPattern = new CPattern_Stay(m_stayPosition, m_fStayTime) ;
	pPattern->SetBoss(g_BossManager->GetBossInstance(m_strName)) ;
	g_BossManager->AddPattern(pPattern) ;

	m_bLife = false ;
}