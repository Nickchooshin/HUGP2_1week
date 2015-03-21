#pragma once
#include <d3dx9.h>

class CSprite
{
private :
	LPDIRECT3DVERTEXBUFFER9	m_pVB ;
	LPDIRECT3DINDEXBUFFER9	m_pIB ;
	LPDIRECT3DTEXTURE9		m_pTexture ;
	D3DXIMAGE_INFO			*m_pTexInfo ;

	float m_fWidth, m_fHeight ;
	D3DXVECTOR3 m_Position ;
	D3DXVECTOR3 m_CenterPosition ;
	float m_fScaleX, m_fScaleY ;
	float m_fAngle[3] ;
	int m_R, m_G, m_B ;
	int m_nAlpha ;
	float m_tu[4], m_tv[4] ;

public :
	CSprite() ;
	~CSprite() ;

	bool Init(char *texfile) ;
	bool Init(float Width, float Height, char *texfile) ;

	void SetPosition(float X, float Y) ;						// 좌표설정 (중앙 기준)
	void SetPositionZ(float Z) ;								// Z축 좌표설정
	void SetCenterPosition(float CenterX, float CenterY) ;		// 중심점 설정
	void SetScale(float ScaleX, float ScaleY) ;					// 확대, 축소
	void SetAngle(float Angle, char Direction='z') ;			// 각도 설정 (반시계방향)
	void SetRGB(int R, int G, int B) ;							// RGB값 설정
	void SetAlpha(int Alpha) ;									// 알파값 설정 0~255
	
	void SetTextureUV(float u1, float v1, float u2, float v2) ;	// 텍스쳐 UV 설정
	void TexReverse() ;											// 텍스쳐 뒤집기

	D3DXVECTOR3 GetPosition() ;									// 좌표 받아오기

	void Render() ;
private :
	HRESULT InitVB() ;

	bool SetTexture(char *texfile) ;
	void SetupMatrices() ;
} ;

struct SPRITE_VERTEX
{
	float		x, y, z ;	// The position
	D3DCOLOR	color ;		// The color
	float		tu, tv ;	// The texture coordinates (x, y)
} ;

#define D3DFVF_SPRITE_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)