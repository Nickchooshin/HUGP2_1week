#include "SampleScene.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "Sprite.h"
#include "UISprite.h"
#include "CameraManager.h"
#include "MusicManager.h"

const int sprite_max=1000 ;

FMOD::Sound *sound[3] ;

SampleScene::SampleScene() : m_pSprite1(NULL), m_pSprite2(NULL),
							 m_pUISprite1(NULL), m_pUISprite2(NULL)
{
}
SampleScene::~SampleScene()
{
	if(m_pSprite1!=NULL)
		delete m_pSprite1 ;
	if(m_pSprite2!=NULL)
		delete m_pSprite2 ;
	if(m_pUISprite1!=NULL)
		delete m_pUISprite1 ;
	if(m_pUISprite2!=NULL)
		delete m_pUISprite2 ;
}

Scene* SampleScene::scene()
{
	Scene *scene = new SampleScene ;

	return scene ;
}

void SampleScene::Init()
{
	g_CameraManager->AddCamera(new CCamera(), 0) ;
	g_CameraManager->AddCamera(new CCamera(), 1) ;
	g_CameraManager->MovePosition(50.0f, 50.0f, 1) ;

	m_pSprite1 = new CSprite ;
	m_pSprite1->Init(50.0f, 50.0f, "sample_texture.png") ;
	m_pSprite1->SetTextureUV(0.0f, 0.0f, 50.0f, 50.0f) ;
	m_pSprite1->SetPositionZ(0.0f) ;

	m_pUISprite1 = new CUISprite ;
	m_pUISprite1->Init(60.0f, 80.0f, "sample_texture2.png") ;
	m_pUISprite1->Init("sample_texture2.png") ;

	m_pSprite2 = new CSprite ;
	m_pSprite2->Init("sample_texture2.png") ;

	m_pUISprite2 = new CUISprite ;
	m_pUISprite2->Init("sample_texture2.png") ;

	sound[0] = g_MusicManager->LoadMusic("click_1.mp3", false, false) ;
	sound[1] = g_MusicManager->LoadMusic("click_2.mp3", false, false) ;
	sound[2] = g_MusicManager->LoadMusic("eat.mp3", false, false) ;
}

void SampleScene::Destroy()
{
}

void SampleScene::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	static float x=0.0f, y=0.0f ;

	if(g_Keyboard->IsButtonDown(DIK_UP))
	{
		y += 1.5f ;
	}
	if(g_Keyboard->IsButtonDown(DIK_DOWN))
	{
		y -= 1.5f ;
	}
	if(g_Keyboard->IsButtonDown(DIK_RIGHT))
	{
		x += 1.5f ;
	}
	if(g_Keyboard->IsButtonDown(DIK_LEFT))
	{
		x -= 1.5f ;
	}

	if(g_Keyboard->IsButtonDown(DIK_1))
	{
		m_pSprite1->SetTextureUV(0.0f, 0.0f, 50.0f, 50.0f) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_2))
	{
		m_pSprite1->SetTextureUV(50.0f, 0.0f, 100.0f, 50.0f) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_3))
	{
		m_pSprite1->SetTextureUV(0.0f, 50.0f, 50.0f, 100.0f) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_4))
	{
		m_pSprite1->SetTextureUV(50.0f, 50.0f, 100.0f, 100.0f) ;
	}

	if(g_Keyboard->IsButtonDown(DIK_8))
	{
		m_pSprite1->SetPositionZ(-1.0f) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_9))
	{
		m_pSprite1->SetPositionZ(1.0f) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_0))
	{
		m_pSprite1->SetPositionZ(0.0f) ;
	}

	if(g_Keyboard->IsButtonDown(DIK_5))
	{
		m_pUISprite1->SetPositionZ(0.0f) ;
		m_pUISprite2->SetPositionZ(0.0f) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_6))
	{
		m_pUISprite1->SetPositionZ(1.0f) ;
		m_pUISprite2->SetPositionZ(0.0f) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_7))
	{
		m_pUISprite1->SetPositionZ(0.0f) ;
		m_pUISprite2->SetPositionZ(1.0f) ;
	}

	if(g_Keyboard->IsButtonDown(DIK_F1))
	{
		g_CameraManager->SetCamera(0) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_F2))
	{
		g_CameraManager->SetCamera(1) ;
	}
	
	if(g_Mouse->IsMouse(g_Mouse->LBUTTON_DOWN))
	{
		g_MusicManager->PlayMusic(sound[0]) ;
	}
	if(g_Mouse->IsMouse(g_Mouse->RBUTTON_DOWN))
	{
		g_MusicManager->PlayMusic(sound[2]) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_SPACE))
	{
		g_MusicManager->PlayMusic(sound[1]) ;
	}

	/*if(g_Mouse->IsMouse(g_Mouse->LBUTTON_DOWN))
	{
		MessageBox(NULL, "LBUTTON_DOWN", "LBUTTON_DOWN", MB_OK) ;
	}

	if(g_Joystick->IsButtonDown(0))
	{
		MessageBox(NULL, "0 Button", "0 BUtton", MB_OK) ;
	}
	if(g_Joystick->IsButtonDown(1))
	{
		MessageBox(NULL, "1 Button", "1 BUtton", MB_OK) ;
	}
	if(g_Joystick->IsButtonDown(3))
	{
		MessageBox(NULL, "3 Button", "3 BUtton", MB_OK) ;
	}
	if(g_Joystick->IsButtonDown(4))
	{
		MessageBox(NULL, "4 Button", "4 BUtton", MB_OK) ;
	}
	if(g_Joystick->IsAxisMin(1000, 'x'))
	{
		MessageBox(NULL, "X 1000", "X 1000", MB_OK) ;
	}
	if(g_Joystick->IsPov(22500))
	{
		MessageBox(NULL, "POV ก็", "POV ก็", MB_OK) ;
	}*/

	m_pSprite1->SetPosition(x, y) ;
	m_pSprite2->SetPosition(100.0f, 100.0f) ;
	m_pUISprite1->SetPosition(100.0f, 100.0f) ;
	m_pUISprite2->SetPosition(50.0f, 50.0f) ;
}

void SampleScene::Render()
{
	g_CameraManager->CameraRun() ;
	
	m_pSprite1->Render() ;
	m_pUISprite1->Render() ;
	m_pSprite2->Render() ;
	m_pUISprite2->Render() ;
}