#ifndef Resolved_Integer_H_
#define Resolved_Integer_H_
#pragma once

#include "Data.h"
#include <vector>
#include <stdexcept>
namespace Resolved{
	/*
	 * Class to represent an integer on the data stream.
	 */
	//TODO: finish the implementation of the integer class ( reding data from the stream )
	class Integer: public Data
	{
	public:
		Integer( bool isSigned, Source::DataSource &source, Source::Size position = 0, unsigned int width = 32 )
			: Data( source, position, Source::Size(0, width ) )
			, isSigned( isSigned )
		{
			if( getSize().storageBytes() > sizeof( long long ) /sizeof( unsigned char ) )
			{
				throw std::runtime_error( "Resolved::Integer(): size is too big (biger than long long )" );
			}
		}

		virtual ~Integer()
		{
		}

		virtual bool hasConstantSize() {
			return true;
		}

		virtual void accept( Visitor* visitor)
		{
			visitor->visit( *this );
		}


		unsigned long long readValue()
		{
			std::vector<unsigned char> buffer( static_cast<size_t>( getSize().storageBytes() ), 0);

			Data::read( &buffer[0] );

			long long retval = 0;
			unsigned char *ptr = reinterpret_cast<unsigned char *>( &retval );
			auto lastByte = sizeof( retval )/sizeof( unsigned char );

			int currentByte = lastByte;
			for( auto buffch = buffer.rbegin(); buffch != buffer.rend() && currentByte > 0; ++buffch )
			{
				ptr[--currentByte] = *buffch;
			}

			if( isSigned )
			{
				//TDOO: sign extend
				//else it's all zeros
			}


			return retval;
		}

		bool isSigned;
	};
}


#endif
