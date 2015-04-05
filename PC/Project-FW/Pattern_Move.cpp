#include "Pattern_Move.h"
#include "Boss.h"

#include "D3dDevice.h"

CPattern_Move::CPattern_Move(POSITION startPosition, POSITION endPosition, float moveTime) : CPattern(moveTime),
																							 m_startPosition(startPosition), m_endPosition(endPosition),
																							 m_moveVector()
{
	m_moveVector = endPosition - startPosition ;
}
CPattern_Move::~CPattern_Move()
{
}

void CPattern_Move::Update()
{
	m_pBoss->SetPosition(m_startPosition + (m_moveVector * (m_fTime / m_fTargetTime))) ;

	Time() ;
}