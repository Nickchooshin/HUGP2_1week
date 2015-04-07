#include "PatternCommand_Irregular.h"
#include "Pattern_Irregular22.h"
#include "BossManager.h"

CPatternCommand_Irregular::CPatternCommand_Irregular(std::string strName) : m_strName(strName)
{
}
CPatternCommand_Irregular::~CPatternCommand_Irregular()
{
}

void CPatternCommand_Irregular::Update()
{
	CPattern *pPattern ;

	if(m_strName=="Boss2_Pattern2")
		pPattern = new CPattern_Irregular22() ;

	//CPattern *pPattern = new CPattern_Irregular(m_strName) ;
	g_BossManager->AddPattern(pPattern) ;

	m_bLife = false ;
}