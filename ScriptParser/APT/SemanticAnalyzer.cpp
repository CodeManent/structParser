//TODO: complete the semantic analyzer
//TODO: add a type checking/ deduction system
#include "SemanticAnalyzer.h"
#include "APT.h"
#include "Expression.h"

#include "../../SymbolTable/Symbol.h"
#include "../Symbols.h"

#include <iostream>
#include <stdexcept>
#include <memory>

namespace ScriptParser{
	namespace APT{
		/*
		 * Constructor for the semantic analyzer class.
		 * It defines some basic data type to be used for the type validation of te abstract parsing tree.
		 // TODO: maybe i should refactor the type system and tie it with the resut tree
		 */
		SemanticAnalyzer::SemanticAnalyzer()
			: Visitor()
		{
			table.insert( "u32" , std::unique_ptr<SymbolTable::Symbol>( new Symbol::POD( Symbol::DataType() ) ) );
			table.insert( "i32" , std::unique_ptr<SymbolTable::Symbol>( new Symbol::POD( Symbol::DataType() ) ) );
			table.insert( "u16" , std::unique_ptr<SymbolTable::Symbol>( new Symbol::POD( Symbol::DataType() ) ) );
			table.insert( "i16" , std::unique_ptr<SymbolTable::Symbol>( new Symbol::POD( Symbol::DataType() ) ) );
			table.insert( "char", std::unique_ptr<SymbolTable::Symbol>( new Symbol::POD( Symbol::DataType() ) ) );
		}


		/*
		 * Semantic analuzer destructor
		 * The sumbol table will autoatically destroyed by it's destructor.
		 */
		SemanticAnalyzer::~SemanticAnalyzer()
		{
		}


		/*
		 * Semantic analusis for a StructDefinition node of the APT
		 * Adds a struct symbol to the stack, and continues the analusis on
		 * it's scoped childer nodes.
		 */
		void SemanticAnalyzer::visit( StructDefinition& def )
		{
			table.insert( def.getName(), std::unique_ptr<SymbolTable::Symbol>( new Symbol::Struct( Symbol::DataType() ) ) );
			table.pushScope( def.getName() );

			Visitor::visit( def );

			table.popScope();
		}



		/*
		* Semantic analysis for a Typename node
		* Checks if a type with the given name exists in the symbol table
		*/
		void SemanticAnalyzer::visit( Typename& typeName )
		{
			try{
				//check if symbol is in the symbol table
				const SymbolTable::Symbol &s = table.lookup( typeName.getName() );

				//check that returnde symbol is a type symbol
				dynamic_cast<const Symbol::Type&>( s ); // throws std::bad_cast exception
			}
			catch( const std::exception &e )
			{
				throw std::runtime_error( std::string("SemanticAnalyzer: Typename is not defined: ") + e.what() );
			}
		}

		// Check the type and insert in the symbol table the field
		void SemanticAnalyzer::visit( Field& field )
		{
			//define a new struct or verify the typename
			field.inspectType().accept( this );
			table.insert( field.getName(), std::unique_ptr<SymbolTable::Symbol>( new Symbol::Field() ) );
		}

		void SemanticAnalyzer::visit( Array& array )
		{
			// Visit the type and the expression
			Visitor::visit( array );

			//TODO: FIXME: replace field with array
			table.insert( array.getName(), std::unique_ptr<SymbolTable::Symbol>( new Symbol::Field ) );
		}

		void SemanticAnalyzer::visit( Variable& var )
		{
			var.inspectExpression().accept( this );
			// TODO: var.setType( /* magial deduct type function*/( var.inspectExpression() )  );
		}
	}
}