#include "Pattern_Stay.h"
#include "Boss.h"

#include "D3dDevice.h"

CPattern_Stay::CPattern_Stay(POSITION stayPosition, float stayTime) : CPattern(stayTime),
																	  m_stayPosition(stayPosition)
{
}
CPattern_Stay::~CPattern_Stay()
{
}

void CPattern_Stay::Update()
{
	m_pBoss->SetPosition(m_stayPosition) ;

	Time() ;
}