#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager() : m_pScene(0)
{
}
SceneManager::~SceneManager()
{
	DestroyScene() ;
}

void SceneManager::StartScene(Scene *pScene)
{
	m_pScene = pScene ;
}

void SceneManager::InitScene()
{
	if(m_pScene==0)
		return ;

	m_pScene->Init() ;
}

void SceneManager::UpdateScene(float dt)
{
	m_pScene->Update(dt) ;
}

void SceneManager::RenderScene()
{
	m_pScene->Render() ;
}

void SceneManager::DestroyScene()
{
	if(m_pScene==0)
		return ;

	m_pScene->Destroy() ;
	delete m_pScene ;
	m_pScene = 0 ;
}

void SceneManager::ChangeScene(Scene *pScene)
{
	DestroyScene() ;

	m_pScene = pScene ;

	InitScene() ;
}