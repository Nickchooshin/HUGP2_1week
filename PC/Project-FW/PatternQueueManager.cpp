#include "PatternQueueManager.h"
#include <string.h>
#include <stdlib.h>

#include "DataLoader.h"
#include "PatternCommand.h"
#include "PatternCommand_Wait.h"
#include "PatternCommand_Move.h"
#include "PatternCommand_Stay.h"
#include "PatternCommand_Sound.h"

CPatternQueueManager::CPatternQueueManager() : m_pNowCommand(NULL),
											   m_bQueueEnd(true)
{
}
CPatternQueueManager::~CPatternQueueManager()
{
	ClearQueue() ;

	if(m_pNowCommand!=NULL)
		delete m_pNowCommand ;
}

bool CPatternQueueManager::LoadScript(char *filename)
{
	CDataLoader DataLoader ;
	char filepath[100] ;

	sprintf_s(filepath, "Resource/Data/Boss/%s.dat", filename) ;
	if(!DataLoader.OpenData(filepath))
		return false ;

	char command[100] ;

	while(DataLoader.GetCommand(command))
	{
		int len = strlen(command) ;
		CPatternCommand *pPatternCommand=NULL ;

		if(len==4)
		{
			if(strcmp(command, "WAIT")==0)
			{
				float waitTime ;

				DataLoader.GetValue(waitTime) ;

				pPatternCommand = new CPatternCommand_Wait(waitTime) ;
			}
			else if(strcmp(command, "MOVE")==0)
			{
				char strName[20] ;
				POSITION startPosition, endPosition ;
				float moveTime ;
				
				DataLoader.GetString(strName) ;
				DataLoader.GetValue(startPosition.x) ;
				DataLoader.GetValue(startPosition.y) ;
				DataLoader.GetValue(endPosition.x) ;
				DataLoader.GetValue(endPosition.y) ;
				DataLoader.GetValue(moveTime) ;

				pPatternCommand = new CPatternCommand_Move(strName, startPosition, endPosition, moveTime) ;
			}
			else if(strcmp(command, "STAY")==0)
			{
				char strName[20] ;
				POSITION stayPosition ;
				float stayTime ;
				
				DataLoader.GetString(strName) ;
				DataLoader.GetValue(stayPosition.x) ;
				DataLoader.GetValue(stayPosition.y) ;
				DataLoader.GetValue(stayTime) ;

				pPatternCommand = new CPatternCommand_Stay(strName, stayPosition, stayTime) ;
			}
		}
		else if(len==5 && strcmp(command, "SOUND")==0)
		{
			char strName[20] ;

			DataLoader.GetString(strName) ;

			pPatternCommand = new CPatternCommand_Sound(strName) ;
		}

		if(pPatternCommand!=NULL)
			m_CommandQueue.push(pPatternCommand) ;
	}

	DataLoader.CloseData() ;

	if(m_pNowCommand==NULL)
	{
		m_pNowCommand = m_CommandQueue.front() ;
		m_CommandQueue.pop() ;
	}

	m_bQueueEnd = false ;

	return true ;
}

const bool CPatternQueueManager::BeQueueEnd() const
{
	return m_bQueueEnd ;
}

void CPatternQueueManager::ClearQueue()
{
	CPatternCommand *temp ;

	while(!m_CommandQueue.empty())
	{
		temp = m_CommandQueue.front() ;
		m_CommandQueue.pop() ;
		delete temp ;
	}
}

void CPatternQueueManager::Update()
{
	if(m_bQueueEnd)
		return ;

	m_pNowCommand->Update() ;

	if(!m_pNowCommand->BeLife())
	{
		if(m_pNowCommand!=NULL)
		{
			delete m_pNowCommand ;
			m_pNowCommand = NULL ;
		}

		m_bQueueEnd = m_CommandQueue.empty() ;
		if(!m_bQueueEnd)
		{
			m_pNowCommand = m_CommandQueue.front() ;
			m_CommandQueue.pop() ;
		}
	}
}