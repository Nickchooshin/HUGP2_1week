#include "TitleScene.h"
#include "HowToScene.h"
#include "CreditScene.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "Sprite.h"
#include "CameraManager.h"
#include "MusicManager.h"
#include "SceneManager.h"
#include "TextureManager.h"

#include "D3dDevice.h"

TitleScene::TitleScene() : m_pBackground(NULL),
						   m_nMenuNum(0),
						   m_pBGM(NULL),
						   m_pSEMenu(NULL), m_pSESelect(NULL)
{
}
TitleScene::~TitleScene()
{
	if(m_pBackground!=NULL)
		delete m_pBackground ;

	for(int i=0; i<3; i++)
	{
		if(m_pButton[i]!=NULL)
			delete m_pButton[i] ;
	}

	g_TextureManager->ClearTexture() ;
}

Scene* TitleScene::scene()
{
	Scene *scene = new TitleScene ;

	return scene ;
}

void TitleScene::Init()
{
	g_CameraManager->AddCamera(new CCamera()) ;

	const float fWinWidth = g_D3dDevice->GetWinWidth() ;
	const float fWinHeight = g_D3dDevice->GetWinHeight() ;

	m_pBackground = new CSprite ;
	m_pBackground->Init("Resource/Image/Title/main_bg.jpg") ;
	m_pBackground->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;

	m_pButton[0] = new CSprite ;
	m_pButton[0]->Init(180.0f, 60.0f, "Resource/Image/Title/main_btn_1.png") ;
	m_pButton[0]->SetPosition(1000.0f, fWinHeight - 480.0f) ;
	m_pButton[0]->SetTextureUV(0.0f, 0.0f, 180.0f, 60.0f) ;

	m_pButton[1] = new CSprite ;
	m_pButton[1]->Init(180.0f, 60.0f, "Resource/Image/Title/main_btn_2.png") ;
	m_pButton[1]->SetPosition(1000.0f, fWinHeight - 570.0f) ;
	m_pButton[1]->SetTextureUV(180.0f, 0.0f, 360.0f, 60.0f) ;

	m_pButton[2] = new CSprite ;
	m_pButton[2]->Init(180.0f, 60.0f, "Resource/Image/Title/main_btn_3.png") ;
	m_pButton[2]->SetPosition(1000.0f, fWinHeight - 660.0f) ;
	m_pButton[2]->SetTextureUV(180.0f, 0.0f, 360.0f, 60.0f) ;

	m_pBGM = g_MusicManager->LoadMusic("Resource/Sound/BGM-Main.mp3", true, true) ;
	m_pSEMenu = g_MusicManager->LoadMusic("Resource/Sound/SE/SE_menu.mp3", false, false) ;
	m_pSESelect = g_MusicManager->LoadMusic("Resource/Sound/SE/SE_select.mp3", false, false) ;

	g_MusicManager->PlayMusic(m_pBGM) ;
}

void TitleScene::Destroy()
{
}

void TitleScene::Update(float dt)
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
			g_SceneManager->ChangeScene(HowToScene::scene()) ;
			return ;

		case 1 :
			g_SceneManager->ChangeScene(CreditScene::scene()) ;
			return ;

		case 2 :
			PostQuitMessage(0) ;
			return ;
		}
	}
}

void TitleScene::Render()
{
	g_CameraManager->CameraRun() ;

	m_pBackground->Render() ;

	for(int i=0; i<3; i++)
		m_pButton[i]->Render() ;
}

void TitleScene::MenuSelect()
{
	int prevMenuNum = m_nMenuNum ;

	if(g_Keyboard->IsPressDown(DIK_DOWN))
	{
		if(m_nMenuNum<2)
			++m_nMenuNum ;
	}

	if(g_Keyboard->IsPressDown(DIK_UP))
	{
		if(m_nMenuNum>0)
			--m_nMenuNum ;
	}

	if(m_nMenuNum!=prevMenuNum)
	{
		m_pButton[prevMenuNum]->SetTextureUV(180.0f, 0.0f, 360.0f, 60.0f) ;
		m_pButton[m_nMenuNum]->SetTextureUV(0.0f, 0.0f, 180.0f, 60.0f) ;
		
		g_MusicManager->PlayMusic(m_pSEMenu, 1) ;
	}
}