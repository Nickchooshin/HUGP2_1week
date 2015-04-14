#pragma once

#include "Scene.h"

class CSprite ;

class CreditScene : public Scene
{
private :
	CSprite *m_pCredit ;

public :
	static Scene* scene() ;

	CreditScene() ;
	virtual ~CreditScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;