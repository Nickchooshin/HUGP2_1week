#pragma once

#include "Singleton.h"
#include <d3dx9.h>
#include <string>
#include <map>

using namespace std ;

class TextureManager : public Singleton<TextureManager>
{
private :
	map<string, LPDIRECT3DTEXTURE9> m_Texture ;
	map<string, D3DXIMAGE_INFO> m_TexInfo ;

public :
	TextureManager() ;
	~TextureManager() ;

	LPDIRECT3DTEXTURE9 GetTexture(string texfile, D3DXIMAGE_INFO **pTexInfo) ;
	D3DXIMAGE_INFO GetTexInfo(string texfile) ;

	void ClearTexture() ;
} ;

#define g_TextureManager TextureManager::GetInstance()