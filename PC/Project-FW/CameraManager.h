#pragma once
#include "Singleton.h"
#include "Camera.h"
#include <map>

using namespace std ;

class CCamera ;

class CameraManager : public Singleton<CameraManager>
{
private :
	map<int, CCamera*> m_Camera ;
	int m_nCameraNumber ;

public :
	CameraManager() ;
	~CameraManager() ;

	void AddCamera(CCamera *Camera, int Number=0) ;
	void SetCamera(int Number) ;
	void CameraClear(int Number) ;
	void AllCameraClear() ;

	void SetPosition(float x, float y) ;
	void SetPosition(float x, float y, int Number) ;
	void MovePosition(float x, float y) ;
	void MovePosition(float x, float y, int Number) ;

	const D3DXVECTOR3 GetPosition() ;

	void CameraRun() ;
} ;

#define g_CameraManager CameraManager::GetInstance()