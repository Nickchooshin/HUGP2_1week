#pragma once

#include "Objects.h"

class CBoss : public CObjects
{
public :
	CBoss() ;
	~CBoss() ;

	void Init() ;

	void SetImage(char *strImage) ;
	void SetBoundingBox(BBox Box) ;
} ;