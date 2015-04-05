#include "GameScene.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "Sprite.h"
#include "CameraManager.h"
#include "MusicManager.h"
#include "SceneManager.h"
#include "TextureManager.h"

#include "Hero.h"
#include "BossManager.h"
#include "PatternQueueManager.h"

#include "D3dDevice.h"

GameScene::GameScene() : m_pBackground(NULL),
						 m_pHero(NULL),
						 m_fTime(0.0f),
						 m_pfnLoop(NULL)
{
}
GameScene::~GameScene()
{
	if(m_pBackground!=NULL)
		delete m_pBackground ;

	if(m_pHero!=NULL)
		delete m_pHero ;

	if(m_pCount!=NULL)
		delete m_pCount ;
	
	g_TextureManager->ClearTexture() ;
}

Scene* GameScene::scene()
{
	Scene *scene = new GameScene ;

	return scene ;
}

void GameScene::Init()
{
	g_CameraManager->AddCamera(new CCamera()) ;

	const float fWinWidth = g_D3dDevice->GetWinWidth() ;
	const float fWinHeight = g_D3dDevice->GetWinHeight() ;

	m_pBackground = new CSprite ;
	m_pBackground->Init("Resource/Image/Dummy/Background.png") ;
	m_pBackground->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;

	m_pCount = new CSprite ;
	m_pCount->Init(64.0f, 64.0f, "Resource/Image/Dummy/Count.png") ;
	m_pCount->SetTextureUV(0.0f, 0.0f, 64.0f, 64.0f) ;
	m_pCount->SetScale(2.0f, 2.0f) ;
	m_pCount->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;

	m_pHero = new CHero ;
	m_pHero->Init() ;
	m_pHero->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;

	m_pfnLoop = &GameScene::Count ;

	g_BossManager->SetupBoss("Boss1") ;
	g_PatternQueueManager->LoadScript("Boss1_Pattern3") ;
}

void GameScene::Destroy()
{
}

void GameScene::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	(this->*m_pfnLoop)() ;
}

void GameScene::Render()
{
	g_CameraManager->CameraRun() ;

	m_pBackground->Render() ;

	m_pHero->Render() ;

	m_pCount->Render() ;

	g_BossManager->Render() ;
}

void GameScene::Count()
{
	int time = (int)m_fTime ;

	switch(time)
	{
	case 0 :
		m_pCount->SetTextureUV(0.0f, 0.0f, 64.0f, 64.0f) ;
		break ;

	case 1 :
		m_pCount->SetTextureUV(64.0f, 0.0f, 128.0f, 64.0f) ;
		break ;

	case 2 :
		m_pCount->SetTextureUV(0.0f, 64.0f, 64.0f, 128.0f) ;
		break ;

	case 3 :
		m_pCount->SetTextureUV(64.0f, 64.0f, 128.0f, 128.0f) ;
		m_fTime = 0.0f ;
		m_pfnLoop = &GameScene::GameLoop ;
		return ;
	}

	m_fTime += g_D3dDevice->GetTime() ;
}

void GameScene::GameLoop()
{
	m_pHero->Update() ;

	g_PatternQueueManager->Update() ;
	g_BossManager->Update() ;
}