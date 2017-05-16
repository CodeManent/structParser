#ifndef ScriptParser_APT_BooleanValue_H_
#define ScriptParser_APT_BooleanValue_H_
#pragma once

#include "BooleanExpression.h"

namespace ScriptParser{
	namespace APT{
		class BooleanValue: public BooleanExpression
		{
		public:
			BooleanValue( bool value )
				: BooleanExpression()
				, value_( value )
			{
			}

			virtual ~BooleanValue()
			{
			}

			virtual bool getValue() const
			{
				return value_;
			}

			virtual void setValue( bool value )
			{
				value_ = value;
			}

			virtual void accept( Visitor* visitor )
			{
				visitor->visit( *this );
			}

		private:
			bool value_;
		};
	}
}


#endif