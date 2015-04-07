#include "Pattern.h"
#include "Boss.h"

#include "D3dDevice.h"

CPattern::CPattern() : m_pBoss(NULL),
					   m_fTime(0.0f), m_fTargetTime(0.0f),
					   m_bStartTime(false), m_bLife(true)
{
}
CPattern::CPattern(float targetTime) : m_pBoss(NULL),
									   m_fTime(0.0f), m_fTargetTime(targetTime),
									   m_bStartTime(false), m_bLife(true)
{
}
CPattern::~CPattern()
{
	if(m_pBoss!=NULL)
		delete m_pBoss ;
}

void CPattern::SetBoss(CBoss *pBoss)
{
	m_pBoss = pBoss ;
}

void CPattern::Render()
{
	m_pBoss->Render() ;
}

const bool CPattern::BeLife() const
{
	return m_bLife ;
}

void CPattern::Time()
{
	/*if(m_fTime>=m_fTargetTime)
		m_bLife = false ;
	
	m_fTime += g_D3dDevice->GetTime() ;*/
	if(m_bStartTime)
		m_fTime += g_D3dDevice->GetTime() ;
	else
		m_bStartTime = true ;

	if(m_fTime>=m_fTargetTime)
		m_bLife = false ;
}