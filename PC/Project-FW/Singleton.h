#pragma once

template <class T>
class Singleton
{
public :
	static T* GetInstance()
	{
		static T Instance ;

		return &Instance ;
	}
} ;