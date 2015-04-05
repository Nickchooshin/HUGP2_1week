#include "Objects.h"
#include "Sprite.h"

CObjects::CObjects() : m_pSprite(NULL),
					   m_BBox(),
					   m_Position()
{
}
CObjects::~CObjects()
{
	if(m_pSprite!=NULL)
		delete m_pSprite ;
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

void CObjects::Update()
{
}

void CObjects::Render()
{
	m_pSprite->SetPosition(m_Position.x, m_Position.y) ;
	m_pSprite->Render() ;
}