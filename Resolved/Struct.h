#ifndef Resolved_Struct_H_
#define Resolved_Struct_H_
#pragma once

#include "Data.h"
#include <vector>
#include <utility> // for std::pair
#include <string>
#include <iterator>

namespace Resolved{
	class Struct: public Data
	{
	public:
		Struct( Source::DataSource &source, Source::Size position = 0)
			: Data( source, position, 0 )
		{
		}
		virtual ~Struct()
		{
			//delete all the memory holded in the vector
			for( auto i: members )
			{
				delete i.second;
			}
		}

		virtual bool hasConstantSize()
		{
			throw "TODO: Struct::hasConstantSize(): unimplemented";
			return false;
		}

		virtual void accept( Visitor* visitor )
		{
			visitor->visit( *this );
		}

		std::vector<std::pair<std::string, Data* >>::iterator begin()
		{
			return members.begin();
		}

		std::vector<std::pair<std::string, Data* >>::iterator end()
		{
			return members.end();
		}

		void addElelemt( std::string name, Data* data )
		{
			members.emplace_back(name, data);
		}

	private:
		std::vector<std::pair<std::string, Data*>> members;
	};
}

#endif
