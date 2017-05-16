#include "Visualizer.h"

#include <GL/glew.h>
#include <GL/glut.h>

#include <stdexcept>

Visualizer::Visualizer *Visualizer::Visualizer::currentVisualizer = nullptr;

void display( void ){
	Visualizer::Visualizer::currentVisualizer->draw();
}


namespace Visualizer{
	Visualizer::Visualizer( int& argc, char *argv[] )
		: winId( 0 )
		, displayData( nullptr )
	{
		if( currentVisualizer != nullptr )
		{
			throw std::runtime_error( "Visualizer: Only one instance is allowed at any time" );
		}

		glutInit( &argc, argv );
		glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );

		glutInitWindowSize( 640, 480 );
		winId = glutCreateWindow( "Struct parser visualizer" );

		glutDisplayFunc( display );

		glClearColor( 0.75f, 0.5f, 0.6f, 0.5f );
		//glViewport( 0, 0, 800, 600 );

		setData( nullptr );

		currentVisualizer = this;
	}

	void Visualizer::go() const
	{
		glutMainLoop();
	}

	//seth the datat to display an also sets the camera
	void Visualizer::setData( std::unique_ptr<Box> data )
	{
		this->displayData = std::move( data );

		if( !displayData )
		{
			//set a test scene
			Container *gtp = new Container();
			gtp->addElelemt( new Field() );
			gtp->addElelemt( new Field() );
			{
				Container *c2 = new Container();
				for( unsigned int i= 0; i < 10; ++i )
				{
					c2->addElelemt( new Field() );
				}


				gtp->addElelemt( c2 );
			}

			gtp->addElelemt( new Field() );
			for( int i = 0; i < 30; ++i )
			{
				gtp->addElelemt( new Field() );
			}


			displayData.reset( gtp );
		}

		if( displayData )
		{
			//set the projection matrix
			displayData->calculateHalfSize();
			displayData->setPosition( Point2f() );

			const Point2f size = displayData->getHalfSize() + Point2f( 1.0f, 1.0f ) ;
			glMatrixMode( GL_PROJECTION );
				//TODO: FIX: use aspect ratio
				glLoadIdentity();
				float biggerSide = std::max( size.x, size.y );

				if( size.x < size.y ) 
				{
					gluOrtho2D(-biggerSide, biggerSide, biggerSide, -biggerSide);
				}

				//gluOrtho2D( -size.x, size.x, size.y, -size.y );
			glMatrixMode( GL_MODELVIEW );

			glutPostRedisplay();
		}
	}

	void Visualizer::draw() const
	{
		checkGL();
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		if( displayData )
		{
			displayData->draw();
		}

		glutSwapBuffers();

		checkGL();
	}

	void Visualizer::checkGL() const
	{
		GLenum err = GL_NO_ERROR;
		std::string errStr;
		int count = 0;

		while( ( err = glGetError() ) != GL_NO_ERROR )
		{
			if( count )
			{
				errStr += '\n';
			}

			++count;
			errStr += "OpenGL Error: ";
			switch( err )
			{
			case GL_INVALID_ENUM:
				errStr += "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
				break;

			case GL_INVALID_VALUE:
				errStr += "GL_INVALID_VALUE: A numeric argument is out of range.";
				break;

			case GL_INVALID_OPERATION:
				errStr += "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
				break;

			case GL_STACK_OVERFLOW:
				errStr += "GL_STACK_OVERFLOW: The function caused a stack overflow.";
				break;

			case GL_STACK_UNDERFLOW:
				errStr += "GL_STACK_UNDERFLOW: The function caused a stack underflow.";
				break;

			case GL_OUT_OF_MEMORY:
				errStr += "GL_OUT_OF_MEMORY: There is not enough memory left to execute the function.";
				break;

			case GL_TABLE_TOO_LARGE:
				errStr += "GL_TABLE_TOO_LARGE: The specified table exceeds the implementation's maximum supported table size.";
				break;

			default:
				errStr += "Onspecified OpenGL Error";
			}
		}

		if( count )
		{
			throw std::runtime_error( errStr );
		}
	}

}
