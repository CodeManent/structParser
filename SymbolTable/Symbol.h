#ifndef SymbolTable_Symbol_H_
#define SymbolTable_Symbol_H_
#pragma once


namespace SymbolTable{
/*
//TODO: implement data type handling for the symbol table
	namespace DataType{
		class DataType{
		};

		class Struct: public DataType{
		};
	}
*/

	/*
		* A class representing a symbol for the script parser that will be
		* used in the symbol table. All types of symbols that the parser will
		* use, should be a sbclass of this class.
		*
		* TODO: make the class pure abstract class (interface)
		*/
	class Symbol{
	public:
		Symbol(){};				// Create a symbol (shouln't be directly used).
		virtual ~Symbol(){};	// Delete the symbol and release any reserved resouces
	};
}


#endif
