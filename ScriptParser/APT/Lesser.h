#ifndef ScriptParser_APT_Lesser_H_
#define ScriptParser_APT_Lesser_H_
#pragma once

#include "ComparisonExpression.h"

namespace ScriptParser{
	namespace APT{

		class Lesser : public ComparisonExpression
		{
		public:
			Lesser( std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs)
				: ComparisonExpression( std::move( lhs ), std::move( rhs ) )
			{
			}

			virtual ~Lesser()
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
