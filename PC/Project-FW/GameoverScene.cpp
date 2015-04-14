#include "GameoverScene.h"
#include "TitleScene.h"
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
#include "ScoreUI.h"

#include "D3dDevice.h"

GameoverScene::GameoverScene() : m_pBackground(NULL),
								 m_pRank(NULL), m_pText(NULL),
								 m_pScoreUI(NULL),
								 m_nMenuNum(0),
								 m_pSEMenu(NULL), m_pSESelect(NULL)
{
	for(int i=0; i<2; i++)
		m_pButton[i] = NULL ;
}
GameoverScene::~GameoverScene()
{
	if(m_pBackground!=NULL)
		delete m_pBackground ;

	for(int i=0; i<2; i++)
		delete m_pButton[i] ;

	if(m_pRank!=NULL)
		delete m_pRank ;
	if(m_pText!=NULL)
		delete m_pText ;
	if(m_pScoreUI!=NULL)
		delete m_pScoreUI ;
}

Scene* GameoverScene::scene()
{
	Scene *scene = new GameoverScene ;

	return scene ;
}

void GameoverScene::Init()
{
	g_CameraManager->AddCamera(new CCamera()) ;

	const float fWinWidth = g_D3dDevice->GetWinWidth() ;
	const float fWinHeight = g_D3dDevice->GetWinHeight() ;

	m_pBackground = new CSprite ;
	m_pBackground->Init("Resource/Image/Gameover/rst_bg.jpg") ;
	m_pBackground->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;

	for(int i=0; i<2; i++)
	{
		char filename[100] ;
		sprintf_s(filename, "Resource/Image/Gameover/rst_btn_%d.png", i+1) ;

		m_pButton[i] = new CSprite ;
		m_pButton[i]->Init(260.0f, 80.0f, filename) ;
		m_pButton[i]->SetPosition(1100.0f, fWinHeight - (520.0f + (i * 120.0f))) ;
		m_pButton[i]->SetTextureUV(0.0f, (i * 80.0f), 260.0f, ((i+1) * 80.0f)) ;
	}
	
	m_pRank = new CSprite ;
	m_pRank->Init(226.0f, 183.0f, "Resource/Image/Gameover/rst_rank.png") ;
	m_pRank->SetPosition(312.0f, fWinHeight - 380.0f) ;
	const int rank = g_Hero->GetRank() ;
	if(rank==0)
		m_pRank->SetTextureUV(452.0f, 366.0f, 678.0f, 549.0f) ;
	else if(rank==1)
		m_pRank->SetTextureUV(226.0f, 366.0f, 452.0f, 549.0f) ;
	else if(rank==2)
		m_pRank->SetTextureUV(0.0f, 366.0f, 226.0f, 549.0f) ;
	else if(rank==3)
		m_pRank->SetTextureUV(452.0f, 183.0f, 678.0f, 366.0f) ;
	else if(rank==4)
		m_pRank->SetTextureUV(226.0f, 183.0f, 452.0f, 366.0f) ;
	else if(rank==5)
		m_pRank->SetTextureUV(0.0f, 183.0f, 226.0f, 366.0f) ;
	else if(rank==6)
		m_pRank->SetTextureUV(452.0f, 0.0f, 678.0f, 183.0f) ;
	else if(rank==7)
		m_pRank->SetTextureUV(226.0f, 0.0f, 452.0f, 183.0f) ;
	else if(rank==8)
		m_pRank->SetTextureUV(0.0f, 0.0f, 226.0f, 183.0f) ;

	m_pText = new CSprite ;
	m_pText->Init(506.0f, 194.0f, "Resource/Image/Gameover/rst_txt.png") ;
	m_pText->SetPosition(965.0f, fWinHeight - 164.0f) ;
	if(rank==8)
		m_pText->SetTextureUV(0.0f, 194.0f, 506.0f, 388.0f) ;
	else
		m_pText->SetTextureUV(0.0f, 0.0f, 506.0f, 194.0f) ;

	m_pScoreUI = new CScoreUI ;
	m_pScoreUI->Init(1) ;
	m_pScoreUI->SetPosition(650.0f, fWinHeight - 488.0f) ;
	m_pScoreUI->Update() ;
	
	m_pSEMenu = g_MusicManager->LoadMusic("Resource/Sound/SE/SE_menu.mp3", false, false) ;
	m_pSESelect = g_MusicManager->LoadMusic("Resource/Sound/SE/SE_select.mp3", false, false) ;
}

void GameoverScene::Destroy()
{
	g_MusicManager->StopMusic() ;
}

void GameoverScene::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	MenuSelect() ;

	if(g_Keyboard->IsPressDown(DIK_RETURN))
	{
		g_MusicManager->PlayMusic(m_pSESelect, 1) ;

		switch(m_nMenuNum)
		{
		case 0 :
			g_SceneManager->ChangeScene(GameScene::scene()) ;
			return ;

		case 1 :
			g_SceneManager->ChangeScene(TitleScene::scene()) ;
			return ;

		case 2 :
			PostQuitMessage(0) ;
			return ;
		}
	}
}

void GameoverScene::Render()
{
	g_CameraManager->CameraRun() ;

	m_pBackground->Render() ;

	for(int i=0; i<2; i++)
		m_pButton[i]->Render() ;

	m_pRank->Render() ;
	m_pScoreUI->Render() ;
	m_pText->Render() ;
}

void GameoverScene::MenuSelect()
{
	int prevMenuNum = m_nMenuNum ;

	if(g_Keyboard->IsPressDown(DIK_DOWN))
	{
		if(m_nMenuNum<1)
			++m_nMenuNum ;
	}

	if(g_Keyboard->IsPressDown(DIK_UP))
	{
		if(m_nMenuNum>0)
			--m_nMenuNum ;
	}

	if(m_nMenuNum!=prevMenuNum)
	{
		m_pButton[prevMenuNum]->SetTextureUV(0.0f, 80.0f, 260.0f, 160.0f) ;
		m_pButton[m_nMenuNum]->SetTextureUV(0.0f, 0.0f, 260.0f, 80.0f) ;
		
		g_MusicManager->PlayMusic(m_pSEMenu, 1) ;
	}
}