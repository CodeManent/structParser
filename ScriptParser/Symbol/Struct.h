#ifndef ScriptParser_Symbol_Struct_H_
#define ScriptParser_Symbol_Struct_H_
#pragma once

#include "Type.h"

namespace ScriptParser{
	namespace Symbol{

		//TODO: fix typeInfo to get a DataType subclass (DataType::Struct). Maybe refactor it
		/*
		 * This class represents a symbol that can be used to represent a 
		 * struct in the symbol table. The actual struct layout (AST) will
		 * be contained in the typeInfo parameter. This class is merely a
		 * placeholder so we can reference the underlying AST with a name.
		 */
		class Struct: public Type{
		public:
			Struct( const DataType &typeInfo );
			virtual ~Struct();
			virtual const DataType& getTypeInfo() const;
		};
	}
}

#endif
