#include "Boss.h"
#include "Sprite.h"

#include "CollisionManager.h"

CBoss::CBoss() : m_bLife(false)
{
}
CBoss::CBoss(const CBoss *pBoss) : m_bLife(pBoss->m_bLife)
{
	m_pSprite = new CSprite(pBoss->m_pSprite) ;

	if(pBoss->m_pBounding->_type==IBounding::BOX)
		m_pBounding = new BBOX(*(BBOX*)pBoss->m_pBounding) ;
	else if(pBoss->m_pBounding->_type==IBounding::CIRCLE)
		m_pBounding = new BCIRCLE(*(BCIRCLE*)pBoss->m_pBounding) ;
	else if(pBoss->m_pBounding->_type==IBounding::ELLIPSE)
		m_pBounding = new BELLIPSE(*(BELLIPSE*)pBoss->m_pBounding) ;
	else if(pBoss->m_pBounding->_type==IBounding::LINE)
		m_pBounding = new BLINE(*(BLINE*)pBoss->m_pBounding) ;
	else
		m_pBounding = NULL ;

	m_Position = pBoss->m_Position ;
}
CBoss::~CBoss()
{
	g_CollisionManager->DeleteObject(this) ;
}

void CBoss::Init()
{
	m_pSprite = new CSprite ;
	m_bLife = true ;
}

void CBoss::SetImage(char *strImage)
{
	m_pSprite->Init(strImage) ;
}

void CBoss::SetImage(float fWidth, float fHeight, char *strImage)
{
	m_pSprite->Init(fWidth, fHeight, strImage) ;
}