#ifndef Parameters_H_
#define Parameters_H_
#pragma once

#include <cstdlib>
#include <iostream>
#include <string>

/*
* A helper class that handles the command line parameters.
* After parsing the parameters, it stores a set of configuration values for the program.
* Default values are set in the constructor.
*/
class Parameters{
public:
	/*
	 * Constructor. Take the command lines arguments and sets the appropriate
	 * variable values in the class.
	 */
	Parameters( int argc, char *argv[] )
		: dataFile( "diablo.bmp" )
		, startSymbol( "BmpFile" )
		, definitionsFile( "test.script" )
		//TODO: remove base path from here and from the methods
		//, basePath( "C:\\Users\\Orion_G\\Documents\\visual studio 2012\\Projects\\StructParser\\StructParser\\Data\\" )
		, basePath("Data/")
	{
		if( argc > 4 || ( argc > 1 && !std::string( argv[1] ).compare( "--help" ) ) )
		{
			printUsage();
			exit( EXIT_FAILURE );
		}

		switch( argc )
		{
		case 4: definitionsFile = argv[3];
			//fallthrough
		case 3: dataFile = argv[2];
			//fallthrough
		case 2: dataFile = argv[1];
			//fallthrough
		default:
			//default parameters
			;
		}
	}

	// Returns the path of the file that will be parsed.
	std::string getDataFile() const
	{
		return basePath + dataFile;
	}

	// Returns the starting symbol that will be used by the parser
	std::string getStartSymbol() const
	{
		return startSymbol;
	}

	// Returns the path of the file htat contains the struct definitions.
	std::string getDefinitionsFile() const
	{
		return basePath + definitionsFile;
	}

	// Prints the usage string to the console.
	void printUsage() const
	{
		std::cout << "usage: structParser [ dataFile [ startSymbol [ definitionsFile ] ] ]" << std::endl;
	}

private:
	std::string dataFile;			// The path of the file that will be parsed.
	std::string startSymbol;		// The starting symbol that will be used by the parser.
	std::string definitionsFile;	// The path of the file that contains the struct definitions (the script).

	std::string basePath;// Debugging helper. Path of the files
};

#endif // !Parameters_H_
