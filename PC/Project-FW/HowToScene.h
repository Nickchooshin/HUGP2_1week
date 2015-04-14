#pragma once

#include "Scene.h"
#include <fmod.hpp>

class CSprite ;

class HowToScene : public Scene
{
private :
	CSprite *m_pHowToPlay ;
	
	FMOD::Sound *m_pSESelect ;

public :
	static Scene* scene() ;

	HowToScene() ;
	virtual ~HowToScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;