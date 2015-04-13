#include "GameScene.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "Sprite.h"
#include "CameraManager.h"
#include "MusicManager.h"
#include "SceneManager.h"
#include "TextureManager.h"

#include "Count.h"
#include "Hero.h"
#include "BossManager.h"
#include "CollisionManager.h"
#include "PatternQueueManager.h"

#include "D3dDevice.h"

GameScene::GameScene() : m_pBackground(NULL),
						 m_pBottom(NULL), m_pScore(NULL), m_pText(NULL),
						 m_fTime(0.0f),
						 m_fTextX(0.0f), m_fTextY(0.0f), m_fTextDirection(1.0f),
						 m_pBGM(NULL),
						 m_pfnLoop(NULL)
{
}
GameScene::~GameScene()
{
	if(m_pBackground!=NULL)
		delete m_pBackground ;
	if(m_pBottom!=NULL)
		delete m_pBottom ;
	if(m_pScore!=NULL)
		delete m_pScore ;
	if(m_pText!=NULL)
		delete m_pText ;

	if(m_pCount!=NULL)
		delete m_pCount ;
	
	g_CollisionManager->DeleteAllObjects() ;
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
	m_pBackground->Init("Resource/Image/Game/play_bg.jpg") ;
	m_pBackground->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;

	m_pBottom = new CSprite ;
	m_pBottom->Init("Resource/Image/Game/play_btm.png") ;
	m_pBottom->SetPosition(fWinWidth / 2.0f, fWinHeight - 678.0f) ;
	
	m_pScore = new CSprite ;
	m_pScore->Init("Resource/Image/Game/play_ui.png") ;
	m_pScore->SetPosition(fWinWidth / 2.0f, fWinHeight - 153.0f) ;
	
	m_pText = new CSprite ;
	m_pText->Init("Resource/Image/Game/play_txt.png") ;
	m_fTextX = (fWinWidth / 2.0f) - 110.0f ;
	m_fTextY = (fWinHeight / 2.0f) ;
	m_pText->SetPosition(m_fTextX, m_fTextY) ;

	m_pCount = new CCount ;
	m_pCount->Init() ;
	m_pCount->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;

	g_Hero->Init() ;
	g_Hero->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;

	m_pfnLoop = &GameScene::Count ;

	g_BossManager->SetupBoss("Boss3") ;
	g_PatternQueueManager->LoadScript("Boss3_Pattern1") ;

	m_pBGM = g_MusicManager->LoadMusic("Resource/Sound/BGM-Play.mp3", true, true) ;

	g_MusicManager->PlayMusic(m_pBGM) ;
}

void GameScene::Destroy()
{
	g_MusicManager->StopMusic() ;
	g_MusicManager->StopMusic(1) ;
}

void GameScene::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	BackgroundTextMoving() ;

	(this->*m_pfnLoop)() ;
}

void GameScene::Render()
{
	g_CameraManager->CameraRun() ;

	m_pBackground->Render() ;
	m_pText->Render() ;
	m_pScore->Render() ;
	m_pBottom->Render() ;

	g_BossManager->Render() ;

	g_Hero->Render() ;

	if(m_pCount->BeLife())
		m_pCount->Render() ;
}

void GameScene::GameLoop()
{
	if(m_pCount->BeLife())
		m_pCount->Update() ;

	g_Hero->Update() ;

	g_PatternQueueManager->Update() ;
	g_BossManager->Update() ;
	g_CollisionManager->Update() ;
}

void GameScene::Count()
{
	m_pCount->Update() ;

	if(m_fTime>=3.0f)
	{
		m_fTime = 0.0f ;
		m_pfnLoop = &GameScene::GameLoop ;
	}

	m_fTime += g_D3dDevice->GetTime() ;
}

void GameScene::BackgroundTextMoving()
{
	const float fTime = g_D3dDevice->GetTime() ;

	m_fTextX += 55.0f * fTime * m_fTextDirection ;

	if(m_fTextX<=530.0f)
	{
		m_fTextX = 530.0f ;
		m_fTextDirection = 1.0f ;
	}
	else if(m_fTextX>=750.0f)
	{
		m_fTextX = 750.0f ;
		m_fTextDirection = -1.0f ;
	}

	m_pText->SetPosition(m_fTextX, m_fTextY) ;
}