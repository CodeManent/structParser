//TODO: reimplement symbol table as scope tree
#include "SymbolTable.h"
#include "Alias.h"

#include <stdexcept>

namespace SymbolTable{

SymbolTable::SymbolTable()
	: predefined_( nullptr )
{
}

/*
 * Destructor
 * The defined symbols are automatically freed by the destructor
 * of the vector which calls the destructor of the pairs which 
 * calls the destructor of the unique_ptr which calls the deleter
 * and frees the memory allocated for the symbol
 */
SymbolTable::~SymbolTable()
{
}

/*
 * Inserts a symbol with a name in the table
 * The ownweship of the symbol is passed to the table
 */
void SymbolTable::insert( const std::string  name, std::unique_ptr<Symbol> symbol )
{
	// table_.push_back( std::make_pair( name, std::move( symbol ) ) );
	table_.emplace_back( std::move( name ), std::move( symbol ) );
}


/*
 * Pushes a scope symbol in the symbol table.
 * The scope is also pushed in the helper scope stack.
 */
void SymbolTable::pushScope( const std::string name )
{
	scopeStack_.push_back( std::make_pair( name, table_.size() ) );
	//insert( std::move( name ), std::unique_ptr<Symbol::Symbol>(new Symbol::Scope) );
}


/*
 * Removes a scope from the symbol table and it's contained symbols
 */
void SymbolTable::popScope()
{
	if( scopeStack_.empty() )
		throw std::runtime_error( "SymbolTable::popScope: Unbalanced scope pop" );

	// Remove symbols defined in the scope
	// Extra symbols are automaitcally deleted by the vector that
	// calls the destructor of the pair
	// The scope symbol is also deleted
	table_.resize( scopeStack_.back().second );

	//remove the scope definition srom the scope stack
	//scopeStack_.pop_back();
}


/*
 * Returns a symbol based on the defined name.
 * If an alias is specified for the current symbol, follow it and
 * return the original symbol. If the symbol isn't in the table,
 * check the prdefined symbols table.
 *
 * An exception is thrown when the symbol cannot be found.
 */
const Symbol& SymbolTable::lookup( const std::string name ) const
{
	std::vector<std::pair<std::string, std::unique_ptr<Symbol>>>::const_reverse_iterator iter;

	for( iter = table_.crbegin(); iter != table_.crend(); ++iter )
	{
		if(name == iter->first)
		{
			if( typeid( iter->second ) == typeid( Alias ) )
			{
				auto alSymbol = dynamic_cast<const Alias * const>( iter->second.get() );

				return lookup( alSymbol->getAlias() );
			}
			return *( iter->second );
		}
	}

	// Symbol not contained in the current table.
	// Look it up in the predefined symbols table (if one is registered)
	if( predefined_ )
		return predefined_->lookup( name );

	// The symbol does not exist in the current table and no
	// predefined symbol table is registeded.
	throw std::runtime_error( "SymbolTable::lookup( \"" + name + "\" ): The specified symbol could not be found" );
}

/*
 * Registers a table with predefined symbols to be used on lookup and merge
 */
void SymbolTable::setPredefined( SymbolTable& predefined )
{
	predefined_ = &predefined;
}


/*
 * Moves the symbols of the current table in the table with the
 * predefined symbols.
 * After the move, the local table is cleared.
 */
void SymbolTable::mergeInPrededined()
{
	if( predefined_ )
	{
		//move the symbols tho the predefined symbols table
		predefined_->table_.insert(
			predefined_->table_.end(),
			std::make_move_iterator( table_.begin() ),
			std::make_move_iterator( table_.end() )
			);
		// and clear the "local" table
		table_.clear();
	}
}


/*
 * Returns an idented string representation of the symbol table.
 */
std::string SymbolTable::toString(const unsigned int identation) const
{
	std::string bumper(identation, '\t');
	std::string result = bumper + "Symbol table{\n";

	if( predefined_ )
	{
		result += bumper + "Predefined:\n";
		result += predefined_->toString(identation + 1);
	}

	for( auto symbol = table_.cbegin(); symbol != table_.end(); ++symbol )
	{
		result += bumper + "\tSymbol: " + symbol->first + '\n';
	}

	result += bumper + "\n}";

	// return value optimization (RVO) should prevent the copying
	return result;
}
}