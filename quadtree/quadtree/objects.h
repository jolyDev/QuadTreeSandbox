#pragma once

#include "export.h"
#include <memory>

template<typename TType>
class Point2d
{
public:
	TType x = 0;
	TType y = 0;

	Point2d operator+(const Point2d& other)
	{
		return { x + other.x, y + other.y };
	}

	Point2d operator-(const Point2d& other)
	{
		return { x - other.x, y - other.y };
	}

	Point2d operator*(const TType& k)
	{
		return { k * x, k * y };
	}

	Point2d operator/(const TType& k)
	{
		return Point2d{ x / k, y / k };
	}
};

template<typename TType>
class BBox
{
public:
	BBox(Point2d<TType> center, Point2d<TType> size)
		: center(center)
		, size(size)
	{}

	Point2d<TType> center;
	Point2d<TType> size;

	bool Contains(const Point2d<TType> point)
	{
		auto f_is_in_bounds = [](TType val, TType low, TType high) -> bool
		{
			return val >= low && val <= high;
		};

		return f_is_in_bounds(point.x, center.x - size.x, center.x + size.x)
			&& f_is_in_bounds(point.y, center.y - size.y, center.y + size.y);
	}

	bool Intersects(const std::unique_ptr<BBox>& other)
	{
		return Contains({ other->center.x + other->size.x, other->center.y + other->size.y })
			|| Contains({ other->center.x - other->size.x, other->center.y - other->size.y })
			|| Contains({ other->center.x + other->size.x, other->center.y - other->size.y })
			|| Contains({ other->center.x - other->size.x, other->center.y + other->size.y });
	}
};

class DLIB_EXPORT Object
{
public:
	BBox<float> bbox;
};

class DLIB_EXPORT Rectangle : public Object
{};

class DLIB_EXPORT Circle : public Object
{};