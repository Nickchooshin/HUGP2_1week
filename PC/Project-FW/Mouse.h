#pragma once

#include "Singleton.h"
#include <dinput.h>

class Mouse : public Singleton<Mouse>
{
private :
	LPDIRECTINPUTDEVICE8 m_pDIDMouse ;

	DIMOUSESTATE MouseBuffer ;
	DIMOUSESTATE prevMouseBuffer ;
	
	POINT MousePoint ;
public :
	enum MouseButtonType{LBUTTON_DOWN, LBUTTON_UP, RBUTTON_DOWN, RBUTTON_UP} ;

public :
	Mouse() ;
	~Mouse() ;

	bool Init() ;

	HRESULT Update() ;

	bool IsMouse(MouseButtonType ButtonType) ;
	bool IsMousePress(MouseButtonType ButtonType) ;
	void SetMousePoint(int x, int y) ;
	const POINT GetMousePoint() const ;
} ;

#define g_Mouse Mouse::GetInstance()