#include "Boss.h"
#include "Sprite.h"

CBoss::CBoss() : m_bLife(false)
{
}
CBoss::CBoss(const CBoss *pBoss) : m_bLife(pBoss->m_bLife)
{
	m_pSprite = new CSprite(pBoss->m_pSprite) ;
	m_BBox = pBoss->m_BBox ;
	m_Position = pBoss->m_Position ;
}
CBoss::~CBoss()
{
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

void CBoss::SetBoundingBox(BBox Box)
{
	m_BBox = Box ;
}