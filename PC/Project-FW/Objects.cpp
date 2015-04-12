#include "Objects.h"
#include "Sprite.h"

CObjects::CObjects() : m_pSprite(NULL),
					   m_pBounding(NULL),
					   m_Position(),
					   m_bCollision(true)
{
}
CObjects::~CObjects()
{
	if(m_pSprite!=NULL)
		delete m_pSprite ;
	if(m_pBounding!=NULL)
		delete m_pBounding ;
}

void CObjects::SetPosition(POSITION Position)
{
	m_Position = Position ;
}

void CObjects::SetPosition(float x, float y)
{
	m_Position.x = x ;
	m_Position.y = y ;
}

void CObjects::SetBounding(IBounding *pBounding)
{
	m_pBounding = pBounding ;
}

void CObjects::SetCollision(bool bCollision)
{
	m_bCollision = bCollision ;
}

POSITION CObjects::GetPosition() const
{
	return m_Position ;
}

IBounding* CObjects::GetBounding() const
{
	return m_pBounding ;
}

bool CObjects::BeCollision() const
{
	return m_bCollision ;
}

void CObjects::Update()
{
}

void CObjects::Render()
{
	m_pSprite->SetPosition(m_Position.x, m_Position.y) ;
	m_pSprite->Render() ;
}