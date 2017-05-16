#ifndef ScriptParser_APT_Div_H_
#define ScriptParser_APT_Div_H_
#pragma once

#include "BinaryExpression.h"

namespace ScriptParser{
	namespace APT{
		class Div: public BinaryExpression
		{
		public:
			Div( std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs )
				:BinaryExpression( std::move( lhs ), std::move( rhs ) )
			{
			}

			virtual ~Div()
			{
			}

			virtual void accept( Visitor* visitor )
			{
				//visit this node
				visitor->visit( *this );
			}
		};
	}
}

#endif
