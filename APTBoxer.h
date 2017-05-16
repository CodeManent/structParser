#ifndef APTBoxer_H_
#define APTBoxer_H_
#pragma once

#include "ScriptParser/APT/Visitor.h"
#include "ScriptParser/APT/APT.h"
#include "Visualizer/Box.h"

#include <vector>
#include <stdexcept>
#include <memory>

class APTBoxer: public ScriptParser::APT::Visitor
{
public:
	// A class that traverses the nodes of the abstract parsing tree and creates a visulaization tree
	APTBoxer()
		: Visitor()
	{
	}

	//if the container stack is not empty, release te contained elements.
	virtual ~APTBoxer()
	{
		for( auto i: containerStack )
		{
			delete i;
		}
	}
	
	virtual void visit( ScriptParser::APT::TranslationUnit& tu )
	{
		Visualizer::Container *cont = new Visualizer::Container();
		containerStack.push_back(cont);

		for( auto i = tu.begin(); i != tu.end(); ++i )
		{
			i->get()->accept( this );
		}
		
		if( containerStack.size() != 1 )
		{
			throw std::runtime_error( "APTBoxer::Visit(TranslationUnit& ): Container stack has more than one elements at the end" );
		}
	}

	virtual void visit( ScriptParser::APT::StructDefinition& sd )
	{
		//create a container
		Visualizer::Container *cont = new Visualizer::Container();
		//add it as a child to the current 
		containerStack.back()->addElelemt( cont );
		//and push it to he stack makin it the current container.
		containerStack.push_back( cont );

		//sizit al the subnodes of the struct definition node, adding them in the graph accordingly
		Visitor::visit( sd );

		//remove current container from the stack
		containerStack.pop_back();
	}
	
	virtual void visit( ScriptParser::APT::Typename& f )
	{
		containerStack.back()->addElelemt( new Visualizer::Field() );
	}

	virtual void visit( ScriptParser::APT::Array& arr )
	{
		{
			auto *cont = new Visualizer::Container();
			containerStack.back()->addElelemt( cont );
			containerStack.push_back( cont );
		}

		auto numExpr = dynamic_cast<ScriptParser::APT::Number *>( &arr.inspectExpression() );
		if( numExpr )
		{
			for( int i = 0; i < numExpr->getValue(); ++i )
			{
				//add copies of the type in the current container
				arr.inspectType().accept( this );
			}
		}


		containerStack.pop_back();
	}

	
	std::unique_ptr<Visualizer::Box> getBoxedTree()
	{
		if( containerStack.size() != 1 )
		{
			throw std::runtime_error( "APTBoxer::getBoxedTree(): The container stack is not in a valid state ( it should have only 1 element )" ) ;
		}
		auto cont = containerStack.back();
		containerStack.pop_back();
		return std::unique_ptr<Visualizer::Box>(cont);

	}


private:
	std::vector<Visualizer::Container*> containerStack;
};


#endif
