#pragma once

#include "Scene.h"

class CSprite ;
class CUISprite ;

class SampleScene : public Scene
{
private :
	CSprite *m_pSprite1, *m_pSprite2 ;
	CUISprite *m_pUISprite1, *m_pUISprite2 ;

public :
	static Scene* scene() ;

	SampleScene() ;
	virtual ~SampleScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;