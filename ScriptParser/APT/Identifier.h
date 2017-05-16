#ifndef ScriptParser_APT_Identifier_H_
#define ScriptParser_APT_Identifier_H_
#pragma once

#include "Expression.h"
#include "Traits.h"
#include "Visitor.h"

namespace ScriptParser{
	namespace APT{
		class Identifier: public Expression, public Named
		{
		public:
			Identifier( std::string name )
				: Expression()
				, Named( name )
			{
			}

			virtual ~Identifier()
			{
			}

			virtual void accept( Visitor * visitor )
			{
				visitor->visit( *this );
			}
		};
	}
}
#endif
