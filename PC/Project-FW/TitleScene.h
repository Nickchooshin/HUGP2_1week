#pragma once

#include "Scene.h"

class CSprite ;

class TitleScene : public Scene
{
private :
	CSprite *m_pBackground ;
	CSprite *m_pButton[3] ;

	int m_nMenuNum ;

public :
	static Scene* scene() ;

	TitleScene() ;
	virtual ~TitleScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
private :
	void MenuSelect() ;
} ;