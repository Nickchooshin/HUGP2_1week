#include "Hero.h"
#include "Sprite.h"

#include "Keyboard.h"
#include "DataLoader.h"

#include "D3dDevice.h"

CHero::CHero() : m_fSpeed(320.0f),
				 m_fJump(742.85715f), m_fGravity(2122.449f),
				 m_fYVelocity(0.0f),
				 m_bJump(false), m_bDead(false),
				 m_lStartTime(0), m_lEndTime(0),
				 m_bStart(false)
{
	m_pSprite = new CSprite ;
	m_pSprite->Init("Resource/Image/Game/chr.png") ;

	m_pBounding = new BBOX(-20.0f, 20.0f, 20.0f, -20.0f) ;
	m_nBoundingNum = 1 ;
}
CHero::~CHero()
{
}

void CHero::Init()
{
	m_fYVelocity = 0.0f ;
	m_bJump = false ;
	m_bDead = false ;
	m_lStartTime = 0 ;
	m_lEndTime = 0;
	m_bStart = false ;
}

const int CHero::GetScore() const
{
	float time = (float)(m_lEndTime - m_lStartTime) * 0.001f ;
	int score = (int)((time / 144.260833f) * 10000.0f) ;

	return score ;
}

const int CHero::GetRank() const
{
	float time = (float)(m_lEndTime - m_lStartTime) * 0.001f ;
	int percent = (int)((time / 144.260833f) * 100.0f) ;
	int rank ;

	if(percent<=9)
		rank = 0 ;
	else if(percent<=19)
		rank = 1 ;
	else if(percent<=29)
		rank = 2 ;
	else if(percent<=39)
		rank = 3 ;
	else if(percent<=49)
		rank = 4 ;
	else if(percent<=59)
		rank = 5 ;
	else if(percent<=72)
		rank = 6 ;
	else if(percent<=99)
		rank = 7 ;
	else
		rank = 8 ;

	return rank ;
}

const bool CHero::BeDead() const
{
	return m_bDead ;
}

void CHero::Dead()
{
	m_bDead = true ;
}

void CHero::Clear()
{
	m_lEndTime = m_lStartTime + 144261 ;
}

void CHero::Update()
{
	const float time = g_D3dDevice->GetTime() ;

	if(g_Keyboard->IsPressDown(DIK_Z))
	{
		m_fSpeed = -m_fSpeed ;
		m_pSprite->TexReverse() ;
	}
	if(!m_bJump && g_Keyboard->IsPressDown(DIK_X))
	{
		m_fYVelocity = m_fJump ;
		m_bJump = true ;
	}

	m_Position.x += (m_fSpeed * time) ;
	if(m_Position.x<20.0f)
		m_Position.x = 20.0f ;
	else if(m_Position.x>1260.0f)
		m_Position.x = 1260.0f ;
	Gravity() ;

	if(!m_bStart)
	{
		m_lStartTime = timeGetTime() ;
		m_lEndTime = m_lStartTime ;
		m_bStart = true ;
	}
	else
		m_lEndTime = timeGetTime() ;
}

void CHero::Gravity()
{
	const float time = g_D3dDevice->GetTime() ;
	m_fYVelocity -= m_fGravity * time ;
	m_Position.y += m_fYVelocity * time ;

	if(m_Position.y<98.0f)
	{
		m_Position.y = 98.0f ;
		m_fYVelocity = 0.0f ;
		m_bJump = false ;
	}
}