#ifndef ScriptParser_APT_And_H_
#define ScriptParser_APT_And_H_


#include "BooleanExpression.h"
#include "BinaryExpression.h"
#include "Visitor.h"

#include <memory>

namespace ScriptParser{
	namespace APT{
		/*
		 * A class for the boolean operator "and" in the parsing tree. It is also
		 * a boolean expression as the result of this operator is a boolean value.
		 */
		class And: public BooleanExpression, public BinaryExpression
		{
		public:
			/*
			 * Sets the left hand side and right hand side boolean expressions.
			 */
			And( std::unique_ptr<BooleanExpression> lhs, std::unique_ptr<BooleanExpression> rhs )
				: BooleanExpression()
				, BinaryExpression( std::move( lhs ), std::move( rhs ) )
			{
			}

			virtual ~And()
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
