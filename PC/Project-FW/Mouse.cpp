#include "Mouse.h"
#include "InputDevice.h"

#include "D3dDevice.h"

Mouse::Mouse() : m_pDIDMouse(NULL),
				 MousePoint()
{
}
Mouse::~Mouse()
{
	if(m_pDIDMouse!=NULL)
	{
		m_pDIDMouse->Unacquire() ;
		m_pDIDMouse->Release() ;
		m_pDIDMouse = NULL ;
	}
}

bool Mouse::Init()
{
	// 마우스 DirectInputDevice 초기화
	if( FAILED( g_InputDevice->m_pDInput->CreateDevice( GUID_SysMouse, &m_pDIDMouse, NULL ) ) )
	{
		MessageBox(NULL, "Mouse CreateDevice Fail", "Error", MB_OK) ;
		return false ;
	}

	// 마우스 DirectInputDevice 포멧 설정
	if( FAILED( m_pDIDMouse->SetDataFormat( &c_dfDIMouse ) ) )
	{
		MessageBox(NULL, "Mouse SetDataFormat Fail", "Error", MB_OK) ;
		return false ;
	}

	// 마우스 DirectInputDevice 의 액세스 권한을 설정
	// DISCL_EXCLUSIVE (독점모드) - 다른 애플리케이션으로 포커스 이동이 안된다. 마우스와 키보드를 독점모드로 사용하게 될 경우 윈도우 메뉴, 이동, 크기 변경을 할 수 없다. DISCL_BACKGROUND와 같이 쓰일 수 없다.
	// DISCL_FOREGROUND - 포커스를 가지고 있지 않을 경우 디바이스의 데이터(상태)를 얻지 못 한다.
	if( FAILED( m_pDIDMouse->SetCooperativeLevel( g_InputDevice->m_hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND ) ) )
	{
		MessageBox(NULL, "Mouse SetCooperativeLevel Fail", "Error", MB_OK) ;
		return false ;
	}

	m_pDIDMouse->Acquire() ;										// 마우스 DirectInputDevice 습득

	return true ;
}

HRESULT Mouse::Update()
{
	HRESULT hr ;
	prevMouseBuffer = MouseBuffer ;

	// 마우스 디바이스로부터 마우스 상태를 가져올 수 없으면
	// 마우스 디바이스를 다시 습득한다
	if( FAILED( m_pDIDMouse->GetDeviceState( sizeof(MouseBuffer), &MouseBuffer ) ) )
	{
		hr = m_pDIDMouse->Acquire() ;

		while(hr == DIERR_INPUTLOST) // hr == DIERR_INPUTLOST || hr == E_ACCESSDENIED
		{
			hr = m_pDIDMouse->Acquire() ;
		}

		if( FAILED( hr ) )
			return hr ;
	}

	return S_OK ;
}

bool Mouse::IsMouse(MouseButtonType ButtonType)
{
	if(ButtonType == LBUTTON_DOWN && MouseBuffer.rgbButtons[0] == 0x80)
	{
		return TRUE ;
	}
	else if(ButtonType == LBUTTON_UP && MouseBuffer.rgbButtons[0] != 0x80)
	{
		return TRUE ;
	}
	else if(ButtonType == RBUTTON_DOWN && MouseBuffer.rgbButtons[1] == 0x80)
	{
		return TRUE ;
	}
	else if(ButtonType == RBUTTON_UP && MouseBuffer.rgbButtons[1] != 0x80)
	{
		return TRUE ;
	}
	else
	{
		return FALSE ;
	}
}

bool Mouse::IsMousePress(MouseButtonType ButtonType)
{
	if(ButtonType == LBUTTON_DOWN && ( MouseBuffer.rgbButtons[0] == 0x80 && prevMouseBuffer.rgbButtons[0] != 0x80 ))
	{
		return TRUE ;
	}
	else if(ButtonType == LBUTTON_UP && ( MouseBuffer.rgbButtons[0] != 0x80 && prevMouseBuffer.rgbButtons[0] == 0x80 ))
	{
		return TRUE ;
	}
	else if(ButtonType == RBUTTON_DOWN && ( MouseBuffer.rgbButtons[1] == 0x80 && prevMouseBuffer.rgbButtons[1] != 0x80 ))
	{
		return TRUE ;
	}
	else if(ButtonType == RBUTTON_UP && ( MouseBuffer.rgbButtons[1] != 0x80 && prevMouseBuffer.rgbButtons[1] == 0x80 ))
	{
		return TRUE ;
	}
	else
	{
		return FALSE ;
	}
}

void Mouse::SetMousePoint(int x, int y)
{
	int Height = g_D3dDevice->GetWinHeight() ;

	MousePoint.x = x ;
	MousePoint.y = Height - y ;
}

const POINT Mouse::GetMousePoint() const
{
	return MousePoint ;
}