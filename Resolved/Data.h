#ifndef Resolved_Data_H_
#define Resolved_Data_H_
#pragma once

#include "../Source/DataSource.h"
#include "../Source/Size.h"

#include "Visitor.h"



namespace Resolved{
	/*
	 * Abstract class representing a portion of data in the data a stream;
	 * The class also holds the type information for the pointied data.
	 */
	class Data{
	public:
		Data(Source::DataSource & source, Source::Size position = 0, Source::Size size = 0)
			: source( source )
			, position( position )
			, size( size )
		{
		}

		virtual ~Data()
		{
		}

		virtual Source::Size getSize(){
			return size;
		}

		virtual Source::Size getPosition(){
			return position;
		}

		virtual void setSize( const Source::Size& newSize ){
			size = newSize;
		}
		virtual void setPosition( const Source::Size& newPosition){
			position = newPosition;
		}

		virtual Source::DataSource& getSource()
		{
			return source;
		}

		virtual void read( void* buffer )
		{
			Source::DataSource& src = getSource();
			src.seek( getPosition() );
			src.read( getSize(), buffer );
		}

		// Returns true when the size of the data type is dependent on the actual data.
		virtual bool hasConstantSize() = 0;
		
		//Helper method to implement the visitor pattern
		virtual void accept( Visitor* ) = 0;

	private:
		Source::DataSource &source;
		Source::Size position;
		Source::Size size;
	};
}
#endif
