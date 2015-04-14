#pragma once

#include "Scene.h"
#include <fmod.hpp>

class CSprite ;

class CreditScene : public Scene
{
private :
	CSprite *m_pCredit ;
	
	FMOD::Sound *m_pSESelect ;

public :
	static Scene* scene() ;

	CreditScene() ;
	virtual ~CreditScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;