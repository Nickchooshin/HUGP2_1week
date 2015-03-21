#include "Keyboard.h"
#include "InputDevice.h"

Keyboard::Keyboard() : m_pDIDKeyboard(NULL)
{
	ZeroMemory(KeyBuffer, sizeof(KeyBuffer)) ;
	ZeroMemory(prevKeyBuffer, sizeof(prevKeyBuffer)) ;
}
Keyboard::~Keyboard()
{
	if(m_pDIDKeyboard!=NULL)
	{
		m_pDIDKeyboard->Unacquire() ;
		m_pDIDKeyboard->Release() ;
		m_pDIDKeyboard = NULL ;
	}
}

bool Keyboard::Init()
{
	// 키보드 DirectInputDevice 초기화
	if( FAILED( g_InputDevice->m_pDInput->CreateDevice( GUID_SysKeyboard, &m_pDIDKeyboard, NULL ) ) )
	{
		MessageBox(NULL, "Keyboard CreateDevice Fail", "Error", MB_OK) ;
		return false ;
	}

	// 키보드 DirectInputDevice 포멧 설정
	if( FAILED( m_pDIDKeyboard->SetDataFormat( &c_dfDIKeyboard ) ) )
	{
		MessageBox(NULL, "Keyboard SetDataFormat Fail", "Error", MB_OK) ;
		return false ;
	}

	// 키보드 DirectInputDevice 의 액세스 권한을 설정
	// DISCL_EXCLUSIVE (독점모드) - 다른 애플리케이션으로 포커스 이동이 안된다. 마우스와 키보드를 독점모드로 사용하게 될 경우 윈도우 메뉴, 이동, 크기 변경을 할 수 없다. DISCL_BACKGROUND와 같이 쓰일 수 없다.
	// DISCL_FOREGROUND - 포커스를 가지고 있지 않을 경우 디바이스의 데이터(상태)를 얻지 못 한다.
	if( FAILED( m_pDIDKeyboard->SetCooperativeLevel( g_InputDevice->m_hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND ) ) )
	{
		MessageBox(NULL, "KeyBoard SetCooperativeLevel Fail", "Error", MB_OK) ;
		return false ;
	}

	m_pDIDKeyboard->Acquire() ;										// 키보드 DirectInputDevice 습득
	m_pDIDKeyboard->GetDeviceState(sizeof(KeyBuffer), &KeyBuffer) ;	// 키보드 DirectInputDevice 에서 키보드의 상태를 가져온다

	return true ;
}

HRESULT Keyboard::Update()
{
	HRESULT hr ;
	memcpy(prevKeyBuffer, KeyBuffer, sizeof(KeyBuffer)) ;
	ZeroMemory(KeyBuffer, sizeof(KeyBuffer)) ;

	// 키보드 디바이스로부터 키보드의 상태를 가져올 수 없으면
	// 키보드의 디바이스를 다시 습득한다
	if( FAILED( m_pDIDKeyboard->GetDeviceState( sizeof(KeyBuffer), &KeyBuffer ) ) )
	{
		hr = m_pDIDKeyboard->Acquire() ;

		while(hr == DIERR_INPUTLOST) // hr == DIERR_INPUTLOST || hr == E_ACCESSDENIED
		{
			hr = m_pDIDKeyboard->Acquire() ;
		}

		if( FAILED( hr ) )
			return hr ;
	}

	return S_OK ;
}

bool Keyboard::IsButtonDown(BYTE Button)
{
	if(KeyBuffer[Button] & 0x80)
		return true ;

	return false ;
}

bool Keyboard::IsButtonUp(BYTE Button)
{
	if(KeyBuffer[Button] & 0x80)
		return false ;

	return true ;
}

bool Keyboard::IsPressDown(BYTE Button)
{
	if((KeyBuffer[Button] & 0x80) && !(prevKeyBuffer[Button] & 0x80))
		return true ;

	return false ;
}

bool Keyboard::IsPressUp(BYTE Button)
{
	if(!(KeyBuffer[Button] & 0x80) && (prevKeyBuffer[Button] & 0x80))
		return true ;

	return false ;
}