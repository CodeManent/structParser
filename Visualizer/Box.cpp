#include "Box.h"

#include <GL/glew.h>
#include <GL/glut.h>

namespace Visualizer{

	const Point2f Container::separator = Point2f( 0.5f, 0.5f );

	void Field::draw() const
	{
		//top-left point
		const Point2f tl = getPosition() - getHalfSize();
		//bottom-right point
		const Point2f br = getPosition() + getHalfSize();

		glColor3f( .7f, .2f, .2f );

		glBegin( GL_QUADS );
			glVertex2f( tl.x, tl.y );
			glVertex2f( tl.x, br.y );
			glVertex2f( br.x, br.y );
			glVertex2f( br.x, tl.y );
		glEnd();
	}

	/* Add a box into the container
	 * the pointer will be passed to an unique_ptr into the vector
	 * So the pointed memory is now owned by the container
	 */
	void Container::addElelemt( Box* b )
	{
		elements.emplace_back( b );
	}

	void Container::calculateHalfSize()
	{
		float maxX = 0.0f;
		float sumY = 0.0f;

		for( auto element = elements.begin(); element != elements.end(); ++element )
		{
			element->get()->calculateHalfSize();
			
			const Point2f halfSize = element->get()->getHalfSize();
			if( maxX < halfSize.x )
			{
				maxX = halfSize.x;
			}

			sumY += halfSize.y;
		}

		setHalfSize( Point2f( maxX + separator.x, sumY + (elements.size()+1)*separator.y/2.0f ) );
	}

	void Container::setPosition( const Point2f& newPosition )
	{
		//set the position for the current box
		Box::setPosition( newPosition );

		//and then set the position for all the containedelements
		const Point2f halfSize = getHalfSize();

		float x = newPosition.x;
		float y = newPosition.y - halfSize.y;

		for( auto element = elements.begin(); element != elements.end(); ++element )
		{
			const float elemHalfY = element->get()->getHalfSize().y;

			y += separator.y + elemHalfY;
			element->get()->setPosition( Point2f( x, y ) );
			y += elemHalfY;
		}
	}

	void Container::draw() const
	{
		{
			// put it in a scope so the variables get erased from the stack before
			// the cal to the contianed elements
			const Point2f tl = getPosition() - getHalfSize();
			const Point2f br = getPosition() + getHalfSize();

			//glColor3f( 0.5f, 0.5f, 0.5f );
			glColor3f( 1.0f, 1.0f, 1.0f );

			glBegin( GL_LINE_LOOP );
				glVertex2f( tl.x, tl.y );
				glVertex2f( tl.x, br.y );
				glVertex2f( br.x, br.y );
				glVertex2f( br.x, tl.y );
			glEnd();
		}

		for( auto element = elements.begin(); element != elements.end(); ++element )
		{
			element->get()->draw();
		}
	}
}