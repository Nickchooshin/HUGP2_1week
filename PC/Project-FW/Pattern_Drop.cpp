#include "Pattern_Drop.h"
#include "Boss.h"

#include "D3dDevice.h"

CPattern_Drop::CPattern_Drop(POSITION startPosition, POSITION endPosition, float moveTime, float stayTime) : CPattern(moveTime + stayTime),
																											 m_startPosition(startPosition), m_endPosition(endPosition),
																											 m_moveVector(),
																											 m_fMoveTime(moveTime)
{
	m_moveVector = endPosition - startPosition ;
}
CPattern_Drop::~CPattern_Drop()
{
}

void CPattern_Drop::Update()
{
	if(m_fTime<m_fMoveTime)
		m_pBoss->SetPosition(m_startPosition + (m_moveVector * (m_fTime / m_fMoveTime))) ;
	else
		m_pBoss->SetPosition(m_endPosition) ;

	Time() ;
}