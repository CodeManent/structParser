#ifndef ScriptParser_APT_Sub_H_
#define ScriptParser_APT_Sub_H_
#pragma once

#include "BinaryExpression.h"

namespace ScriptParser{
	namespace APT{
		class Sub: public BinaryExpression
		{
		public:
			Sub( std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs )
				:BinaryExpression( std::move( lhs ), std::move( rhs ) )
			{
			}

			virtual ~Sub()
			{
			}

			virtual void accept( Visitor* visitor )
			{
				//visit this node
				visitor->visit( *this );;
			}
		};
	}
}

#endif
