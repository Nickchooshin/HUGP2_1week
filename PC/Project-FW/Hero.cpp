#include "Hero.h"
#include "Sprite.h"

#include "Keyboard.h"
#include "DataLoader.h"

#include "D3dDevice.h"

CHero::CHero() : m_fSpeed(430.0f),
				 m_fJump(742.85715f), m_fGravity(2122.449f),
				 m_fYVelocity(0.0f),
				 m_bJump(false)
{
	char item[100] ;
	CDataLoader Data ;
	Data.OpenData("Resource/Data/Hero.dat") ;

	while(Data.GetItem(item))
	{
		if(strcmp(item, "SPEED")==0)
			Data.GetValue(m_fSpeed) ;
		else if(strcmp(item, "JUMP")==0)
			Data.GetValue(m_fJump) ;
		else if(strcmp(item, "GRAVITY")==0)
			Data.GetValue(m_fGravity) ;
	}

	Data.CloseData() ;

	m_pBounding = new BBOX(-20.0f, 20.0f, 20.0f, -20.0f) ;
	m_nBoundingNum = 1 ;
}
CHero::~CHero()
{
}

void CHero::Init()
{
	m_pSprite = new CSprite ;
	m_pSprite->Init(40.0f, 40.0f, "Resource/Image/Dummy/Hero.png") ;
}

void CHero::Dead()
{
}

void CHero::Update()
{
	const float time = g_D3dDevice->GetTime() ;

	if(g_Keyboard->IsPressDown(DIK_Z))
		m_fSpeed = -m_fSpeed ;
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