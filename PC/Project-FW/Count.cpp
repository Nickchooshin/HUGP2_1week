#include "Count.h"
#include "Sprite.h"

#include "MusicManager.h"

#include "D3dDevice.h"

CCount::CCount() : m_pSprite(NULL),
				   m_nNum(-1),
				   m_fTime(0.0f),
				   m_bStart(false), m_bLife(true),
				   m_pSECount(NULL), m_pSEStart(NULL)
{
}
CCount::~CCount()
{
	if(m_pSprite!=NULL)
		delete m_pSprite ;
}

void CCount::Init()
{
	m_pSprite = new CSprite ;
	m_pSprite->Init(520.0f, 160.0f, "Resource/Image/Game/play_c.png") ;
	m_pSprite->SetTextureUV(0.0f, 0.0f, 64.0f, 64.0f) ;

	m_nNum = -1 ;
	m_fTime = 0.0f ;
	m_bStart = false ;
	m_bLife = true ;
	
	m_pSECount = g_MusicManager->LoadMusic("Resource/Sound/SE/SE_count.mp3", false, false) ;
	m_pSEStart = g_MusicManager->LoadMusic("Resource/Sound/SE/SE_start.mp3", false, false) ;
}

void CCount::SetPosition(float x, float y)
{
	m_pSprite->SetPosition(x, y) ;
}

const bool CCount::BeLife() const
{
	return m_bLife ;
}

void CCount::Update()
{
	if(m_bStart)
		m_fTime += g_D3dDevice->GetTime() ;
	else
		m_bStart = true ;

	int num = (int)(m_fTime / 1.0f) ;

	if(m_nNum!=num)
	{
		m_nNum = num ;

		switch(m_nNum)
		{
		case 0 :
			m_pSprite->SetTextureUV(0.0f, 320.0f, 520.0f, 480.0f) ;
			g_MusicManager->PlayMusic(m_pSECount, 1) ;
			break ;

		case 1 :
			m_pSprite->SetTextureUV(0.0f, 160.0f, 520.0f, 320.0f) ;
			g_MusicManager->PlayMusic(m_pSECount, 1) ;
			break ;

		case 2 :
			m_pSprite->SetTextureUV(0.0f, 0.0f, 520.0f, 160.0f) ;
			g_MusicManager->PlayMusic(m_pSECount, 1) ;
			break ;

		case 3 :
			m_pSprite->SetTextureUV(0.0f, 480.0f, 520.0f, 640.0f) ;
			g_MusicManager->PlayMusic(m_pSEStart, 1) ;
			break ;

		case 4 :
			m_bLife = false ;
			break ;
		}
	}
}

void CCount::Render()
{
	m_pSprite->Render() ;
}