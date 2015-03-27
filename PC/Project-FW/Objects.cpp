#include "Objects.h"
#include "Sprite.h"

CObjects::CObjects() : m_pSprite(NULL),
					   m_BBox(),
					   m_fX(0.0f), m_fY(0.0f)
{
}
CObjects::~CObjects()
{
	if(m_pSprite!=NULL)
		delete m_pSprite ;
}

void CObjects::SetPosition(float X, float Y)
{
	m_fX = X ;
	m_fY = Y ;
}

void CObjects::Update()
{
}

void CObjects::Render()
{
	m_pSprite->SetPosition(m_fX, m_fY) ;
	m_pSprite->Render() ;
}