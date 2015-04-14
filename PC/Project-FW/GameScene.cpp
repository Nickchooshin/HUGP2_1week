#include "GameScene.h"
#include "TitleScene.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "Sprite.h"
#include "CameraManager.h"
#include "MusicManager.h"
#include "SceneManager.h"
#include "TextureManager.h"

#include "CountUI.h"
#include "ScoreUI.h"
#include "Hero.h"
#include "BossManager.h"
#include "CollisionManager.h"
#include "PatternQueueManager.h"

#include "D3dDevice.h"

GameScene::GameScene() : m_pBackground(NULL),
						 m_pBottom(NULL), m_pText(NULL),
						 m_pCountUI(NULL),
						 m_pScoreUI(NULL),
						 m_fTime(0.0f),
						 m_fTextX(0.0f), m_fTextY(0.0f), m_fTextDirection(1.0f),
						 m_nBossNum(1), m_nPatternNum(1),
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
	if(m_pText!=NULL)
		delete m_pText ;

	if(m_pCountUI!=NULL)
		delete m_pCountUI ;
	if(m_pScoreUI!=NULL)
		delete m_pScoreUI ;
	
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
	
	m_pText = new CSprite ;
	m_pText->Init("Resource/Image/Game/play_txt.png") ;
	m_fTextX = (fWinWidth / 2.0f) - 110.0f ;
	m_fTextY = (fWinHeight / 2.0f) + 10.0f ;
	m_pText->SetPosition(m_fTextX, m_fTextY) ;

	m_pCountUI = new CCountUI ;
	m_pCountUI->Init() ;
	m_pCountUI->SetPosition(fWinWidth / 2.0f, fWinHeight - 153.0f) ;

	m_pScoreUI = new CScoreUI ;
	m_pScoreUI->Init() ;
	m_pScoreUI->SetPosition(fWinWidth / 2.0f, fWinHeight - 153.0f) ;

	g_Hero->Init() ;
	g_Hero->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;

	m_pfnLoop = &GameScene::Count ;

	g_BossManager->SetupBoss("Boss1") ;
	g_PatternQueueManager->LoadScript("Boss1_Pattern1") ;

	m_pBGM = g_MusicManager->LoadMusic("Resource/Sound/BGM-Play.mp3", true, true) ;
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
	m_pScoreUI->Render() ;
	m_pBottom->Render() ;

	g_BossManager->Render() ;

	g_Hero->Render() ;

	if(m_pCountUI->BeLife())
		m_pCountUI->Render() ;
}

void GameScene::GameLoop()
{
	if(m_pCountUI->BeLife())
		m_pCountUI->Update() ;

	g_Hero->Update() ;

	g_PatternQueueManager->Update() ;
	g_BossManager->Update() ;
	g_CollisionManager->Update() ;

	NextPattern() ;
}

void GameScene::Count()
{
	m_pCountUI->Update() ;

	if(!m_pCountUI->BeCount())
	{
		g_MusicManager->PlayMusic(m_pBGM) ;

		m_pfnLoop = &GameScene::GameLoop ;
		(this->*m_pfnLoop)() ;

		printf("%f\n", timeGetTime() * 0.001f) ;
	}
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

void GameScene::NextPattern()
{
	if(g_PatternQueueManager->BeQueueEnd())
	{
		if(m_fTime>=2.0f)
		{
			if(m_nBossNum<4)
			{
				if(m_nPatternNum==3)
				{
					++m_nBossNum ;
					m_nPatternNum = 1 ;

					char boss_name[20] ;
					sprintf_s(boss_name, "Boss%d", m_nBossNum) ;
					g_BossManager->SetupBoss(boss_name) ;
				}
				else
					++m_nPatternNum ;
			}
			else
			{
				if(m_nPatternNum==2)
				{
					++m_nBossNum ;
					m_nPatternNum = 1 ;

					if(m_nBossNum>6)
					{
						printf("%f\n", timeGetTime() * 0.001f) ;
						g_SceneManager->ChangeScene(TitleScene::scene()) ;
						return ;
					}
				
					char boss_name[20] ;
					sprintf_s(boss_name, "Boss%d", m_nBossNum) ;
					g_BossManager->SetupBoss(boss_name) ;
				}
				else
					++m_nPatternNum ;
			}

			char pattern_name[20] ;
			sprintf_s(pattern_name, "Boss%d_Pattern%d", m_nBossNum, m_nPatternNum) ;
			g_PatternQueueManager->LoadScript(pattern_name) ;

			m_fTime = 0.0f ;
		}
		else
			m_fTime += g_D3dDevice->GetTime() ;
	}
}