#pragma once

typedef struct _IBounding
{
} Bounding ;

typedef struct _BoundingBox : public Bounding
{
	int _left, _top ;
	int _right, _bottom ;

	_BoundingBox(int left=0, int top=0, int right=0, int bottom=0) : _left(left), _top(top), _right(right), _bottom(bottom)
	{}
} BoundingBox, BBox ;

typedef struct _BoundingCircle : public Bounding
{
	int _x, _y ;
	float _radius ;

	_BoundingCircle(int x=0, int y=0, float radius=0.0f) : _x(x), _y(y), _radius(radius)
	{}
} BoundingCircle, BCircle ;