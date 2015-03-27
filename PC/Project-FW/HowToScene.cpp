#include "HowToScene.h"

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

HowToScene::HowToScene() : m_pHowToPlay(NULL)
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
	m_pHowToPlay->Init("Resource/Image/Dummy/HowToPlay.png") ;
	m_pHowToPlay->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;
}

void HowToScene::Destroy()
{
}

void HowToScene::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	if(g_Keyboard->IsPressDown(DIK_RETURN))
		g_SceneManager->ChangeScene(GameScene::scene()) ;
}

void HowToScene::Render()
{
	g_CameraManager->CameraRun() ;

	m_pHowToPlay->Render() ;
}