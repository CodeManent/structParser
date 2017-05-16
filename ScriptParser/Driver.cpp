//TODO: migrate to a c++ input method 
#define _CRT_SECURE_NO_WARNINGS 1

#include "Driver.h"
#include "Parser.tab.hh"
#include "APT/SemanticAnalyzer.h"
//#include "APT/Printer2.h"			// TODO: delete, used for debugging

#include <stdio.h> // FILE* for flex scanner input
#include <iostream>
#include <memory> //for unique_ptr
#include <stdexcept>

namespace ScriptParser{
Driver::Driver(const std::string filename)
	: file_( filename )
	, traceScanning_( false )
	, traceParsing_( false )
	, parsingErrors_( 0 )
{
}

Driver::~Driver()
{
}

/*
 * Method that initiates the parsing of the script
 * Open the file to be used by the scanner and invokes the parser.
 */
std::unique_ptr<APT::TranslationUnit> Driver::parse()
{
	//open the script file
	//will automatically close while exiting the current method
	// after scanning/parsing it
	struct fileCloser{
		void operator() (FILE *f){
			if( f ) fclose(f);
		}
	};
	std::unique_ptr<FILE, fileCloser> inFile( fopen(file_.c_str(), "r") );
	if( !inFile )
		throw std::runtime_error( "Driver::parse(): Couldn't open input file " + file_ );

	// Set the file to be used by the flex generated scanner
	setScannerInput( inFile.get() );
	
	std::unique_ptr<APT::TranslationUnit> translationUnit( new APT::TranslationUnit() );

	//Parser the script file
	{
		// Create a parsing object
		Parser parser(*this, *translationUnit.get() );

		//enable the debugging information
		//parser.set_debug_level( traceParsing_ );


		//and parse the file
		const int status = parser.parse();

		// At this point, the parser may have successfully parsed the script, but there
		// may be (recoverable) errors in the script.
		if( status || parsingErrors_ != 0 )
			throw std::runtime_error( "Driver::parse(): Parsing of file \"" + file_ + "\" failed" );
	}

	/*
	{
		APT::Printer2 printer;
		translationUnit->accept( &printer );
		std::cout << "Driver::parse()\n" <<  printer.getResult() << std::endl;
	}
	*/
	//Verify the semantics of the parsing tree nodes
	{
		std::clog << "Driver::parse(): Performing semantic analyzation of the parsing tree" << std::endl;
		APT::SemanticAnalyzer analyzer;
		translationUnit->accept( &analyzer );
		std::cout << "Driver::parse():\n" << analyzer.inspectTable().toString() << std::endl;
	}

	return translationUnit;
}

/* Enables/disables the debug logging at the console from parsing and scanning */
void Driver::setTracing(bool parsing, bool scanning)
{
	traceParsing_ = parsing;
	traceScanning_ = scanning;
}

/* Returns the file name of the path registered for scanning/parsing */
std::string Driver::getFilename()
{
	return file_;
}


void Driver::error(const std::string message)
{
	//TODO: better reporting of parsing errors
	std::cerr << message << std::endl;
	++parsingErrors_;
	//throw std::runtime_error( message );
}

} // ScriptParser