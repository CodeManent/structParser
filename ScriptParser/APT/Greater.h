#ifndef ScriptParser_APT_Greater_H_
#define ScriptParser_APT_Greater_H_
#pragma once

#include "ComparisonExpression.h"

namespace ScriptParser{
	namespace APT{

		class Greater : public ComparisonExpression
		{
		public:
			Greater( std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs)
				: ComparisonExpression( std::move( lhs ), std::move( rhs ) )
			{
			}

			virtual ~Greater()
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
