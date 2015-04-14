#include "CreditScene.h"
#include "TitleScene.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "Sprite.h"
#include "CameraManager.h"
#include "MusicManager.h"
#include "SceneManager.h"
#include "TextureManager.h"

#include "GameScene.h"

#include "D3dDevice.h"

CreditScene::CreditScene() : m_pCredit(NULL)
{
}
CreditScene::~CreditScene()
{
	if(m_pCredit!=NULL)
		delete m_pCredit ;
	
	g_TextureManager->ClearTexture() ;
}

Scene* CreditScene::scene()
{
	Scene *scene = new CreditScene ;

	return scene ;
}

void CreditScene::Init()
{
	g_CameraManager->AddCamera(new CCamera()) ;

	const float fWinWidth = g_D3dDevice->GetWinWidth() ;
	const float fWinHeight = g_D3dDevice->GetWinHeight() ;

	m_pCredit = new CSprite ;
	m_pCredit->Init("Resource/Image/Credit/crd_bg.jpg") ;
	m_pCredit->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;
	
	m_pSESelect = g_MusicManager->LoadMusic("Resource/Sound/SE/SE_select.mp3", false, false) ;
}

void CreditScene::Destroy()
{
}

void CreditScene::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	if(g_Keyboard->IsPressDown(DIK_RETURN))
	{
		g_MusicManager->PlayMusic(m_pSESelect, 1) ;

		g_SceneManager->ChangeScene(TitleScene::scene()) ;
	}
}

void CreditScene::Render()
{
	g_CameraManager->CameraRun() ;

	m_pCredit->Render() ;
}