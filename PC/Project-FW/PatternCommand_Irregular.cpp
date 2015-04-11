#include "PatternCommand_Irregular.h"
#include "Pattern_Irregular22.h"
#include "Pattern_Irregular23.h"
#include "Pattern_Irregular31.h"
#include "Pattern_Irregular32.h"
#include "Pattern_Irregular33.h"
#include "Pattern_Irregular52.h"

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
	else if(m_strName=="Boss2_Pattern3")
		pPattern = new CPattern_Irregular23() ;
	else if(m_strName=="Boss3_Pattern1")
		pPattern = new CPattern_Irregular31() ;
	else if(m_strName=="Boss3_Pattern2")
		pPattern = new CPattern_Irregular32() ;
	else if(m_strName=="Boss3_Pattern3")
		pPattern = new CPattern_Irregular33() ;
	else if(m_strName=="Boss5_Pattern2")
		pPattern = new CPattern_Irregular52() ;

	g_BossManager->AddPattern(pPattern) ;

	m_bLife = false ;
}