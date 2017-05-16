#ifndef SymbolTable_Scope_H_
#define SymbolTable_Scope_H_
#pragma once

#include "Symbol.h"

namespace SymbolTable
{
	/*
		* A class representing a scope in the symbol table.
		*/
	class Scope: public Symbol
	{
	public:
		virtual ~Scope(){};

	};
}
#endif
