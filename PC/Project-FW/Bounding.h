#pragma once

typedef struct _IBounding
{
} IBounding ;

typedef struct BOUNDING_BOX : public IBounding
{
	float _left, _top ;
	float _right, _bottom ;

	BOUNDING_BOX(float left=0.0f, float top=0.0f, float right=0.0f, float bottom=0.0f) : _left(left), _top(top), _right(right), _bottom(bottom)
	{}
} BBOX ;

typedef struct BOUNDING_CIRCLE : public IBounding
{
	float _x, _y ;
	float _radius ;

	BOUNDING_CIRCLE(float x=0.0f, float y=0.0f, float radius=0.0f) : _x(x), _y(y), _radius(radius)
	{}
} BCIRCLE ;

typedef struct BOUNDING_LINE : public IBounding
{
	float _x1, _y1 ;
	float _x2, _y2 ;

	BOUNDING_LINE(float x1=0.0f, float y1=0.0f, float x2=0.0f, float y2=0.0f) : _x1(x1), _y1(y1), _x2(x2), _y2(y2)
	{}
} BLINE ;