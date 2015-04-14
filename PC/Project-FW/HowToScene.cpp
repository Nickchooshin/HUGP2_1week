#include "HowToScene.h"
#include "GameScene.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "Sprite.h"
#include "CameraManager.h"
#include "MusicManager.h"
#include "SceneManager.h"
#include "TextureManager.h"

#include "D3dDevice.h"

HowToScene::HowToScene() : m_pHowToPlay(NULL),
						   m_pSESelect(NULL)
{
}
HowToScene::~HowToScene()
{
	if(m_pHowToPlay!=NULL)
		delete m_pHowToPlay ;
	
	g_TextureManager->ClearTexture() ;
}

Scene* HowToScene::scene()
{
	Scene *scene = new HowToScene ;

	return scene ;
}

void HowToScene::Init()
{
	g_CameraManager->AddCamera(new CCamera()) ;

	const float fWinWidth = g_D3dDevice->GetWinWidth() ;
	const float fWinHeight = g_D3dDevice->GetWinHeight() ;

	m_pHowToPlay = new CSprite ;
	m_pHowToPlay->Init("Resource/Image/HowTo/htp_bg.jpg") ;
	m_pHowToPlay->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;
	
	m_pSESelect = g_MusicManager->LoadMusic("Resource/Sound/SE/SE_select.mp3", false, false) ;
}

void HowToScene::Destroy()
{
	g_MusicManager->StopMusic() ;
}

void HowToScene::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	if(g_Keyboard->IsPressDown(DIK_RETURN))
	{
		g_MusicManager->PlayMusic(m_pSESelect, 1) ;

		g_SceneManager->ChangeScene(GameScene::scene()) ;
	}
}

void HowToScene::Render()
{
	g_CameraManager->CameraRun() ;

	m_pHowToPlay->Render() ;
}