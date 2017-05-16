#ifndef ScriptParser_APT_Field_H_
#define ScriptParser_APT_Field_H_
#pragma once

#include "StructMember.h"
#include "Traits.h"
#include "Visitor.h"

#include <memory>

namespace ScriptParser{
	namespace APT{
		/*
		 * Class that represents a field of a struct. 
		 */
		class Field: public StructMember, public Named, public Typed
		{
		public:
			Field( std::string name, std::unique_ptr<Type> type)
				: StructMember()
				, Named( name )
				, Typed( std::move( type ) )
			{
			}

			virtual ~Field()
			{
			}

			/*
			 * Helper method for the visitor pattern.
			 */
			virtual void accept( Visitor * visitor )
			{
				visitor->visit( *this );
			}
		};
	}
}

#endif
