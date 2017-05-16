#ifndef ScriptParser_APT_Add_H_
#define ScriptParser_APT_Add_H_
#pragma once

#include "BinaryExpression.h"

namespace ScriptParser{
	namespace APT{
		class Add: public BinaryExpression
		{
		public:
			Add( std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs )
				:BinaryExpression( std::move( lhs ), std::move( rhs ) )
			{
			}

			virtual ~Add()
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
