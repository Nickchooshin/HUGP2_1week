#include "GameoverScene.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "Sprite.h"
#include "CameraManager.h"
#include "MusicManager.h"
#include "SceneManager.h"
#include "TextureManager.h"

#include "D3dDevice.h"

GameoverScene::GameoverScene()
{
}
GameoverScene::~GameoverScene()
{
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
}

void GameoverScene::Destroy()
{
}

void GameoverScene::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;
}

void GameoverScene::Render()
{
	g_CameraManager->CameraRun() ;
}