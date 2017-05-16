#ifndef ScriptParser_APT_BiileanExpression_H_
#define ScriptpPrser_APT_BooleanExpression_H_
#pragma once

#include "Expression.h"

namespace ScriptParser{
	namespace APT{
		/*
		 * Abstract class to represent a boolean expression of the parsing tree.
		 */
		class BooleanExpression: public Expression
		{
		public:
			BooleanExpression()
				: Expression()
			{
			}

			virtual ~BooleanExpression()
			{
			}
		};
	}
}

#endif
