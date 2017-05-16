#ifndef ScriptParser_APT_SemanticAnalyzer_H_
#define ScriptParser_APT_SemanticAnalyzer_H_
#pragma once

#include "Visitor.h"
#include "../../SymbolTable/SymbolTable.h"

namespace ScriptParser{
	namespace APT{
		/*
		 * A visitor for the parsing tree that verifies whether the semantics of the
		 * nodes conform to the language.
		 */
		class SemanticAnalyzer: public Visitor
		{
		public:
			SemanticAnalyzer();
			~SemanticAnalyzer();

			virtual void visit( StructDefinition&	);
			
			virtual void visit( Typename&			);
			virtual void visit( Field&				);
			virtual void visit( Array&				);
			virtual void visit( Variable&			);

			const SymbolTable::SymbolTable& inspectTable() const
			{
				return table;
			}

		private:
			SymbolTable::SymbolTable table;
		};
	}
}

#endif
