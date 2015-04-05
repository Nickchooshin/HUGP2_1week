#include "MusicManager.h"

/*#ifndef _DEBUG
#pragma comment (lib, "fmodex_vc.lib")
#else
#pragma comment (lib, "fmodexL_vc.lib")
#endif*/

MusicManager::MusicManager(void)
{
	Sounds.clear();
	for (int i=0; i < 32; i++)
		Channels[i] = NULL;
}

MusicManager::~MusicManager(void)
{
	Terminate() ;
}

bool MusicManager::Initialize()
{
	FMOD_RESULT Result;

	Result = FMOD::System_Create(&System);
	if (Result != FMOD_OK)
		return false;

 
	Result = System->init(320, FMOD_INIT_NORMAL, 0);
	if (Result != FMOD_OK)
		return false;
		
	return true;
}

void MusicManager::Terminate()
{
	std::map<std::string, FMOD::Sound *>::iterator iter ;
	for(iter=Sounds.begin(); iter!=Sounds.end(); iter++)
		iter->second->release() ;
	Sounds.clear();
	for (int i=0; i < 32; i++)
		Channels[i] = NULL;
	System->close();
	System->release();
}

FMOD::Sound* MusicManager::LoadMusic(const char *Filename, bool isStream, bool isLoop)
{
	FMOD::Sound * temp;
	
	std::map<std::string, FMOD::Sound *>::iterator iter ;
	
	iter = Sounds.find(Filename) ;
	if(iter==Sounds.end())
	{
		if (isStream)
			System->createStream(Filename, FMOD_SOFTWARE | (isLoop?FMOD_LOOP_NORMAL:0x00) | FMOD_2D, 0, &temp);
		else
			System->createSound(Filename, FMOD_SOFTWARE | (isLoop?FMOD_LOOP_NORMAL:0x00) | FMOD_2D, 0, &temp);

		Sounds[Filename] = temp ;
	}
	else
	{
		temp = Sounds[Filename] ;
	}

	return temp;
}

void MusicManager::PlayMusic(FMOD::Sound* Sound, int Channel)
{
	if (Channel > 32)
		return;

	System->playSound(FMOD_CHANNEL_FREE, Sound, false, &Channels[Channel]);
}

void MusicManager::PauseMusic(bool bPause, int Channel)
{
	if(Channel>32)
		return ;

	Channels[Channel]->setPaused(bPause) ;
}

void MusicManager::StopMusic(int Channel)
{
	if (Channel > 32)
		return;

	bool bPlay;
	Channels[Channel]->isPlaying(&bPlay);
	
	if (bPlay)
		Channels[Channel]->stop();
}

void MusicManager::Loop()
{
	System->update();
}

void MusicManager::Reset()
{
	MusicManager::Terminate();
	MusicManager::Initialize();
}
