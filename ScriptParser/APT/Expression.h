#ifndef ScriptParser_APT_Expression_H_
#define ScriptParser_APT_Expression_H_
#pragma once

#include "Visitor.h"

#include <string>

namespace ScriptParser{
	namespace APT{
		/*
		 * A class representing an expression in the APT
		 * TODO: must add type to expressions and type deductions
		 */
		class Expression
		{
		public:
			Expression()
			{
			}

			virtual ~Expression()
			{
			}

			virtual void accept( Visitor * visitor ) = 0;
		};
	}
}

#endif
