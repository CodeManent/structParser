#ifndef ScriptParser_APT_ComparisonExpression_H_
#define ScriptParser_APT_ComparisonExpression_H_
#pragma once 

#include "BinaryExpression.h"
#include "BooleanExpression.h"

namespace ScriptParser{
	namespace APT{
		/*
		 * A abstract class to represent a comparison between two expressions.
		 */
		class ComparisonExpression: public BooleanExpression, public BinaryExpression
		{
		public:
			ComparisonExpression( std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs)
				: BooleanExpression()
				, BinaryExpression( std::move( lhs ), std::move( rhs ) )
			{
			}

			virtual ~ComparisonExpression()
			{
			}
		};
	}
}

#endif
