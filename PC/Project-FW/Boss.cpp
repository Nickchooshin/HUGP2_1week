#include "Boss.h"
#include "Sprite.h"

CBoss::CBoss()
{
}
CBoss::~CBoss()
{
}

void CBoss::Init()
{
	m_pSprite = new CSprite ;
}

void CBoss::SetImage(char *strImage)
{
	m_pSprite->Init(strImage) ;
}

void CBoss::SetBoundingBox(BBox Box)
{
	m_BBox = Box ;
}