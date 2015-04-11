#include "Lazer.h"
#include "Sprite.h"

#include "D3dDevice.h"

CLazer::CLazer() : m_LazerPosition(), m_endLazerPosition(),
				   m_LazerVector(),
				   m_fLength(0.0f), m_fDegree(0.0f),
				   m_fTime(0.0f)
{
}
CLazer::~CLazer()
{
}

void CLazer::Init()
{
	m_pSprite = new CSprite ;
	m_pSprite->Init("Resource/Image/Boss/obj_bss3_03.png") ;
	m_pSprite->SetCenterPosition(0.5f, 1.0f) ;
	m_pSprite->SetScale(0.0f, 0.0f) ;
}

void CLazer::SetLazerPosition(POSITION startPosition, POSITION endPosition)
{
	m_LazerPosition = startPosition ;
	m_endLazerPosition = endPosition ;
	m_LazerVector = m_endLazerPosition - m_LazerPosition ;
	m_LazerVector = (m_LazerVector / abs(m_LazerVector.x)) * 300.0f ;
	
	Degree() ;
	Length() ;
}

void CLazer::SetLazerPosition(float startX, float startY, float endX, float endY)
{
	POSITION startPosition(startX, startY) ;
	POSITION endPosition(endX, endY) ;

	SetLazerPosition(startPosition, endPosition) ;
}

void CLazer::Update()
{
	if(m_fTime<=0.5f)
		Shoot() ;
	else
		Move() ;

	m_fTime += g_D3dDevice->GetTime() ;
}

void CLazer::Shoot()
{
	m_pSprite->SetAngle(m_fDegree) ;
	m_pSprite->SetScale(1.0f, m_fLength * (m_fTime/0.5f)) ;
}

void CLazer::Move()
{
	m_LazerPosition += (m_LazerVector * g_D3dDevice->GetTime()) ;
	if(	(m_LazerVector.x>=0 && (m_LazerPosition.x>m_endLazerPosition.x)) ||
		(m_LazerVector.x<0 && (m_LazerPosition.x<m_endLazerPosition.x)) )
		m_LazerPosition.x = m_endLazerPosition.x ;
	Degree() ;
	Length() ;

	m_pSprite->SetAngle(m_fDegree) ;
	m_pSprite->SetScale(1.0f, m_fLength) ;
}

void CLazer::Degree()
{
	float dx = m_LazerPosition.x - m_Position.x ;
	float dy = m_LazerPosition.y - m_Position.y ;

	float radius = atan2(dy, dx) ;
	m_fDegree = (radius * 180.0f) / D3DX_PI ;
	m_fDegree += 90.0f ;
}

void CLazer::Length()
{
	POSITION temp = m_Position - m_LazerPosition ;

	float squareX = temp.x * temp.x ;
	float squareY = temp.y * temp.y ;
	m_fLength = sqrt(squareX + squareY) / 245.0f ;
}