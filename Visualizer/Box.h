#ifndef Visualizer_Box_H_
#define Visualizer_Bob_H_
#pragma once

#include <vector>
#include <memory>

struct Point2f
{
	float x, y;
	Point2f( float x = 0, float y = 0): x(x), y(y){}
	Point2f operator+( const Point2f& p2 ) const{
		return Point2f( x + p2.x, y + p2.y );
	}
	Point2f operator-( const Point2f& p2 ) const{
		return Point2f( x - p2.x, y - p2.y );
	}
	Point2f operator*( const Point2f& p2 )const{
		return Point2f( x * p2.x, y * p2.y );
	}
	Point2f operator*( const float f ) const{
		return Point2f( x * f, y * f );
	}

	Point2f operator/( const Point2f& p2 ) const{
		return Point2f( x/p2.x, y/p2.y );
	}
	Point2f operator/( const float f ) const{
		return Point2f( x/f, y/f );
	}
};

namespace Visualizer{
	class Box
	{
	public:
		Box( const Point2f& position = Point2f(), const Point2f& halfSize = Point2f())
			: position( position )
			, halfSize( halfSize )
		{
		}

		virtual ~Box()
		{
		}

		virtual void calculateHalfSize() = 0;
		virtual void setPosition( const Point2f& position ){
			this->position = position;
		}

		virtual void setHalfSize( const Point2f& halfSize ){
			this->halfSize = halfSize;
		}

		virtual Point2f getPosition() const {
			return position;
		}

		virtual Point2f getHalfSize() const {
			return halfSize;
		}

		virtual void draw() const = 0;

	private:
		Point2f position;
		Point2f halfSize;
	};

	class Field: public Box
	{
	public:
		Field()
			: Box( 0.0f, Point2f( 1.0f, 0.5f ) )
		{
		}

		virtual ~Field()
		{
		}

		virtual void calculateHalfSize()
		{
		}

		virtual void draw() const;
	};

	class Container: public Box
	{
	public:
		Container()
			: Box()
		{
		}

		virtual ~Container()
		{
		}

		virtual void calculateHalfSize();
		virtual void setPosition( const Point2f& );
		virtual void draw() const;
		virtual void addElelemt( Box* );

	private:
		std::vector<std::unique_ptr<Box>> elements;
		static const Point2f separator;

	};
}

#endif
