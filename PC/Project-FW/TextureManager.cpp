#include "TextureManager.h"
#include "D3dDevice.h"

TextureManager::TextureManager()
{
}
TextureManager::~TextureManager()
{
	ClearTexture() ;
}

LPDIRECT3DTEXTURE9 TextureManager::GetTexture(string texfile, D3DXIMAGE_INFO **pTexInfo)
{
	const LPDIRECT3DDEVICE9 pd3dDevice = g_D3dDevice->GetDevice() ;
	map<string, LPDIRECT3DTEXTURE9>::iterator iter ;

	iter = m_Texture.find(texfile) ;
	if(iter==m_Texture.end())
	{
		LPDIRECT3DTEXTURE9 pTexture = NULL ;
		D3DXIMAGE_INFO TexInfo ;

		if( FAILED( D3DXCreateTextureFromFileEx( pd3dDevice, texfile.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, NULL,
					D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, &TexInfo, NULL, &pTexture ) ) )
		{
			char str[1024] ;
			sprintf_s(str, "Could not find %s Texture File", texfile.c_str()) ;
			MessageBox(NULL, str, "Texture error", MB_OK) ;

			return NULL ;
		}

		m_Texture[texfile] = pTexture ;
		m_TexInfo[texfile] = TexInfo ;
	}

	if(pTexInfo!=NULL)
		*pTexInfo = &m_TexInfo[texfile] ;

	return m_Texture[texfile] ;
}

D3DXIMAGE_INFO TextureManager::GetTexInfo(string texfile)
{
	return m_TexInfo[texfile] ;
}

void TextureManager::ClearTexture()
{
	if(m_Texture.empty())
		return ;

	map<string, LPDIRECT3DTEXTURE9>::iterator iter ;

	for(iter=m_Texture.begin(); iter!=m_Texture.end(); iter++)
		iter->second->Release() ;

	m_Texture.clear() ;
}

/*
map<string, class*> testmap;

testmap.insert(map<string, class*>::value_type(k, v)).first->second = v; //k=key, v=value


¶Ç´Â


testmap.insert(pair<string, class*>(k,v));
*/