#include "Alias.h"

namespace SymbolTable{
	Alias::Alias(std::string name)
		: Symbol()
		, name_( name )
	{
	}

	Alias::~Alias()
	{
	}

	std::string Alias::getAlias() const
	{
		return name_;
	}
}
