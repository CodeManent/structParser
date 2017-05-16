#ifndef ScriptParser_APT_Mul_H_
#define ScriptParser_APT_Mul_H_
#pragma once

#include "BinaryExpression.h"

namespace ScriptParser{
	namespace APT{
		class Mul: public BinaryExpression
		{
		public:
			Mul( std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs )
				:BinaryExpression( std::move( lhs ), std::move( rhs ) )
			{
			}

			virtual ~Mul()
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
