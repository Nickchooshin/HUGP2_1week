#include "CollisionManager.h"
#include "Hero.h"

CollisionManager::CollisionManager() : m_Collider()
{
}
CollisionManager::~CollisionManager()
{
}

void CollisionManager::AddObject(CObjects *pObject)
{
	m_ObjectList.push_back(pObject) ;
}

void CollisionManager::DeleteObject(CObjects *pObject)
{
	const int num=m_ObjectList.size() ;

	for(int i=0; i<num; i++)
	{
		if(m_ObjectList[i]==pObject)
		{
			m_ObjectList.erase(m_ObjectList.begin() + i) ;
			break ;
		}
	}
}

void CollisionManager::DeleteAllObjects()
{
	if(!m_ObjectList.empty())
		m_ObjectList.clear() ;
}

void CollisionManager::Update()
{
	const int num=m_ObjectList.size() ;
	CObjects *pObject ;

	for(int i=0; i<num; i++)
	{
		pObject = m_ObjectList[i] ;
		if(pObject->BeCollision() && Collision(pObject))
			g_Hero->Dead() ;
	}
}

bool CollisionManager::Collision(CObjects *pObject)
{
	IBounding::Type type = pObject->GetBounding()->_type ;

	BBOX hero = *(BBOX*)g_Hero->GetBounding() ;
	hero._left += g_Hero->GetPosition().x ;
	hero._top += g_Hero->GetPosition().y ;
	hero._right += g_Hero->GetPosition().x ;
	hero._bottom += g_Hero->GetPosition().y ;

	if(type==IBounding::BOX)
	{
		BBOX object = *(BBOX*)pObject->GetBounding() ;
		object._left += pObject->GetPosition().x ;
		object._top += pObject->GetPosition().y ;
		object._right += pObject->GetPosition().x ;
		object._bottom += pObject->GetPosition().y ;

		return m_Collider.BeCollision(hero, object) ;
	}
	else if(type==IBounding::CIRCLE)
	{
		BCIRCLE object = *(BCIRCLE*)pObject->GetBounding() ;
		object._x += pObject->GetPosition().x ;
		object._y += pObject->GetPosition().y ;

		return m_Collider.BeCollision(hero, object) ;
	}
	else if(type==IBounding::ELLIPSE)
	{
		BELLIPSE object = *(BELLIPSE*)pObject->GetBounding() ;
		object._x += pObject->GetPosition().x ;
		object._y += pObject->GetPosition().y ;

		return m_Collider.BeCollision(hero, object) ;
	}
	else if(type==IBounding::LINE)
	{
		BLINE object = *(BLINE*)pObject->GetBounding() ;
		object._x1 += pObject->GetPosition().x ;
		object._y1 += pObject->GetPosition().y ;
		object._x2 += pObject->GetPosition().x ;
		object._y2 += pObject->GetPosition().y ;

		return m_Collider.BeCollision(hero, object) ;
	}

	return false ;
}