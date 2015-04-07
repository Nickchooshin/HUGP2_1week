#include "PatternCommand_Warning.h"
#include "Pattern_Warning.h"
#include "BossManager.h"
#include "Hero.h"
#include "Boss.h"

CPatternCommand_Warning::CPatternCommand_Warning(float width, float height, POSITION stayPosition, float stayTime) : m_axis(NULL),
																													 m_fWidth(width), m_fHeight(height),
																													 m_startPosition(stayPosition),
																													 m_fStayTime(stayTime)
{
}
CPatternCommand_Warning::CPatternCommand_Warning(char axis, float width, float height, float stayAxis, float stayTime) : m_axis(axis),
																														 m_fWidth(width), m_fHeight(height),
																														 m_startPosition(),
																														 m_fStayTime(stayTime)
{
	if(m_axis=='X')
		m_startPosition.y = stayAxis ;
	else if(m_axis=='Y')
		m_startPosition.x = stayAxis ;
}
CPatternCommand_Warning::CPatternCommand_Warning(float width, float height, float stayAxis, float stayTime) : m_axis('C'),
																											  m_fWidth(width), m_fHeight(height),
																											  m_startPosition(),
																											  m_fStayTime(stayTime)
{
	m_startPosition.y = stayAxis ;
}
CPatternCommand_Warning::~CPatternCommand_Warning()
{
}

void CPatternCommand_Warning::Update()
{
	CPattern *pPattern ;
	bool bChase=false ;

	if(m_axis=='X')
		m_startPosition.x = g_Hero->GetPosition().x ;
	else if(m_axis=='Y')
		m_startPosition.y = g_Hero->GetPosition().y ;
	else if(m_axis=='C')
		bChase = true ;

	CBoss *pBoss = new CBoss ;
	pBoss->Init() ;
	pBoss->SetImage(m_fWidth, m_fHeight, "Resource/Image/Warning.png") ;
	pPattern = new CPattern_Warning(m_startPosition, m_fStayTime, bChase) ;
	pPattern->SetBoss(pBoss) ;
	g_BossManager->AddPattern(pPattern) ;

	m_bLife = false ;
}