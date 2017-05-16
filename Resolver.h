#ifndef Resolver_H_
#define Resolver_H_
#pragma once

#include "ScriptParser/APT/Visitor.h"
#include "ScriptParser/APT/APT.h"
#include "Resolved/Resolved.h"
#include "Source/DataSource.h"

#include <string>
#include <vector>
#include <utility>

class Resolver: public ScriptParser::APT::Visitor
{
public:
	//TODO: implement resolver/parser
	Resolver(Source::DataSource& source, std::string startSymbol)
		: Visitor()
		, source( source )
		, startSymbol( startSymbol )
	{
		stack.emplace_back( startSymbol, new Resolved::Struct( source, source.tell() ) );
	}

	virtual ~Resolver()
	{
	}

	virtual void resolve()
	{
		// add a struct into the stack so there is a valid element to hold the data
		stack.emplace_back( startSymbol, new Resolved::Struct( source, source.tell() ) );
		// get the stating struct definitnio maybe from a symbol table
		//parse the struct by visiting it
	}

	virtual void visit( ScriptParser::APT::StructDefinition& sd )
	{
		// put it in it's its scope so the execution stack is freed when we visit
		// the struct's members
		{
			auto newStruct = new Resolved::Struct( source, source.tell() );
			stack.back()->addElelemt( sd.getName(),  newStruct );
			stack.emplace_back( sd.getName(), newStruct );
		}

		for( auto i = sd.begin(); i != sd.end(); ++i )
		{
			//visit all the members of hte struct and arse them accordingly
			(*i)->accept( this );
		}
		// calculate and update the size of the struct
		// pop the current struct form the stack

		stack.pop_back();
	}

	virtual void visit( ScriptParser::APT::Field& field )
	{
		// TODO: implement
		// get type name form symbol
		// retrieve type definition from symbol table
		// parse type definition 
		// field.inspectType().getName();
		// add field to the last struct on the stack
	}

	virtual void visit( ScriptParser::APT::Array& array )
	{
		//TODO: implement
		// calculate range/size
		// get type definition
		// if type has constan size just allocate the nodes
		// else allocate/parse the nodes to create them with the appropriate size
		//calculate and update the size of the array
	}




private:
	Source::DataSource& source;
	std::string startSymbol;
	std::vector<Resolved::Struct*> stack;	// the container stack
};



#endif
