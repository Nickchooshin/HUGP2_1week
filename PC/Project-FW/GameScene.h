#pragma once

#include "Scene.h"

class CSprite ;
//class CHero ;

class GameScene : public Scene
{
private :
	CSprite *m_pBackground ;
	CSprite *m_pCount ;

	//CHero *m_pHero ;

	float m_fTime ;

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