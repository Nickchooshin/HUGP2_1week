#include "PatternCommand_Move.h"
#include "Pattern_Move.h"
#include "BossManager.h"
#include "Hero.h"

CPatternCommand_Move::CPatternCommand_Move(std::string strName, POSITION startPosition, POSITION endPosition, float moveTime) : m_axis(NULL),
																																m_strName(strName),
																																m_startPosition(startPosition), m_endPosition(endPosition),
																																m_fMoveTime(moveTime)
{
}
CPatternCommand_Move::CPatternCommand_Move(char axis, std::string strName, float startAxis, float endAxis, float moveTime) : m_axis(axis),
																															 m_strName(strName),
																															 m_startPosition(), m_endPosition(),
																															 m_fMoveTime(moveTime)
{
	if(m_axis=='X')
	{
		m_startPosition.y = startAxis ;
		m_endPosition.y = endAxis ;
	}
	else if(m_axis=='Y')
	{
		m_startPosition.x = startAxis ;
		m_endPosition.x = endAxis ;
	}
}
CPatternCommand_Move::~CPatternCommand_Move()
{
}

void CPatternCommand_Move::Update()
{
	CPattern *pPattern ;

	if(m_axis=='X')
		m_startPosition.x = m_endPosition.x = g_Hero->GetPosition().x ;
	else if(m_axis=='Y')
		m_startPosition.y = m_endPosition.y = g_Hero->GetPosition().y ;
	
	pPattern = new CPattern_Move(m_startPosition, m_endPosition, m_fMoveTime) ;
	pPattern->SetBoss(g_BossManager->GetBossInstance(m_strName)) ;
	g_BossManager->AddPattern(pPattern) ;

	m_bLife = false ;
}