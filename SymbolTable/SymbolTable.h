#ifndef SymbolTable_SymbolTable_H_
#define SymbolTable_SymbolTable_H_
#pragma once


#include "Symbol.h"

#include <string>
#include <vector>
#include <utility>	// for pair
#include <memory>	// for unique_ptr


namespace SymbolTable{
	/*
	* A class that represents he symbol table for the Script parser
	*/
	class SymbolTable{
	public:
		SymbolTable();
		virtual ~SymbolTable();

		virtual void insert( const std::string name, std::unique_ptr<Symbol> symbol);	// Adds a symbol in the table
		virtual const Symbol& lookup( const std::string name ) const;					// Returns a reference to a symbol by name

		virtual void setPredefined( SymbolTable& predefined );				// Sets a Sets a symbol table with predefined symbols to use on lookup
		virtual void mergeInPrededined();									// Pushes the symbols in the current table in the table of predefined symbols

		virtual void pushScope( const std::string name = "" );				// Adds a scope (can be named) in the symbol table
		virtual void popScope();											// Removes a scope from the symbolTable and it's contained sumbols

		virtual std::string toString(const unsigned int identation = 0) const;			// Retuerns a possibly idented string representation if the symbol table and it's contained symbols

	private:
		std::vector<std::pair<std::string, unsigned int >> scopeStack_;					// A helper table that containes the scope frames (a name and it's posiiton in the symbol table)
		std::vector<std::pair<std::string, std::unique_ptr<Symbol>>> table_;	// The actual table that contains the symbols and stack frames
		SymbolTable* predefined_;											// The table with the predefined Symbols
	};
}


#endif
