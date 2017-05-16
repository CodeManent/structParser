#ifndef ScriptParser_APT_Typenme_H_
#define ScriptParser_APT_Typename_H_
#pragma once

#include "Traits.h"

namespace ScriptParser{
	namespace APT{
		class Typename: public Type
		{
		public:
			Typename( std::string name )
				: Type( name )
			{
			}

			virtual ~Typename()
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
