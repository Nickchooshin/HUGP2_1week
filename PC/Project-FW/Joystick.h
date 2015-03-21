#pragma once

#include "Singleton.h"
#include <dinput.h>

typedef bool (CALLBACK *EX)(const DIDEVICEOBJECTINSTANCE*, VOID*);

class Joystick : public Singleton<Joystick>
{
private :
	LPDIRECTINPUTDEVICE8 m_pDIDJoystick ;

	DIJOYSTATE2 JoystickBuffer ;

	bool m_bReady ;

public :
	Joystick() ;
	~Joystick() ;

	bool Init() ;

	HRESULT Update() ;

	bool IsButtonDown(BYTE Button) ;
	bool IsButtonUp(BYTE Button) ;
	bool IsAxisMin(LONG Min, char Axis) ;
	bool IsAxisMax(LONG Max, char Axis) ;
	bool IsPov(DWORD Pov) ;
private :
	friend BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE* instance, VOID* context) ;
} ;

#define g_Joystick Joystick::GetInstance()