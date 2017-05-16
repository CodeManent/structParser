#ifndef Resolved_Byte_H_
#define Resolved_Byte_H_
#pragma once

#include "Data.h"

#include <vector>

namespace Resolved{
	/*
	 * Class to represent a byte (8-bit value) in the data stream
	 */
	class Byte: public Data
	{
	public:
		Byte( Source::DataSource &source, Source::Size position)
			: Data( source, position, Source::Size( 0, 8 ) )
		{
		}

		virtual ~Byte()
		{
		}

		virtual bool hasConstantSize(){
			return true;
		}

		virtual void accept( Visitor* visitor)
		{
			visitor->visit( *this );
		}

		/*
		 * Reads the byte from the data stream (at the position defined in the class) and returns it.
		 */
		unsigned char readValue()
		{
			unsigned char retVal;
			Data::read( &retVal );
			return retVal;
		}

	};
}


#endif
