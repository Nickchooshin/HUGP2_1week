#pragma once

#include "Scene.h"
#include <fmod.hpp>

class CSprite ;
class CScoreUI ;

class GameoverScene : public Scene
{
private :
	CSprite *m_pBackground ;
	CSprite *m_pButton[2] ;
	CSprite *m_pRank, *m_pText ;
	CScoreUI *m_pScoreUI ;

	int m_nMenuNum ;
	
	FMOD::Sound *m_pSEMenu, *m_pSESelect ;

public :
	static Scene* scene() ;

	GameoverScene() ;
	virtual ~GameoverScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
private :
	void MenuSelect() ;
} ;