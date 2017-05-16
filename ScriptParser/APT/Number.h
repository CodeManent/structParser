#ifndef ScriptParser_APT_Number_H_
#define ScriptParser_APT_Number_H_
#pragma once

#include "Expression.h"

namespace ScriptParser{
	namespace APT{
		/*
		 * A class that represents a number (long) in the script
		 */
		class Number : public Expression
		{
		public:
			Number( long value )
				: Expression()
				, value_( value )
			{
			}

			virtual ~Number()
			{
			}

			// Returns the current calue.
			virtual long getValue() const
			{
				return value_;
			}

			// Sets a new value.
			virtual void setValue( long value )
			{
				value_ = value;
			}

			virtual void accept( Visitor * visitor )
			{
				visitor->visit( *this );
			}

		private:
			// Member containing the actual stored value.
			long value_;
		};
	}
}
#endif
