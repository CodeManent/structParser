#ifndef StructParser_APT_Xor_H_
#define StructParser_APT_Xor_H_
#pragma once

#include "BooleanExpression.h"
#include "BinaryExpression.h"
#include "Visitor.h"

#include <memory>

namespace ScriptParser{
	namespace APT{
		/*
		 * A class for the boolean operator "xor" in the parsing tree. It is also
		 * a boolean expression as the result of this operator is a boolean value.
		 */
		class Xor: public BooleanExpression, public BinaryExpression
		{
		public:
			/*
			 * Sets the left hand side and right hand side boolean expressions.
			 */
			Xor( std::unique_ptr<BooleanExpression> lhs, std::unique_ptr<BooleanExpression> rhs )
				: BooleanExpression()
				, BinaryExpression( std::move( lhs ), std::move( rhs ) )
			{
			}

			virtual ~Xor()
			{
			}

			/*
			 * Helper method for the visitor pattern. 
			 */
			virtual void accept( Visitor *visitor )
			{
				visitor->visit( *this );
			}

		};
	}
}

#endif
