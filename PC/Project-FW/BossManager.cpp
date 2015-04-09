#include "BossManager.h"
#include <stdio.h>
#include <string.h>

#include "DataLoader.h"
#include "Bounding.h"
#include "Boss.h"
#include "Pattern.h"

BossManager::BossManager()
{
}
BossManager::~BossManager()
{
	std::map<std::string, CBoss*>::iterator iter_boss ;
	std::vector<CPattern*>::iterator iter_pattern ;

	for(iter_boss=m_BossList.begin(); iter_boss!=m_BossList.end(); iter_boss++)
		delete iter_boss->second ;

	for(iter_pattern=m_PatternList.begin(); iter_pattern!=m_PatternList.end(); iter_pattern++)
		delete *iter_pattern ;
}

void BossManager::SetupBoss(char *strBossName)
{
	CDataLoader DataLoader ;
	char filepath[100] ;

	sprintf_s(filepath, "Resource/Data/Boss/%s.dat", strBossName) ;
	DataLoader.OpenData(filepath) ;
	
	char item[100] ;
	int len ;
	char name[100], image[100] ;
	float width, height ;
	BBOX box ;

	while(DataLoader.GetItem(item))
	{
		len = strlen(item) ;

		if(len==4)
		{
			if(strcmp(item, "NAME")==0)
			{
				DataLoader.GetString(name) ;
			}
			else if(strcmp(item, "SIZE")==0)
			{
				DataLoader.GetValue(width) ;
				DataLoader.GetValue(height) ;
			}
		}
		else if(len==5 && strcmp(item, "IMAGE")==0)
		{
			DataLoader.GetString(image) ;
		}
		else if(len==12 && strcmp(item, "BOUNDING_BOX")==0)
		{
			DataLoader.GetValue(box._left) ;
			DataLoader.GetValue(box._top) ;
			DataLoader.GetValue(box._right) ;
			DataLoader.GetValue(box._bottom) ;
		}
		else if(len==3 && strcmp(item, "END")==0)
		{
			CBoss *pBoss = new CBoss ;
			pBoss->Init() ;
			pBoss->SetImage(image) ;
			pBoss->SetBoundingBox(box) ;

			m_BossList[name] = pBoss ;

			memset(name, 0, strlen(name)) ;
			memset(image, 0, strlen(image)) ;
			width = height = 0.0f ;
			box._left = box._top = box._right = box._bottom = 0.0f ;
		}
	}

	DataLoader.CloseData() ;
}

void BossManager::AddPattern(CPattern *pPattern)
{
	m_PatternList.push_back(pPattern) ;
}

CBoss* BossManager::GetBossInstance(std::string name)
{
	CBoss *pBoss = new CBoss(m_BossList[name]) ;

	return pBoss ;
}

void BossManager::Update()
{
	int num=m_PatternList.size() ;
	CPattern *pPattern ;

	for(int i=0; i<num; i++)
	{
		pPattern = m_PatternList[i] ;
		pPattern->Update() ;

		if(!pPattern->BeLife())
		{
			m_PatternList.erase(m_PatternList.begin() + i) ;
			delete pPattern ;
			--num ;
			--i ;
		}
	}
}

void BossManager::Render()
{
	const int num=m_PatternList.size() ;
	CPattern *pPattern ;

	for(int i=0; i<num; i++)
	{
		pPattern = m_PatternList[i] ;
		pPattern->Render() ;
	}
}