#pragma once

typedef struct _IBounding
{
} Bounding ;

typedef struct _BoundingBox : public Bounding
{
	float _left, _top ;
	float _right, _bottom ;

	_BoundingBox(float left=0.0f, float top=0.0f, float right=0.0f, float bottom=0.0f) : _left(left), _top(top), _right(right), _bottom(bottom)
	{}
} BoundingBox, BBox ;

typedef struct _BoundingCircle : public Bounding
{
	float _x, _y ;
	float _radius ;

	_BoundingCircle(float x=0.0f, float y=0.0f, float radius=0.0f) : _x(x), _y(y), _radius(radius)
	{}
} BoundingCircle, BCircle ;