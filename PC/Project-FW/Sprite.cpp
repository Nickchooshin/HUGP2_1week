#include "Sprite.h"
#include "D3dDevice.h"
#include "TextureManager.h"

CSprite::CSprite() : m_pVB(NULL),
					 m_pIB(NULL),
					 m_pTexture(NULL), m_pTexInfo(NULL),
					 m_fWidth(0.0f), m_fHeight(0.0f),
					 m_Position(0.0f, 0.0f, 0.5f),
					 m_CenterPosition(0.0f, 0.0f, 0.0f),
					 m_fScaleX(1.0f), m_fScaleY(1.0f),
					 m_R(255), m_G(255), m_B(255),
					 m_nAlpha(255)
{
	for(int i=0; i<3; i++)
		m_fAngle[i] = 0.0f ;

	m_tu[0] = 0.0f ;	m_tv[0] = 0.0f ;
	m_tu[1] = 1.0f ;	m_tv[1] = 0.0f ;
	m_tu[2] = 0.0f ;	m_tv[2] = 1.0f ;
	m_tu[3] = 1.0f ;	m_tv[3] = 1.0f ;
}
CSprite::~CSprite()
{
	if(m_pVB!=NULL)
		m_pVB->Release() ;

	if(m_pIB!=NULL)
		m_pIB->Release() ;
}

bool CSprite::Init(char *texfile)
{
	if(!SetTexture(texfile))
		return false ;

	m_fWidth = (float)m_pTexInfo->Width ;
	m_fHeight = (float)m_pTexInfo->Height ;

	if(FAILED(InitVB()))
		return false ;

	return true ;
}

bool CSprite::Init(float Width, float Height, char *texfile)
{
	m_fWidth = Width ;
	m_fHeight = Height ;

	if(FAILED(InitVB()))
		return false ;
	if(!SetTexture(texfile))
		return false ;

	return true ;
}

void CSprite::SetPosition(float X, float Y)
{
	// 소수점 단위로 설정하면, 텍셀과 픽셀의 위치가 어긋나기 때문에
	// 화면상에서 픽셀이 일그러져 보이는 경우가 생긴다.
	// 이를 위해, 불필요한 소수점을 제거하기 위해 정수형에 맞춰 반올림 해준다.

	m_Position.x = (float)((int) (X + 0.5f) ) ;
	m_Position.y = (float)((int) (Y + 0.5f) ) ;
}

void CSprite::SetPositionZ(float Z)
{
	m_Position.z = Z ;
}

void CSprite::SetCenterPosition(float CenterX, float CenterY)
{
	m_CenterPosition.x = (-CenterX + 0.5f) * m_fWidth ;
	m_CenterPosition.y = (-CenterY + 0.5f) * m_fHeight ;
}

void CSprite::SetAngle(float Angle, char Direction)
{
	int index ;

	switch(Direction)
	{
	case 'x' :
	case 'X' :
		index = 0 ;
		break ;
	case 'y' :
	case 'Y' :
		index = 1 ;
		break ;
	case 'z' :
	case 'Z' :
		index = 2 ;
		break ;
	}

	// DirectX는 라디안 각도를 기본으로 한다.
	// 입력 각도는 파이로 받고, 이것을 라디안값으로 바꿔서 넣어준다.
	m_fAngle[index] = (Angle * D3DX_PI) / 180 ;
}

void CSprite::SetScale(float ScaleX, float ScaleY)
{
	m_fScaleX = ScaleX ;
	m_fScaleY = ScaleY ;
}

void CSprite::SetRGB(int R, int G, int B)
{
	m_R = R ;
	m_G = G ;
	m_B = B ;

	SPRITE_VERTEX* pVertices;
	if( FAILED( m_pVB->Lock( 0, sizeof(SPRITE_VERTEX), (void**)&pVertices, 0 ) ) )
		return;

	for(int i=0; i<4; i++)
		pVertices[i].color = D3DCOLOR_XRGB(m_R, m_G, m_B) ;

	m_pVB->Unlock();
}

void CSprite::SetAlpha(int Alpha)
{
	m_nAlpha = Alpha ;
}

void CSprite::SetTextureUV(float u1, float v1, float u2, float v2)
{
	float Width = (float)m_pTexInfo->Width ;
	float Height = (float)m_pTexInfo->Height ;

	m_tu[0] = u1/Width ;	m_tv[0] = v1/Height ;
	m_tu[1] = u2/Width ;	m_tv[1] = v1/Height ;
	m_tu[2] = u1/Width ;	m_tv[2] = v2/Height ;
	m_tu[3] = u2/Width ;	m_tv[3] = v2/Height ;

	SPRITE_VERTEX* pVertices ;
	if( FAILED( m_pVB->Lock( 0, sizeof(SPRITE_VERTEX), (void**)&pVertices, 0 ) ) )
		return ;

	for(int i=0; i<4; i++)
	{
		pVertices[i].tu = m_tu[i] ;
		pVertices[i].tv = m_tv[i] ;
	}

	m_pVB->Unlock() ;
}

void CSprite::TexReverse()
{
	int i ;
	float tu[4], tv[4] ;

	for(i=0; i<2; i++)
	{
		tu[1-i] = m_tu[i] ; 
		tu[3-i] = m_tu[2+i] ;
		tv[1-i] = m_tv[i] ;
		tv[3-i] = m_tv[2+i] ;
	}

	for(i=0; i<4; i++)
	{
		m_tu[i] = tu[i] ;
		m_tv[i] = tv[i] ;
	}

	SPRITE_VERTEX* pVertices ;
	if( FAILED( m_pVB->Lock( 0, sizeof(SPRITE_VERTEX), (void**)&pVertices, 0 ) ) )
		return;

	for(i=0; i<4; i++)
	{
		pVertices[i].tu = m_tu[i] ;
		pVertices[i].tv = m_tv[i] ;
	}

	m_pVB->Unlock() ;
}

D3DXVECTOR3 CSprite::GetPosition()
{
	return m_Position ;
}

void CSprite::Render()
{
	const LPDIRECT3DDEVICE9 pd3dDevice = g_D3dDevice->GetDevice() ;

	SetupMatrices() ;

	pd3dDevice->SetTexture( 0, m_pTexture ) ;

	pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
	pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_TFACTOR );
	pd3dDevice->SetRenderState( D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB( m_nAlpha, 0, 0, 0 ));	// 텍스쳐를 해당 수치만큼 밝게 한다
	//g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);	// 정점색에 있는 Alpha 채널을 값으로 알파조정 ex) pVertices[3].color = D3DCOLOR_ARGB(m_Alpha, m_R, m_G, m_B) ;

	//g_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR) ;
	//g_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR) ;

	pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE) ;			// Z 버퍼 ON
	pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE) ;
	pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL ) ;

	pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE ) ; // 알파 블렌딩 ON
	pd3dDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA ) ;
	pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA ) ;

	pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof(SPRITE_VERTEX) );
	pd3dDevice->SetFVF( D3DFVF_SPRITE_VERTEX );
	pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2) ;

	pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE ) ; // 알파 블렌딩 OFF

	pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE) ;			// Z 버퍼 OFF
	pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE) ;
}

HRESULT CSprite::InitVB()
{
	const LPDIRECT3DDEVICE9 pd3dDevice = g_D3dDevice->GetDevice() ;

	if( FAILED( pd3dDevice->CreateVertexBuffer( 4*sizeof(SPRITE_VERTEX), 0, D3DFVF_SPRITE_VERTEX, D3DPOOL_DEFAULT, &m_pVB, NULL ) ) )
	{
		return E_FAIL;
	}

	SPRITE_VERTEX* pVertices ;
	if( FAILED( m_pVB->Lock( 0, sizeof(SPRITE_VERTEX), (void**)&pVertices, 0 ) ) )
		return E_FAIL ;

	float Width_Half = m_fWidth / 2.0f ;
	float Height_Half = m_fHeight / 2.0f ;

	pVertices[0].x = -(Width_Half) - 0.5f ;
	pVertices[0].y = Height_Half - 0.5f ;
	pVertices[0].z = 0.0f ;
	pVertices[0].color = D3DCOLOR_XRGB(m_R, m_G, m_B) ;
	pVertices[0].tu = m_tu[0];
	pVertices[0].tv = m_tv[0] ;

	pVertices[1].x = Width_Half - 0.5f ;
	pVertices[1].y = Height_Half - 0.5f ;
	pVertices[1].z = 0.0f ;
	pVertices[1].color = D3DCOLOR_XRGB(m_R, m_G, m_B) ;
	pVertices[1].tu = m_tu[1] ;
	pVertices[1].tv = m_tv[1] ;

	pVertices[2].x = -(Width_Half) - 0.5f ;
	pVertices[2].y = -(Height_Half) - 0.5f ;
	pVertices[2].z = 0.0f ;
	pVertices[2].color = D3DCOLOR_XRGB(m_R, m_G, m_B) ;
	pVertices[2].tu = m_tu[2] ;
	pVertices[2].tv = m_tv[2] ;

	pVertices[3].x = Width_Half - 0.5f ;
	pVertices[3].y = -(Height_Half) - 0.5f ;
	pVertices[3].color = D3DCOLOR_XRGB(m_R, m_G, m_B) ;
	pVertices[3].z = 0.0f ;
	pVertices[3].tu = m_tu[3] ;
	pVertices[3].tv = m_tv[3] ;

	m_pVB->Unlock() ;

	return true ;
}

bool CSprite::SetTexture(char *texfile)
{
	m_pTexture = g_TextureManager->GetTexture(texfile, &m_pTexInfo) ;

	if(m_pTexture!=NULL)
		return true ;
	else
		return false ;
}

void CSprite::SetupMatrices()
{
	const LPDIRECT3DDEVICE9 pd3dDevice = g_D3dDevice->GetDevice() ;

	D3DXMATRIXA16 matWorld, matX, matY, matZ, matT, matT2, matS ;
	D3DXMatrixIdentity( &matWorld ) ;
	D3DXMatrixRotationZ(&matX, m_fAngle[0]) ;
	D3DXMatrixRotationZ(&matY, m_fAngle[1]) ;
	D3DXMatrixRotationZ(&matZ, m_fAngle[2]) ;
	D3DXMatrixTranslation( &matT, m_Position.x, m_Position.y, m_Position.z ) ;
	D3DXMatrixTranslation( &matT2, m_CenterPosition.x, m_CenterPosition.y, 0.0f) ;
	D3DXMatrixScaling( &matS, m_fScaleX, m_fScaleY, 0.0f ) ;

	matWorld = matWorld * matT2 * matX * matY * matZ * matS * matT ;
	pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld ) ;
}