#include "BossManager.h"
#include <stdio.h>
#include <string.h>

#include "DataLoader.h"
#include "Bounding.h"
#include "Boss.h"

BossManager::BossManager()
{
}
BossManager::~BossManager()
{
	std::map<std::string, CBoss*>::iterator iter, iter_end=m_BossList.end() ;

	for(iter=m_BossList.begin(); iter!=iter_end; iter++)
		delete iter->second ;
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
	BBox box ;

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

			memset(name, NULL, strlen(name)) ;
			memset(image, NULL, strlen(image)) ;
			width = height = 0.0f ;
			box._left = box._top = box._right = box._bottom = 0.0f ;
		}
	}

	DataLoader.CloseData() ;
}

void BossManager::Render()
{
	std::map<std::string, CBoss*>::iterator iter, iter_end=m_BossList.end() ;
	CBoss *pBoss ;

	for(iter=m_BossList.begin(); iter!=iter_end; iter++)
	{
		pBoss = iter->second ;
		pBoss->SetPosition(100.0f, 100.0f) ;
		pBoss->Render() ;
	}
}