#ifndef ScriptParser_APT_Equals_H_
#define ScriptParser_APT_Equals_H_
#pragma once

#include "ComparisonExpression.h"

namespace ScriptParser{
	namespace APT{
		/*
		 * A class to represent the equality operator in the abstract parsing tree.
		 */
		class Equal : public ComparisonExpression
		{
		public:
			Equal( std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs)
				: ComparisonExpression( std::move( lhs ), std::move( rhs ) )
			{
			}

			virtual ~Equal()
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
