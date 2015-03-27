#pragma once

#include <stdio.h>

class CDataLoader
{
private :
	FILE *m_pFile ;

public :
	CDataLoader() ;
	~CDataLoader() ;

	const bool OpenData(char *filepath) ;
	const bool CloseData() ;
	
	const bool GetItem(char *item) ;
	void GetString(char *str) ;
	void GetValue(int &value) ;
	void GetValue(float &value) ;
} ;

#define g_LoadManager LoadManager::GetInstance()