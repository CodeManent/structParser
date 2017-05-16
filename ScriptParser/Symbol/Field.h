#ifndef ScriptParser_Symbol_Field_H_
#define ScriptParser_Symbol_Field_H_
#pragma once

#include "../../SymbolTable/Symbol.h"

namespace ScriptParser{
	namespace Symbol{

		/*
		 * A class representing a field of a struct
		 */
		class Field: public SymbolTable::Symbol{
		public:
			~Field(){}
		};
	}
}

#endif
