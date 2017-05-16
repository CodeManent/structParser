#include "DataParser.h"
#include "ScriptParser/Driver.h"

#include "APTBoxer.h"
#include "Resolver.h"

#include <iostream>

/*
 * Default constructor.
 * Fills some basic types in the symbol table and reads the script if one is defined.
 */
DataParser::DataParser(const std::string scriptPath)
{
	defineBasicTypes();

	if( scriptPath.length() != 0 )
		readDefinitions( scriptPath );
}

DataParser::~DataParser()
{
}

/*
 * Reads the definitions contained in the specified script file.
 */
void DataParser::readDefinitions( const std::string scriptPath )
{
	//TODO: implement the method
	ScriptParser::Driver parsingDriver( scriptPath );

	translationUnit = std::move( parsingDriver.parse() );

	/*
	//TODO: remove the following block or make it somwhere a method
	//Testing code
	// Formats the and prints it to the console
	{
		std::unique_ptr<ScriptParser::APT::Printer> printer( new ScriptParser::APT::Printer() );

		//The two following lines are functional equivalent.
		//The 2nd one uses one less stack frame

		//translationUnit->accept( printer.get() );
		printer->visit( *translationUnit.get() );

		std::cout << printer->getResult();
	}
	*/
}

/*
 * Drives the parsing of the specified data cource based on the the definitions contained in the symbol table.
 */
std::unique_ptr<char> DataParser::resolveData( Source::DataSource &src, const std::string startSymbol, const Source::Size position)
{
	Resolver resolver( src, startSymbol );
	translationUnit->accept( &resolver );
	//TODO: implement the method and change void
	return nullptr;
}

/*
 * Returns the abstract syntaxt tree in a boxed format for visualization
 */
std::unique_ptr<Visualizer::Box> DataParser::boxAPT()
{
	APTBoxer boxer;
	translationUnit->accept( &boxer );
	
	return boxer.getBoxedTree();
}


std::string DataParser::toString() const
{
	//TODO: implement method
	return "";
}

/*
 * Defines some basic types meeded to parse the script and the data stream.
 * It does so by adding them into the symbol table.
 */
void DataParser::defineBasicTypes()
{
	//TODO: implement method
}
