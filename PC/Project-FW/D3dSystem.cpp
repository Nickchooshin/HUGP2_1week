#include "D3dSystem.h"
#include "D3dDevice.h"
#include "InputDevice.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"
#include "TextureManager.h"
#include "Sprite.h"
#include "UISprite.h"
#include "Camera.h"
#include "MusicManager.h"

CD3dSystem::CD3dSystem() : m_pD3d(NULL),
						   m_pd3dDevice(NULL)
{
}
CD3dSystem::~CD3dSystem()
{
	if( m_pd3dDevice != NULL )
		m_pd3dDevice->Release();

	if( m_pD3d != NULL )
		m_pD3d->Release();
}

HRESULT CD3dSystem::InitD3d(const HINSTANCE hInst, const HWND hWnd, const int nWidth, const int nHeight, char* ErrorStr)
{
	if( NULL == ( m_pD3d = Direct3DCreate9( D3D_SDK_VERSION ) ) )
	{
		strcpy(ErrorStr, "DirectX를 초기화 하지 못했습니다.") ;
		return E_FAIL;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.BackBufferWidth = nWidth ;			// 백버퍼 넓이
	d3dpp.BackBufferHeight = nHeight ;			// 백버퍼 높이
	d3dpp.Windowed = TRUE ;						// 창모드 유무
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD ;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8 ;	// 백버퍼 포맷	// D3DFMT_UNKNOWN
	d3dpp.BackBufferCount = 1 ;					// 백버퍼 개수
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE ;	// 멀티샘플링 사용 유무
	d3dpp.MultiSampleQuality = 0 ;				// 멀티샘플링(1x 2x 4x 8x ...)
	d3dpp.EnableAutoDepthStencil = true ;		// Direct3D가 깊이버퍼를 만들고 관리한다
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16 ;	// 깊이버퍼의 크기 설정(16bit 정도면 충분히 깊이를 판단 가능)
	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE ; // 모니터 주사율에 따른 수직 동기화 해제
	//

	if( FAILED( m_pD3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_MIXED_VERTEXPROCESSING, &d3dpp, &m_pd3dDevice ) ) )
	{
		//if( FAILED( m_pD3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pd3dDevice ) ) )
		{
			if( FAILED( m_pD3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pd3dDevice ) ) )
			{
				strcpy(ErrorStr, "DirectX 디바이스를 생성하지 못했습니다.") ;
				return E_FAIL;
			}
		}
	}

	m_hInst = hInst ;

	strcpy(ErrorStr, "InputDevice 초기화 실패") ;

	if( !g_InputDevice->InitDevice(hInst, hWnd) )
		return E_FAIL ;
	if( !g_Keyboard->Init() )
		return E_FAIL ;
	if( !g_Mouse->Init() )
		return E_FAIL ;
	g_Joystick->Init() ;
	//if( !g_Joystick->Init() )
	//	return E_FAIL ;

	g_MusicManager->Initialize() ;

	g_D3dDevice->g_pd3dDevice = m_pd3dDevice ;
	g_D3dDevice->WinWidth = nWidth ;
	g_D3dDevice->WinHeight = nHeight ;

	SetRenderState() ;

	return S_OK;
}

LPDIRECT3DDEVICE9 CD3dSystem::GetDevice()
{
	return m_pd3dDevice ;
}

bool CD3dSystem::BeginScene()
{
	m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0 ); // D3DCOLOR_XRGB

	return SUCCEEDED( m_pd3dDevice->BeginScene() ) ;
}

void CD3dSystem::EndScene()
{
	m_pd3dDevice->EndScene() ;
}

void CD3dSystem::Present()
{
	m_pd3dDevice->Present( NULL, NULL, NULL, NULL ) ;
}

void CD3dSystem::SetRenderState()
{
	m_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	m_pd3dDevice->SetRenderState( D3DRS_DITHERENABLE, FALSE ); // 색 혼합법
	m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );	// 광원
	m_pd3dDevice->SetRenderState( D3DRS_SPECULARENABLE, FALSE ); // 재질 광원

	m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE ) ;	// Z버퍼
	m_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE ) ;	// Z버퍼 2D 관련??

	m_pd3dDevice->SetRenderState( D3DRS_ANTIALIASEDLINEENABLE, FALSE ) ;	// 안티앨리어싱 렌더링
}