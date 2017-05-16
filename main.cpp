#include "Source/FileSource.h"
#include "DataParser.h"
#include "Parameters.h"

#include "Resolved/Integer.h"
#include "Resolved/Byte.h"
#include "Resolved/Struct.h"
#include "Resolved/Array.h"


#include "Visualizer/Visualizer.h"

#include <iostream>
#include <string>
#include <stdexcept>


int main( int argc, char *argv[] )
{
	try{
		Parameters params(argc, argv);

		Source::FileSource src( params.getDataFile() );
		DataParser parser;

		std::clog << "main: Loading definitions" << std::endl;
		parser.readDefinitions( params.getDefinitionsFile() );

		std::clog << "main: Parsing data" << std::endl;
		parser.resolveData(src, params.getStartSymbol() );

		// visualize data
		Visualizer::Visualizer viz( argc, argv );
		viz.setData( parser.boxAPT() );

		viz.go();
		//
	}
	catch( const std::exception &e )
	{
		std::cerr << e.what() << std::endl;		// show the exception
		//throw;								// rethrow it so we can cath it and debug the problem
	}

	// Pause the execution so we can see the result in the console.
	//std::cout << "Press Enter to close the program";
	//std::cin.get();
	return EXIT_SUCCESS;
}
