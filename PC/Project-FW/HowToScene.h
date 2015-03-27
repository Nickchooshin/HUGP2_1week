#pragma once

#include "Scene.h"

class CSprite ;

class HowToScene : public Scene
{
private :
	CSprite *m_pHowToPlay ;

public :
	static Scene* scene() ;

	HowToScene() ;
	virtual ~HowToScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;