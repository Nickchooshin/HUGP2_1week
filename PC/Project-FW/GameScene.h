#pragma once

#include "Scene.h"
#include <fmod.hpp>

class CSprite ;
class CCount ;

class GameScene : public Scene
{
private :
	CSprite *m_pBackground ;
	CSprite *m_pBottom, *m_pScore, *m_pText ;

	CCount *m_pCount ;

	float m_fTime ;

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
	void Count() ;
	void GameLoop() ;
} ;