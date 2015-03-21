#pragma once
#include <d3dx9.h>

class CCamera
{
private :
	D3DXVECTOR3 m_Position ;
	D3DXVECTOR3 m_MaxPosition, m_MinPosition ;
	float m_fWidth, m_fHeight ;

public :
	CCamera() ;
	~CCamera() ;

	void SetPosition(float x, float y) ;
	void MovePosition(float x, float y) ;

	void SetWolrdSize(float width, float height) ;
	void SetWorldSize(float w1, float h1, float w2, float h2) ;

	const D3DXVECTOR3 GetPosition() const ;
	
	void Run() ;
private :
	void CorrectionPosition() ;
	void SetWorldPosition_MinMax(float w1, float h1, float w2, float h2) ;
} ;