#pragma once

#include <d3d9.h>

class CD3dSystem
{
private :
	HINSTANCE			m_hInst ;
	LPDIRECT3D9			m_pD3d ;
	LPDIRECT3DDEVICE9	m_pd3dDevice ;

public :
	CD3dSystem() ;
	~CD3dSystem() ;

	//void Release() ;

	HRESULT InitD3d(const HINSTANCE hInst, const HWND hWnd, const int nWidth, const int nHeight, char* ErrorStr) ;
	LPDIRECT3DDEVICE9 GetDevice() ;

	bool BeginScene() ;
	void EndScene() ;
	void Present() ;
private :
	void SetRenderState() ;
} ;