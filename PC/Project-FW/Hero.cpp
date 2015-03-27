#include "Hero.h"
#include "Sprite.h"

#include "Keyboard.h"
#include "DataLoader.h"

#include "D3dDevice.h"

CHero::CHero() : m_fSpeed(10.0f),
				 m_fJump(0.0f), m_fGravity(0.0),
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
}
CHero::~CHero()
{
}

void CHero::Init()
{
	m_pSprite = new CSprite ;
	m_pSprite->Init(64.0f, 64.0f, "Resource/Image/Dummy/Hero.png") ;
}

void CHero::Update()
{
	if(g_Keyboard->IsPressDown(DIK_Z))
		m_fSpeed = -m_fSpeed ;
	if(!m_bJump && g_Keyboard->IsPressDown(DIK_X))
	{
		m_fYVelocity = m_fJump ;
		m_bJump = true ;
	}

	m_fX += m_fSpeed ;
	Gravity() ;
}

void CHero::Gravity()
{
	m_fYVelocity -= m_fGravity ;
	m_fY += m_fYVelocity ;

	if(m_fY<32.0f)
	{
		m_fY = 32.0f ;
		m_fYVelocity = 0.0f ;
		m_bJump = false ;
	}
}