#pragma once

#include "Singleton.h"

class Scene ;

class SceneManager : public Singleton<SceneManager>
{
private :
	Scene *m_pScene ;

public :
	SceneManager() ;
	~SceneManager() ;

	void StartScene(Scene *pScene) ;
	void InitScene() ;

	void UpdateScene(float dt) ;
	void RenderScene() ;

	void DestroyScene() ;

	void ChangeScene(Scene *pScene) ;
} ;

#define g_SceneManager SceneManager::GetInstance()