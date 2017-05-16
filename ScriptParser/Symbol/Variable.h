#ifndef ScriptParser_Symbol_Variable_H_
#define ScriptParser_Symbol_Variable_H_
#pragma once

#include "../../SymbolTable/Symbol.h"

namespace ScriptParser{
	namespace Symbol{
		/*
		 * This class represents a variable in the script. It is used so we can reference
		 * it by name so we can construct the AST for the container (struct) that it resides.
		 *
		 * TODO: maybe a type should be associated with it, we'll see.
		 */
		class Variable : public SymbolTable::Symbol{
		public:
			virtual ~Variable(){}
		};
	}
}

#endif
