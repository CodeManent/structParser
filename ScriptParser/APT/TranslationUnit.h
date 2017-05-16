#ifndef ScriptParser_TranslationUnit_H_
#define ScriptParser_TranslationUnit_H_
#pragma once

#include "StructDefinition.h"
#include "Visitor.h"

#include <vector>
#include <memory>


namespace ScriptParser{
	namespace APT{
		/*
		 * A class that represents the main node of the result after parsing a
		 * file/translation unit.
		 * It contians the defined structs and possibly some declarations (not implemented yes)
		 */
		class TranslationUnit{
		public:
			TranslationUnit()
			{
			}

			virtual ~TranslationUnit()
			{
			}

			virtual void importDefinitions( std::vector<std::unique_ptr<StructDefinition>> & definitions )
			{
				auto iter = definitions.begin();
				auto end = definitions.end();

				for( ; iter !=end; ++iter )
				{
					definitions_.push_back( std::move( *iter ) );
				}

				definitions.clear();
			}

			typedef std::vector<std::unique_ptr<StructDefinition>>::iterator iterator;
			iterator begin()
			{
				return definitions_.begin();
			}

			iterator end()
			{
				return definitions_.end();
			}


			virtual void accept( Visitor * visitor )
			{
				visitor->visit( *this );
			}


		private:
			// The List of the defined structs in the script
			std::vector<std::unique_ptr<StructDefinition> > definitions_;

			// The list of declarations in the script		//TOOD: do we want declarations?
			//std::vector<std::unique_ptr<Declaration> > declarations_;
		};
	}
}

#endif
