#include "PatternCommand_Sound.h"
#include "MusicManager.h"

CPatternCommand_Sound::CPatternCommand_Sound(std::string strName) : m_strName("Resource/Sound/SE_bss/" + strName)
{
}
CPatternCommand_Sound::~CPatternCommand_Sound()
{
}

void CPatternCommand_Sound::Update()
{
	FMOD::Sound *pSound = g_MusicManager->LoadMusic(m_strName.c_str(), false, false) ;
	g_MusicManager->PlayMusic(pSound, 1) ;

	m_bLife = false ;
}