#ifndef ScriptParser_APT_Mod_H_
#define ScriptParser_APT_Mod_H_
#pragma once

#include "BinaryExpression.h"

namespace ScriptParser{
	namespace APT{
		class Mod: public BinaryExpression
		{
		public:
			Mod( std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs )
				:BinaryExpression( std::move( lhs ), std::move( rhs ) )
			{
			}

			virtual ~Mod()
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
