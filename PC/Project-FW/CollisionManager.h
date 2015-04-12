#pragma once

#include "Singleton.h"
#include "Collider.h"
#include <vector>

class CObjects ;

class CollisionManager : public Singleton<CollisionManager>
{
private :
	std::vector<CObjects*> m_ObjectList ;
	CCollider m_Collider ;

public :
	CollisionManager() ;
	~CollisionManager() ;

	void AddObject(CObjects *pObject) ;
	void DeleteObject(CObjects *pObject) ;

	void DeleteAllObjects() ;

	void Update() ;
private :
	bool Collision(CObjects *pObject) ;
} ;

#define g_CollisionManager CollisionManager::GetInstance()