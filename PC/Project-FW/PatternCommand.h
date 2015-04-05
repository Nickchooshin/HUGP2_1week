#pragma once

class CPatternCommand
{
protected :
	bool m_bLife ;

public :
	CPatternCommand() ;
	virtual ~CPatternCommand() ;

	virtual void Update() = 0 ;

	const bool BeLife() const ;
} ;