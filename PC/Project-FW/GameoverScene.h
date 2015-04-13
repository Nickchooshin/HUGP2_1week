#pragma once

#include "Scene.h"

class CSprite ;

class GameoverScene : public Scene
{
private :
	CSprite *m_pBackground ;

public :
	static Scene* scene() ;

	GameoverScene() ;
	virtual ~GameoverScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;