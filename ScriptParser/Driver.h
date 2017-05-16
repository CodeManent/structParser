#ifndef ScriptParser_Driver_H_
#define ScriptParser_Driver_H_
#pragma once

#include "APT/TranslationUnit.h"

#include <string>
#include <stdio.h>
#include <memory>

namespace ScriptParser{
	class Parser;

	/*
	* A class That drives the parsing of the script.
	*/
	class Driver{
		friend class ScriptParser::Parser;
	public:
		Driver(const std::string filename);
		virtual ~Driver();

		// Parses a script
		std::unique_ptr<APT::TranslationUnit> parse();

		// Enables/disables the tracing messages from the lexer and the parser
		void setTracing(bool parsing, bool scanning);

		std::string getFilename();
		
		// Error reporting method to be used from the parser and the scanner
		void error(const std::string message);
	private:
		/* Sets the input file to the flex generated scanner */
		void setScannerInput(FILE* f);

		//handle the scanner
		const std::string file_;			// The file that is curently parsed
		bool traceScanning_;				// Flag that makes the scanning verbose
		bool traceParsing_;					// flag that makes the parsing verbose
		unsigned int parsingErrors_;		// Variable counting the parsing errors for the script
	};
} 

#endif // !ScriptParser_Driver_H_
