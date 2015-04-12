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
	IBounding::Type type = pObject->GetBounding()[0]._type ;
	const int num = pObject->GetBoundingNum() ;

	BBOX hero = *(BBOX*)g_Hero->GetBounding() ;
	hero._left += g_Hero->GetPosition().x ;
	hero._top += g_Hero->GetPosition().y ;
	hero._right += g_Hero->GetPosition().x ;
	hero._bottom += g_Hero->GetPosition().y ;

	if(type==IBounding::BOX)
	{
		BBOX *object = (BBOX*)pObject->GetBounding() ;

		for(int i=0; i<num; i++)
		{
			BBOX temp = object[i] ;
			temp._left += pObject->GetPosition().x ;
			temp._top += pObject->GetPosition().y ;
			temp._right += pObject->GetPosition().x ;
			temp._bottom += pObject->GetPosition().y ;

			if(m_Collider.BeCollision(hero, temp))
				return true ;
		}
	}
	else if(type==IBounding::CIRCLE)
	{
		BCIRCLE *object = (BCIRCLE*)pObject->GetBounding() ;

		for(int i=0; i<num; i++)
		{
			BCIRCLE temp = object[i] ;
			temp._x += pObject->GetPosition().x ;
			temp._y += pObject->GetPosition().y ;

			if(m_Collider.BeCollision(hero, temp))
				return true ;
		}
	}
	else if(type==IBounding::ELLIPSE)
	{
		BELLIPSE *object = (BELLIPSE*)pObject->GetBounding() ;

		for(int i=0; i<num; i++)
		{
			BELLIPSE temp = object[i] ;
			temp._x += pObject->GetPosition().x ;
			temp._y += pObject->GetPosition().y ;

			if(m_Collider.BeCollision(hero, temp))
				return true ;
		}
	}
	else if(type==IBounding::LINE)
	{
		BLINE *object = (BLINE*)pObject->GetBounding() ;

		for(int i=0; i<num; i++)
		{
			BLINE temp = object[i] ;
			temp._x1 += pObject->GetPosition().x ;
			temp._y1 += pObject->GetPosition().y ;
			temp._x2 += pObject->GetPosition().x ;
			temp._y2 += pObject->GetPosition().y ;

			if(m_Collider.BeCollision(hero, temp))
				return true ;
		}
	}

	return false ;
}