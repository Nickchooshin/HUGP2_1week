#include "Return.h"
#include "Boss.h"

#include "D3dDevice.h"
#include "BossManager.h"

CReturn::CReturn() : m_pBoss(NULL),
					 m_Position(),
					 m_startPosition(), m_endPosition(),
					 m_moveVector(),
					 m_fTime(0.0f),
					 m_State(FORWARD)
{
}
CReturn::~CReturn()
{
	if(m_pBoss!=NULL)
		delete m_pBoss ;
}

void CReturn::Init()
{
	m_pBoss = g_BossManager->GetBossInstance("obj6") ;
}

void CReturn::SetRoute(POSITION startPosition, POSITION endPosition)
{
	m_startPosition = startPosition ;
	m_endPosition = endPosition ;

	m_Position = m_startPosition ;
	m_moveVector = m_endPosition - m_startPosition ;
}

void CReturn::SetRoute(float startX, float startY, float endX, float endY)
{
	POSITION startPosition(startX, startY) ;
	POSITION endPosition(endX, endY) ;

	SetRoute(startPosition, endPosition) ;
}

bool CReturn::BeLife() const
{
	return (m_State==END) ;
}

void CReturn::Update()
{
	float distance ;

	m_fTime += g_D3dDevice->GetTime() ;
	distance = (m_fTime / 0.3f) ;
	if(distance>1.0f)
		distance = 1.0f ;

	m_pBoss->SetPosition(m_Position + (m_moveVector * distance)) ;

	if(m_fTime>=0.3f)
	{
		if(m_State==FORWARD)
		{
			m_fTime = 0.0f ;
			m_State = RETURN ;
			m_Position = m_endPosition ;
			m_moveVector = m_startPosition - m_endPosition ;
		}
		else if(m_State==RETURN)
		{
			m_State = END ;
		}
	}
}

void CReturn::Render()
{
	m_pBoss->Render() ;
}