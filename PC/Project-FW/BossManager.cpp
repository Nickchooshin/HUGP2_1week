#include "BossManager.h"
#include <stdio.h>
#include <string.h>

#include "DataLoader.h"
#include "Bounding.h"
#include "Boss.h"
#include "Pattern.h"

#include "CollisionManager.h"

BossManager::BossManager()
{
}
BossManager::~BossManager()
{
	Clear() ;
}

void BossManager::SetupBoss(char *strBossName)
{
	CDataLoader DataLoader ;
	char filepath[100] ;

	ClearBoss() ;

	sprintf_s(filepath, "Resource/Data/Boss/%s.dat", strBossName) ;
	DataLoader.OpenData(filepath) ;
	
	char item[100] ;
	int len ;
	char name[100], image[100] ;
	float width, height ;
	IBounding *bounding=NULL ;
	int bounding_num ;
	bool collision ;

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
			if(bounding!=NULL)
				delete bounding ;
			
			DataLoader.GetValue(bounding_num) ;
			BBOX *pBox = new BBOX[bounding_num] ;

			for(int i=0; i<bounding_num; i++)
			{
				DataLoader.GetValue(pBox[i]._left) ;
				DataLoader.GetValue(pBox[i]._top) ;
				DataLoader.GetValue(pBox[i]._right) ;
				DataLoader.GetValue(pBox[i]._bottom) ;
			}

			bounding = pBox ;
		}
		else if(len==15 && strcmp(item, "BOUNDING_CIRCLE")==0)
		{
			if(bounding!=NULL)
				delete bounding ;
			
			DataLoader.GetValue(bounding_num) ;
			BCIRCLE *pCircle = new BCIRCLE[bounding_num] ;

			for(int i=0; i<bounding_num; i++)
			{
				DataLoader.GetValue(pCircle[i]._x) ;
				DataLoader.GetValue(pCircle[i]._y) ;
				DataLoader.GetValue(pCircle[i]._radius) ;
			}

			bounding = pCircle ;
		}
		else if(len==16 && strcmp(item, "BOUNDING_ELLIPSE")==0)
		{
			if(bounding!=NULL)
				delete bounding ;
			
			DataLoader.GetValue(bounding_num) ;
			BELLIPSE *pEllipse = new BELLIPSE[bounding_num] ;
			
			for(int i=0; i<bounding_num; i++)
			{
				DataLoader.GetValue(pEllipse[i]._x) ;
				DataLoader.GetValue(pEllipse[i]._y) ;
				DataLoader.GetValue(pEllipse[i]._a) ;
				DataLoader.GetValue(pEllipse[i]._b) ;
			}

			bounding = pEllipse ;
		}
		else if(len==13 && strcmp(item, "BOUNDING_LINE")==0)
		{
			if(bounding!=NULL)
				delete bounding ;

			DataLoader.GetValue(bounding_num) ;
			BLINE *pLine = new BLINE[bounding_num] ;

			for(int i=0; i<bounding_num; i++)
			{
				DataLoader.GetValue(pLine[i]._x1) ;
				DataLoader.GetValue(pLine[i]._y1) ;
				DataLoader.GetValue(pLine[i]._x2) ;
				DataLoader.GetValue(pLine[i]._y2) ;
			}
			
			bounding = pLine ;
		}
		else if(len==9 && strcmp(item, "COLLISION")==0)
		{
			int temp ;

			DataLoader.GetValue(temp) ;
			collision = (bool)temp ;
		}
		else if(len==3 && strcmp(item, "END")==0)
		{
			CBoss *pBoss = new CBoss ;
			pBoss->Init() ;
			pBoss->SetImage(image) ;
			pBoss->SetBounding(bounding, bounding_num) ;
			pBoss->SetCollision(collision) ;

			m_BossList[name] = pBoss ;

			memset(name, 0, strlen(name)) ;
			memset(image, 0, strlen(image)) ;
			width = height = 0.0f ;
			bounding = NULL ;
			bounding_num = 0 ;
			collision = false ;
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

	g_CollisionManager->AddObject(pBoss) ;

	return pBoss ;
}

void BossManager::Clear()
{
	ClearBoss() ;
	ClearPattern() ;
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

void BossManager::ClearBoss()
{
	if(m_BossList.empty())
		return ;

	std::map<std::string, CBoss*>::iterator iter, iter_end=m_BossList.end() ;

	for(iter=m_BossList.begin(); iter!=iter_end; iter++)
		delete iter->second ;
	m_BossList.clear() ;
}

void BossManager::ClearPattern()
{
	if(m_PatternList.empty())
		return ;

	std::vector<CPattern*>::iterator iter, iter_end=m_PatternList.end() ;

	for(iter=m_PatternList.begin(); iter!=iter_end; iter++)
		delete *iter ;
	m_PatternList.clear() ;
}