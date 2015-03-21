#include "CameraManager.h"

CameraManager::CameraManager() : m_nCameraNumber(0)
{
}
CameraManager::~CameraManager()
{
	AllCameraClear() ;
}

void CameraManager::AddCamera(CCamera *Camera, int Number)
{
	map<int, CCamera*>::iterator iter ;

	iter = m_Camera.find(Number) ;
	if(iter!=m_Camera.end())
		delete iter->second ;

	m_Camera[Number] = Camera ;
}

void CameraManager::SetCamera(int Number)
{
	m_nCameraNumber = Number ;
}

void CameraManager::CameraClear(int Number)
{
	map<int, CCamera*>::iterator iter ;

	iter = m_Camera.find(Number) ;

	if(iter!=m_Camera.end())
	{
		delete iter->second ;
		m_Camera.erase(iter) ;
	}
}

void CameraManager::AllCameraClear()
{
	if(m_Camera.empty())
		return ;

	map<int, CCamera*>::iterator iter ;
	map<int, CCamera*>::iterator iter_end = m_Camera.end() ;

	for(iter=m_Camera.begin(); iter!=iter_end; iter++)
		delete iter->second ;

	m_Camera.clear() ;
}

void CameraManager::SetPosition(float x, float y)
{
	SetPosition(x, y, m_nCameraNumber) ;
}

void CameraManager::SetPosition(float x, float y, int Number)
{
	m_Camera[Number]->SetPosition(x, y) ;
}

void CameraManager::MovePosition(float x, float y)
{
	MovePosition(x, y, m_nCameraNumber) ;
}

void CameraManager::MovePosition(float x, float y, int Number)
{
	m_Camera[Number]->MovePosition(x, y) ;
}

const D3DXVECTOR3 CameraManager::GetPosition()
{
	return m_Camera[m_nCameraNumber]->GetPosition() ;
}

void CameraManager::CameraRun()
{
	m_Camera[m_nCameraNumber]->Run() ;
}