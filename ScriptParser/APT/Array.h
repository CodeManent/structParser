#ifndef ScriptParser_APT_Array_H_
#define ScriptParser_APT_Array_H_
#pragma once

#include "StructMember.h"
#include "Traits.h"
#include "Expression.h"
#include "Visitor.h"

#include <string>
#include <memory>

namespace ScriptParser{
	namespace APT{
		/*
		 * A class representing an array in the script.
		 */
		class Array : public StructMember, public Named, public Typed
		{
		public:
			Array( std::string name, std::unique_ptr<Type> type,  std::unique_ptr<Expression> expression )
				: StructMember()
				, Named( name )
				, Typed( std::move( type ))
				, expression_( std::move( expression ) )
			{
			}

			virtual ~Array()
			{
			}

			virtual void accept( Visitor * visitor )
			{
				visitor->visit( *this );
			}

			virtual Expression& inspectExpression() const
			{
				return *expression_.get();
			}

		private:
			//The expression in the brackets
			std::unique_ptr<Expression> expression_;
		};
	}
}

#endif
