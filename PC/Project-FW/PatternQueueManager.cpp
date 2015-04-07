#include "PatternQueueManager.h"
#include <string.h>
#include <stdlib.h>

#include "DataLoader.h"
#include "PatternCommand.h"
#include "PatternCommand_Wait.h"
#include "PatternCommand_Move.h"
#include "PatternCommand_Drop.h"
#include "PatternCommand_Stay.h"
#include "PatternCommand_Sound.h"
#include "PatternCommand_Warning.h"
#include "PatternCommand_Irregular.h"

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

	char command[30] ;

	while(DataLoader.GetCommand(command))
	{
		int len = strlen(command) ;

		if(len==4)
		{
			if(strcmp(command, "WAIT")==0)
				CommandWait(DataLoader) ;
			else if(strcmp(command, "MOVE")==0)
				CommandMove(DataLoader) ;
			else if(strcmp(command, "DROP")==0)
				CommandDrop(DataLoader) ;
			/*else if(strcmp(command, "MOVE")==0 || strcmp(command, "DROP")==0)
			{
				char option[30] ;
				bool bStay ;
				DataLoader.GetCommand(option) ;
				if(strcmp(command, "DROP")==0)
					bStay = true ;

				char strName[20] ;
				float moveTime ;

				if(strcmp(option, "NORMAL")==0)
				{
					POSITION startPosition, endPosition ;
				
					DataLoader.GetString(strName) ;
					DataLoader.GetValue(startPosition.x) ;
					DataLoader.GetValue(startPosition.y) ;
					DataLoader.GetValue(endPosition.x) ;
					DataLoader.GetValue(endPosition.y) ;
					DataLoader.GetValue(moveTime) ;

					if(!bStay)
						pPatternCommand = new CPatternCommand_Move(strName, startPosition, endPosition, moveTime) ;
					else
					{
						float stayTime ;
						DataLoader.GetValue(stayTime) ;
						pPatternCommand = new CPatternCommand_Move(strName, startPosition, endPosition, moveTime, stayTime) ;
					}
				}
				else if(strcmp(option, "TRACE")==0)
				{
					float startAxis, endAxis ;

					DataLoader.GetCommand(option) ;
					DataLoader.GetString(strName) ;
					DataLoader.GetValue(startAxis) ;
					DataLoader.GetValue(endAxis) ;
					DataLoader.GetValue(moveTime) ;

					if(!bStay)
						pPatternCommand = new CPatternCommand_Move(option[0], strName, startAxis, endAxis, moveTime) ;
					else
					{
						float stayTime ;
						DataLoader.GetValue(stayTime) ;
						pPatternCommand = new CPatternCommand_Move(option[0], strName, startAxis, endAxis, moveTime, stayTime) ;
					}
				}
			}*/
			else if(strcmp(command, "STAY")==0)
				CommandStay(DataLoader) ;
		}
		else if(len==5)
		{
			if(strcmp(command, "SOUND")==0)
				CommandSound(DataLoader) ;
			else if(strcmp(command, "SHAKE")==0)
				CommandShake(DataLoader) ;
		}
		else if(len==7 && strcmp(command, "WARNING")==0)
			CommandWarning(DataLoader) ;
		else if(len==9 && strcmp(command, "IRREGULAR")==0)
			CommandIrregular(DataLoader) ;
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
	while(!m_bQueueEnd)
	{
		m_pNowCommand->Update() ;

		if(!m_pNowCommand->BeLife())
		{
			delete m_pNowCommand ;
			m_pNowCommand = NULL ;

			m_bQueueEnd = m_CommandQueue.empty() ;
			if(!m_bQueueEnd)
			{
				m_pNowCommand = m_CommandQueue.front() ;
				m_CommandQueue.pop() ;
			}
		}
		else
			break ;
	}
}

/******************* COMMAND ********************/

void CPatternQueueManager::CommandWait(CDataLoader &DataLoader)
{
	float waitTime ;

	DataLoader.GetValue(waitTime) ;

	CPatternCommand *pPatternCommand = new CPatternCommand_Wait(waitTime) ;
	m_CommandQueue.push(pPatternCommand) ;
}

void CPatternQueueManager::CommandMove(CDataLoader &DataLoader)
{
	char option[30] ;
	char strName[20] ;
	float moveTime ;

	CPatternCommand *pPatternCommand ;
	
	DataLoader.GetCommand(option) ;

	if(strcmp(option, "NORMAL")==0)
	{
		POSITION startPosition, endPosition ;

		DataLoader.GetString(strName) ;
		DataLoader.GetValue(startPosition.x) ;
		DataLoader.GetValue(startPosition.y) ;
		DataLoader.GetValue(endPosition.x) ;
		DataLoader.GetValue(endPosition.y) ;
		DataLoader.GetValue(moveTime) ;

		pPatternCommand = new CPatternCommand_Move(strName, startPosition, endPosition, moveTime) ;
	}
	else if(strcmp(option, "TRACE")==0)
	{
		float startAxis, endAxis ;

		DataLoader.GetCommand(option) ;
		DataLoader.GetString(strName) ;
		DataLoader.GetValue(startAxis) ;
		DataLoader.GetValue(endAxis) ;
		DataLoader.GetValue(moveTime) ;

		pPatternCommand = new CPatternCommand_Move(option[0], strName, startAxis, endAxis, moveTime) ;
	}
	
	m_CommandQueue.push(pPatternCommand) ;
}

void CPatternQueueManager::CommandDrop(CDataLoader &DataLoader)
{
	char option[30] ;
	char strName[20] ;
	float moveTime, stayTime ;
	
	CPatternCommand *pPatternCommand ;

	DataLoader.GetCommand(option) ;

	if(strcmp(option, "NORMAL")==0)
	{
		POSITION startPosition, endPosition ;

		DataLoader.GetString(strName) ;
		DataLoader.GetValue(startPosition.x) ;
		DataLoader.GetValue(startPosition.y) ;
		DataLoader.GetValue(endPosition.x) ;
		DataLoader.GetValue(endPosition.y) ;
		DataLoader.GetValue(moveTime) ;
		//
		DataLoader.GetValue(stayTime) ;

		pPatternCommand = new CPatternCommand_Drop(strName, startPosition, endPosition, moveTime, stayTime) ;
	}
	else if(strcmp(option, "TRACE")==0)
	{
		float startAxis, endAxis ;

		DataLoader.GetCommand(option) ;
		DataLoader.GetString(strName) ;
		DataLoader.GetValue(startAxis) ;
		DataLoader.GetValue(endAxis) ;
		DataLoader.GetValue(moveTime) ;
		//
		DataLoader.GetValue(stayTime) ;

		pPatternCommand = new CPatternCommand_Drop(option[0], strName, startAxis, endAxis, moveTime, stayTime) ;
	}
	
	m_CommandQueue.push(pPatternCommand) ;
}

void CPatternQueueManager::CommandStay(CDataLoader &DataLoader)
{
	char strName[20] ;
	POSITION stayPosition ;
	float stayTime ;

	DataLoader.GetString(strName) ;
	DataLoader.GetValue(stayPosition.x) ;
	DataLoader.GetValue(stayPosition.y) ;
	DataLoader.GetValue(stayTime) ;

	CPatternCommand *pPatternCommand = new CPatternCommand_Stay(strName, stayPosition, stayTime) ;
	m_CommandQueue.push(pPatternCommand) ;
}

void CPatternQueueManager::CommandSound(CDataLoader &DataLoader)
{
	char strName[20] ;

	DataLoader.GetString(strName) ;

	CPatternCommand *pPatternCommand = new CPatternCommand_Sound(strName) ;
	m_CommandQueue.push(pPatternCommand) ;
}

void CPatternQueueManager::CommandShake(CDataLoader &DataLoader)
{
	//CPatternCommand *pPatternCommand = new CPatternCommand_Shake() ;
	//m_CommandQueue.push(pPatternCommand) ;
}

void CPatternQueueManager::CommandWarning(CDataLoader &DataLoader)
{
	char option[30] ;
	float width, height ;
	float stayTime ;
	
	CPatternCommand *pPatternCommand ;

	DataLoader.GetCommand(option) ;

	if(strcmp(option, "NORMAL")==0)
	{
		POSITION stayPosition ;

		DataLoader.GetValue(width) ;
		DataLoader.GetValue(height) ;
		DataLoader.GetValue(stayPosition.x) ;
		DataLoader.GetValue(stayPosition.y) ;
		DataLoader.GetValue(stayTime) ;

		pPatternCommand = new CPatternCommand_Warning(width, height, stayPosition, stayTime) ;
	}
	else if(strcmp(option, "TRACE")==0)
	{
		float stayAxis ;

		DataLoader.GetCommand(option) ;
		DataLoader.GetValue(width) ;
		DataLoader.GetValue(height) ;
		DataLoader.GetValue(stayAxis) ;
		DataLoader.GetValue(stayTime) ;

		pPatternCommand = new CPatternCommand_Warning(option[0], width, height, stayAxis, stayTime) ;
	}
	else if(strcmp(option, "CHASE")==0)
	{
		float stayAxis ;
		
		DataLoader.GetValue(width) ;
		DataLoader.GetValue(height) ;
		DataLoader.GetValue(stayAxis) ;
		DataLoader.GetValue(stayTime) ;

		pPatternCommand = new CPatternCommand_Warning(width, height, stayAxis, stayTime) ;
	}
	
	m_CommandQueue.push(pPatternCommand) ;
}

void CPatternQueueManager::CommandIrregular(CDataLoader &DataLoader)
{
	char strName[20] ;

	DataLoader.GetString(strName) ;

	CPatternCommand *pPatternCommand = new CPatternCommand_Irregular(strName) ;
	m_CommandQueue.push(pPatternCommand) ;
}