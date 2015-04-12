/*#include <d3d9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 ) */

#ifdef _DEBUG
#include <crtdbg.h>

#define CRTDBG_MAP_ALLOC
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif

#include "WinSystem.h"
#include "SceneManager.h"
#include "TitleScene.h"

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF) ;
	//_CrtSetBreakAlloc(251) ;
#endif
	CWinSystem WinSystem(hInst) ;

	g_SceneManager->StartScene(TitleScene::scene()) ;

	WinSystem.WinSet("Roads to the A - alpha", WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, 1280, 720) ;	// WS_THICKFRAME - 윈도우창 늘리기/줄이기 크기조정 지원안함.
	WinSystem.WinMsg() ;
	WinSystem.WinEnd() ;

	return 0 ;
}