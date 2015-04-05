#include "PatternCommand_Move.h"
#include "Pattern_Move.h"
#include "BossManager.h"

CPatternCommand_Move::CPatternCommand_Move(std::string strName, POSITION startPosition, POSITION endPosition, float moveTime) : m_strName(strName),
																																m_startPosition(startPosition), m_endPosition(endPosition),
																																m_fTime(0.0f), m_fMoveTime(moveTime)
{
}
CPatternCommand_Move::~CPatternCommand_Move()
{
}

void CPatternCommand_Move::Update()
{
	CPattern *pPattern = new CPattern_Move(m_startPosition, m_endPosition, m_fMoveTime) ;
	pPattern->SetBoss(g_BossManager->GetBossInstance(m_strName)) ;
	g_BossManager->AddPattern(pPattern) ;

	m_bLife = false ;
}