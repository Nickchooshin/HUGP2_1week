#pragma once

#include "Scene.h"
#include <fmod.hpp>

class CSprite ;
class CCountUI ;
class CScoreUI ;

class GameScene : public Scene
{
private :
	CSprite *m_pBackground ;
	CSprite *m_pBottom, *m_pText ;

	CCountUI *m_pCountUI ;
	CScoreUI *m_pScoreUI ;
	CSprite *m_pScore, *m_pRank ;

	float m_fTime ;
	float m_fTextX, m_fTextY, m_fTextDirection ;
	int m_nBossNum, m_nPatternNum ;

	FMOD::Sound *m_pBGM ;

	void (GameScene::*m_pfnLoop)(void) ;

public :
	static Scene* scene() ;

	GameScene() ;
	virtual ~GameScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
private :
	void GameLoop() ;

	void Count() ;
	void BackgroundTextMoving() ;
	void Rank() ;
	void NextPattern() ;
} ;