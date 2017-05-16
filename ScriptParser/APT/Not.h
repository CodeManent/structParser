#ifndef StructParser_APT_Not_H_
#define StructParser_APT_Not_H_
#pragma once

#include "BooleanExpression.h"
#include "Visitor.h"

#include <memory>

namespace ScriptParser{
	namespace APT{
		/*
		 * A class for the boolean operator "not" in the parsing tree. It is also
		 * a boolean expression as the result of this operator is a boolean value.
		 */
		class Not: public BooleanExpression
		{
		public:
			/*
			 * Sets the expression to negate.
			 */
			Not( std::unique_ptr<BooleanExpression> expression )
				: BooleanExpression()
				, expression_( std::move( expression ) )
			{
			}

			virtual ~Not()
			{
			}

			/*
			 * Helper method that returns the boolean expression to negate.
			 * The return value is a reference to the actual contained expression.
			 */
			BooleanExpression& inspectExpression()
			{
				return *expression_.get();
			}

			/*
			 * Helper method for the visitor pattern. 
			 */
			virtual void accept( Visitor *visitor )
			{
				visitor->visit( *this );
			}

		private:
			std::unique_ptr<BooleanExpression> expression_;

		};
	}
}

#endif
