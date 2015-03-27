#pragma once

#include "Scene.h"

class CSprite ;

class TitleScene : public Scene
{
private :
	CSprite *m_pBackground ;
	CSprite *m_pStart, *m_pGrade, *m_pCredit, *m_pExit ;
	CSprite *m_pPointer ;

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