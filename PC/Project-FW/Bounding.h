#pragma once

typedef struct _IBounding
{
	enum Type { NONE=0, BOX, CIRCLE, ELLIPSE, LINE } ;
	Type _type ;

	_IBounding(Type type) : _type(type)
	{}
	_IBounding(const _IBounding& b) : _type(b._type)
	{}
} IBounding ;

typedef struct BOUNDING_BOX : public IBounding
{
	float _left, _top ;
	float _right, _bottom ;

	BOUNDING_BOX(float left=0.0f, float top=0.0f, float right=0.0f, float bottom=0.0f) : IBounding(BOX), _left(left), _top(top), _right(right), _bottom(bottom)
	{}
	BOUNDING_BOX(const BOUNDING_BOX &b) : IBounding(b), _left(b._left), _top(b._top), _right(b._right), _bottom(b._bottom)
	{}
} BBOX ;

typedef struct BOUNDING_CIRCLE : public IBounding
{
	float _x, _y ;
	float _radius ;

	BOUNDING_CIRCLE(float x=0.0f, float y=0.0f, float radius=0.0f) : IBounding(CIRCLE), _x(x), _y(y), _radius(radius)
	{}
	BOUNDING_CIRCLE(const BOUNDING_CIRCLE &b) : IBounding(CIRCLE), _x(b._x), _y(b._y), _radius(b._radius)
	{}
} BCIRCLE ;

typedef struct BOUNDING_ELLIPSE : public IBounding
{
	float _x, _y ;
	float _a, _b ;

	BOUNDING_ELLIPSE(float x=0.0f, float y=0.0f, float a=0.0f, float b=0.0f) : IBounding(ELLIPSE), _x(x), _y(y), _a(a), _b(b)
	{}
	BOUNDING_ELLIPSE(const BOUNDING_ELLIPSE &b) : IBounding(ELLIPSE), _x(b._x), _y(b._y), _a(b._a), _b(b._b)
	{}
} BELLIPSE ;

typedef struct BOUNDING_LINE : public IBounding
{
	float _x1, _y1 ;
	float _x2, _y2 ;

	BOUNDING_LINE(float x1=0.0f, float y1=0.0f, float x2=0.0f, float y2=0.0f) : IBounding(LINE), _x1(x1), _y1(y1), _x2(x2), _y2(y2)
	{}
	BOUNDING_LINE(const BOUNDING_LINE &b) : IBounding(LINE), _x1(b._x1), _y1(b._y1), _x2(b._x2), _y2(b._y2)
	{}
} BLINE ;