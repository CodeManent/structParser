#ifndef Resolved_Array_H_
#define Resolved_Array_H_
#pragma once

#include "Data.h"

namespace Resolved{
	class Array: public Data
	{
	public:
		Array( Source::DataSource& source, unsigned int size = 0,  Source::Size position = 0)
			: Data( source, position, 0 )
			, size( size )
		{
		}

		virtual ~Array()
		{
		}

		virtual bool hasConstantSize() {
			throw "TODO: Unimplemented";
			return false;
		}

		virtual void accept( Visitor* visitor )
		{
			visitor->visit( *this );
		}

	private:
		unsigned int size;
	};
}

#endif
