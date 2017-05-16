#ifndef SymbolTable_Alias_H_
#define SymbolTable_Alias_H_
#pragma once

#include "Symbol.h"


#include <string>

namespace SymbolTable{
	/*
		* A symbol that can be used to create aliasesin the symbol table
		*/
	class Alias: public Symbol
	{
	public:
		Alias(std::string name);
		virtual ~Alias();
		std::string getAlias() const;

	private:
		std::string name_;
	};
}


#endif
