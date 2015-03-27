#include "TitleScene.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "Sprite.h"
#include "CameraManager.h"
#include "MusicManager.h"
#include "SceneManager.h"
#include "TextureManager.h"

#include "HowToScene.h"

#include "D3dDevice.h"

TitleScene::TitleScene() : m_pBackground(NULL),
						   m_pStart(NULL), m_pGrade(NULL), m_pCredit(NULL), m_pExit(NULL),
						   m_pPointer(NULL),
						   m_nMenuNum(0)
{
}
TitleScene::~TitleScene()
{
	if(m_pBackground!=NULL)
		delete m_pBackground ;

	if(m_pStart!=NULL)
		delete m_pStart ;
	if(m_pGrade!=NULL)
		delete m_pGrade ;
	if(m_pCredit!=NULL)
		delete m_pCredit ;
	if(m_pExit!=NULL)
		delete m_pExit ;

	if(m_pPointer!=NULL)
		delete m_pPointer ;

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
	m_pBackground->Init("Resource/Image/Dummy/Title_Background.png") ;
	m_pBackground->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;

	m_pStart = new CSprite ;
	m_pStart->Init("Resource/Image/Dummy/TitleButton/Start.png") ;
	m_pStart->SetPosition(fWinWidth / 2.0f, fWinHeight - 450.0f) ;

	m_pGrade = new CSprite ;
	m_pGrade->Init("Resource/Image/Dummy/TitleButton/Grade.png") ;
	m_pGrade->SetPosition(fWinWidth / 2.0f, fWinHeight - 520.0f) ;

	m_pCredit = new CSprite ;
	m_pCredit->Init("Resource/Image/Dummy/TitleButton/Credit.png") ;
	m_pCredit->SetPosition(fWinWidth / 2.0f, fWinHeight - 590.0f) ;

	m_pExit = new CSprite ;
	m_pExit->Init("Resource/Image/Dummy/TitleButton/Exit.png") ;
	m_pExit->SetPosition(fWinWidth / 2.0f, fWinHeight - 660.0f) ;

	m_pPointer = new CSprite ;
	m_pPointer->Init("Resource/Image/Dummy/TitleButton/Pointer.png") ;
	m_pPointer->SetPosition(fWinWidth / 2.0f, fWinHeight - 450.0f) ;
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
		switch(m_nMenuNum)
		{
		case 0 :
			g_SceneManager->ChangeScene(HowToScene::scene()) ;
			return ;
		}
	}
}

void TitleScene::Render()
{
	g_CameraManager->CameraRun() ;

	m_pBackground->Render() ;

	m_pStart->Render() ;
	m_pGrade->Render() ;
	m_pCredit->Render() ;
	m_pExit->Render() ;

	m_pPointer->Render() ;
}

void TitleScene::MenuSelect()
{
	int prevMenuNum = m_nMenuNum ;

	if(g_Keyboard->IsPressDown(DIK_DOWN))
	{
		if(m_nMenuNum<3)
			++m_nMenuNum ;
	}

	if(g_Keyboard->IsPressDown(DIK_UP))
	{
		if(m_nMenuNum>0)
			--m_nMenuNum ;
	}

	if(m_nMenuNum!=prevMenuNum)
	{
		const float x = m_pPointer->GetPosition().x ;
		const float fWinHeight = g_D3dDevice->GetWinHeight() ;
		const float PointerY = 70.0f * m_nMenuNum ;

		m_pPointer->SetPosition(x, fWinHeight - (450.0f + PointerY)) ;
	}
}