#include "Joystick.h"
#include "InputDevice.h"

Joystick::Joystick() : m_pDIDJoystick(NULL),
					   m_bReady(false)
{
}
Joystick::~Joystick()
{
	if(m_pDIDJoystick!=NULL)
	{
		m_pDIDJoystick->Unacquire() ;
		m_pDIDJoystick->Release() ;
		m_pDIDJoystick = NULL ;
	}
}

bool Joystick::Init()
{
	// 조이스틱 DirectInputDevice 초기화
	if( FAILED( g_InputDevice->m_pDInput->CreateDevice( GUID_Joystick, &m_pDIDJoystick, NULL ) ) )
	{
		//MessageBox(NULL, "Joystick CreateDevice Fail", "Error", MB_OK) ;
		return false ;
	}

	// 조이스틱 DirectInputDevice 포멧 설정
	if( FAILED( m_pDIDJoystick->SetDataFormat( &c_dfDIJoystick2 ) ) )
	{
		//MessageBox(NULL, "Joystick SetDataFormat Fail", "Error", MB_OK) ;
		return false ;
	}

	// 조이스틱 DirectInputDevice 의 액세스 권한을 설정
	// DISCL_EXCLUSIVE (독점모드) - 다른 애플리케이션으로 포커스 이동이 안된다. 마우스와 키보드를 독점모드로 사용하게 될 경우 윈도우 메뉴, 이동, 크기 변경을 할 수 없다. DISCL_BACKGROUND와 같이 쓰일 수 없다.
	// DISCL_FOREGROUND - 포커스를 가지고 있지 않을 경우 디바이스의 데이터(상태)를 얻지 못 한다.
	if( FAILED( m_pDIDJoystick->SetCooperativeLevel( g_InputDevice->m_hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND ) ) )
	{
		//MessageBox(NULL, "Joystick SetCooperativeLevel Fail", "Error", MB_OK) ;
		return false ;
	}

	// 조이스틱의 능력에 관한 정보를 수집한다. 축이나 버튼등의 콘트롤러의 수, force feedback의 지원, 및 조이스틱의 동작이나 지원 옵션에 관한 그 외의 상세
	// DIDEVCAPS 구조체는, 능력 정보의 보관 유지에 사용
	DIDEVCAPS diDevCaps ;
	diDevCaps.dwSize = sizeof(DIDEVCAPS) ;
	if( FAILED( m_pDIDJoystick->GetCapabilities(&diDevCaps) ) )
	{
		//MessageBox(NULL, "Joystick GetCapabilities Fail", "Error", MB_OK) ;
		return false ;
	}

	// 메서드의 최초의 인수 EnumAxesCallback 는, 열거된 개체를 필요에 따라서 처리하는 콜백 함수의 주소이다.
	if( FAILED( m_pDIDJoystick->EnumObjects(EnumAxesCallback, (void*)g_InputDevice->m_hWnd, DIDFT_AXIS) ) )
	{
		//MessageBox(NULL, "Joystick EnumObjects Fail", "Error", MB_OK) ;
		return false ;
	}

	m_pDIDJoystick->Poll() ;

	m_bReady = true ;

	return true ;
}

BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE* instance, VOID* context)
{
    DIPROPRANGE propRange; 
    propRange.diph.dwSize       = sizeof(DIPROPRANGE); 
    propRange.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
    propRange.diph.dwHow        = DIPH_BYID; 
    propRange.diph.dwObj        = instance->dwType;
    propRange.lMin              = -1000; 
    propRange.lMax              = +1000; 
    
    // Set the range for the axis
    if (FAILED(g_Joystick->m_pDIDJoystick->SetProperty(DIPROP_RANGE, &propRange.diph))) {
        return DIENUM_STOP;
    }

    return DIENUM_CONTINUE;
}

HRESULT Joystick::Update()
{
	if(!m_bReady)
		return false ;

	HRESULT hr ;

	// 조이스틱 디바이스로부터 조이스틱의 상태를 가져올 수 없으면
	// 조이스틱의 디바이스를 다시 습득한다
	hr = m_pDIDJoystick->Poll() ;

	if( FAILED(hr) )
	{
		hr = m_pDIDJoystick->Acquire() ;
		
		while(hr == DIERR_INPUTLOST) // hr == DIERR_INPUTLOST || hr == E_ACCESSDENIED
		{
			hr = m_pDIDJoystick->Acquire() ;
		}

		if( FAILED( hr ) )
			return hr ;
	}

	if( FAILED( hr = m_pDIDJoystick->GetDeviceState(sizeof(DIJOYSTATE2), &JoystickBuffer) ) )
		return hr ;

	return S_OK ;
}

bool Joystick::IsButtonDown(BYTE Button)
{
	if(JoystickBuffer.rgbButtons[Button] & 0x80)
		return true ;

	return false ;
}

bool Joystick::IsButtonUp(BYTE Button)
{
	if(JoystickBuffer.rgbButtons[Button] & 0x80)
		return false ;

	return true ;
}

bool Joystick::IsAxisMin(LONG Min, char Axis)
{
	LONG axis ;

	switch(Axis)
	{
	case 'x' :
	case 'X' :
		axis = JoystickBuffer.lX ;
		break ;

	case 'y' :
	case 'Y' :
		axis = JoystickBuffer.lY ;
		break ;

	case 'z' :
	case 'Z' :
		axis = JoystickBuffer.lZ ;
		break ;

	case 'r' :
	case 'R' :
		axis = JoystickBuffer.lRz ;
		break ;

	default :
		return false ;
	}

	if(axis>=Min)
		return true ;

	return false ;
}

bool Joystick::IsAxisMax(LONG Max, char Axis)
{
	LONG axis ;

	switch(Axis)
	{
	case 'x' :
	case 'X' :
		axis = JoystickBuffer.lX ;
		break ;

	case 'y' :
	case 'Y' :
		axis = JoystickBuffer.lY ;
		break ;

	case 'z' :
	case 'Z' :
		axis = JoystickBuffer.lZ ;
		break ;

	case 'r' :
	case 'R' :
		axis = JoystickBuffer.lRz ;
		break ;

	default :
		return false ;
	}

	if(axis<=Max)
		return true ;

	return false ;
}

bool Joystick::IsPov(DWORD Pov)
{
	if(JoystickBuffer.rgdwPOV[0]==Pov)
		return true ;

	return false ;
}