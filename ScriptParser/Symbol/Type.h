#ifndef ScriptParser_Symbol_Type_H_
#define ScriptParser_Symbol_Type_H_
#pragma once

#include "../../SymbolTable/Symbol.h"
#include "DataType.h"

namespace ScriptParser{
	namespace Symbol{
		/*
		 * Superclass for all the symbols that contain a type.
		 */
		class Type : public SymbolTable::Symbol{
		public:
			Type( const DataType &typeInfo )
				: typeInfo_( typeInfo )
			{
			}
			virtual ~Type(){};
			virtual const DataType& getTypeInfo() const //= 0
			{
				return typeInfo_;
			}

		private:
			const DataType &typeInfo_;
		};
	}
}

#endif
