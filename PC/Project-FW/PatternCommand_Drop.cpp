#include "PatternCommand_Drop.h"
#include "Pattern_Drop.h"
#include "BossManager.h"
#include "Hero.h"

CPatternCommand_Drop::CPatternCommand_Drop(std::string strName, POSITION startPosition, POSITION endPosition, float moveTime, float stayTime) : m_axis(NULL),
																																				m_strName(strName),
																																				m_startPosition(startPosition), m_endPosition(endPosition),
																																				m_fMoveTime(moveTime), m_fStayTime(stayTime)
{
}
CPatternCommand_Drop::CPatternCommand_Drop(char axis, std::string strName, float startAxis, float endAxis, float moveTime, float stayTime) : m_axis(axis),
																																			 m_strName(strName),
																																			 m_startPosition(), m_endPosition(),
																																			 m_fMoveTime(moveTime), m_fStayTime(stayTime)
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
CPatternCommand_Drop::~CPatternCommand_Drop()
{
}

void CPatternCommand_Drop::Update()
{
	CPattern *pPattern ;

	if(m_axis=='X')
		m_startPosition.x = m_endPosition.x = g_Hero->GetPosition().x ;
	else if(m_axis=='Y')
		m_startPosition.y = m_endPosition.y = g_Hero->GetPosition().y ;
	
	pPattern = new CPattern_Drop(m_startPosition, m_endPosition, m_fMoveTime, m_fStayTime) ;
	pPattern->SetBoss(g_BossManager->GetBossInstance(m_strName)) ;
	g_BossManager->AddPattern(pPattern) ;

	m_bLife = false ;
}