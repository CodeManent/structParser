#ifndef DataParser_H_
#define DataParser_H_
#pragma once

#include "Source/DataSource.h"
#include "SymbolTable/SymbolTable.h"
#include "ScriptParser/APT/TranslationUnit.h"
#include "Visualizer/Box.h"

#include <string>
#include <memory>


/*
* A class that drives the parsing of the data.
* Reads the script from a file and uses the rules to parse the binary file.
*/
class DataParser{
	//TODO: replace void and void* with actual types
public:
	DataParser(const std::string scriptPath = "");
	~DataParser();

	void readDefinitions(const std::string scriptPath);		// Reads the specified script for the parsing rules/struct definitions
	//TODO: change char to actual type
	std::unique_ptr<char> resolveData(
		Source::DataSource &src,
		const std::string startSymbol="init",
		const Source::Size position = 0);					// Parses the specified data stream using the rules from the script

	std::unique_ptr<Visualizer::Box> boxAPT();				// returns the abstract syntaxt tree in a boxed format for visualization

	std::string toString() const;							// Returns a debug/string representation of the object

private:
	void defineBasicTypes();									// Fills the symbol table with some basic types
	SymbolTable::SymbolTable symbolTable_;						// The symbol table containing struct definitions read from the script
	std::unique_ptr<ScriptParser::APT::TranslationUnit> translationUnit;	// The abtract syntaxt tree after parsing the script
};
#endif // !DataParser_H_
