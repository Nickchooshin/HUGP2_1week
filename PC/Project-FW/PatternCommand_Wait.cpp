#include "PatternCommand_Wait.h"

#include "D3dDevice.h"

CPatternCommand_Wait::CPatternCommand_Wait(float delayTime) : m_fTime(0.0f), m_fDelayTime(delayTime)
{
}
CPatternCommand_Wait::~CPatternCommand_Wait()
{
}

void CPatternCommand_Wait::Update()
{
	if(m_fTime>m_fDelayTime)
	{
		m_bLife = false ;
		return ;
	}
	
	m_fTime += g_D3dDevice->GetTime() ;
}