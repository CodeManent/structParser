#ifndef ScriptParser_StruceDefinition_H_
#define Scriptparser_StructDefinition_H_
#pragma once

#include "StructMember.h"
#include "Traits.h"
#include "Visitor.h"

#include <string>

namespace ScriptParser{
	namespace APT{
		/*
		 * A structure definition in the script.
		 */
		class StructDefinition: public Type, public Container<StructMember>{
		public:
			StructDefinition( const std::string name )
				: Type( name )
				, Container()
			{
			}

 			virtual ~StructDefinition()
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
