#include "Boss.h"
#include "Sprite.h"

#include "CollisionManager.h"

CBoss::CBoss() : m_bLife(false)
{
}
CBoss::CBoss(const CBoss *pBoss) : m_bLife(pBoss->m_bLife)
{
	m_pSprite = new CSprite(pBoss->m_pSprite) ;

	m_nBoundingNum = pBoss->GetBoundingNum() ;
	if(pBoss->m_pBounding->_type==IBounding::BOX)
	{
		BBOX *box = new BBOX[m_nBoundingNum] ;
		BBOX *boss = (BBOX*)pBoss->m_pBounding ;
		for(int i=0; i<m_nBoundingNum; i++)
			box[i] = boss[i] ;
		m_pBounding = box ;

		//m_pBounding = new BBOX(*(BBOX*)pBoss->m_pBounding) ;
	}
	else if(pBoss->m_pBounding->_type==IBounding::CIRCLE)
	{
		BCIRCLE *circle = new BCIRCLE[m_nBoundingNum] ;
		BCIRCLE *boss = (BCIRCLE*)pBoss->m_pBounding ;
		for(int i=0; i<m_nBoundingNum; i++)
			circle[i] = boss[i] ;
		m_pBounding = circle ;

		//m_pBounding = new BCIRCLE(*(BCIRCLE*)pBoss->m_pBounding) ;
	}
	else if(pBoss->m_pBounding->_type==IBounding::ELLIPSE)
	{
		BELLIPSE *ellipse = new BELLIPSE[m_nBoundingNum] ;
		BELLIPSE *boss = (BELLIPSE*)pBoss->m_pBounding ;
		for(int i=0; i<m_nBoundingNum; i++)
			ellipse[i] = boss[i] ;
		m_pBounding = ellipse ;

		//m_pBounding = new BELLIPSE(*(BELLIPSE*)pBoss->m_pBounding) ;
	}
	else if(pBoss->m_pBounding->_type==IBounding::LINE)
	{
		BLINE *line = new BLINE[m_nBoundingNum] ;
		BLINE *boss = (BLINE*)pBoss->m_pBounding ;
		for(int i=0; i<m_nBoundingNum; i++)
			line[i] = boss[i] ;
		m_pBounding = line ;

		//m_pBounding = new BLINE(*(BLINE*)pBoss->m_pBounding) ;
	}
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