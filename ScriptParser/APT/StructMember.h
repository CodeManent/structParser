#ifndef ScriptParser_StructMember_H_
#define ScriptParser_StructMember_H_
#pragma once

#include "Visitor.h"

#include <string>

namespace ScriptParser{
	namespace APT{
		/*
		 * An abstract base class representing a member of a struct.
		 */
		class StructMember{
		public:
			StructMember()
			{
			}

			virtual ~StructMember()
			{
			}

			// Returns in string form a representation of the actual struct member.
			virtual void accept( Visitor* visitor ) = 0;
		};
	}
}

#endif