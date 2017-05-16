#ifndef ScriptParser_APT_Variable_H_
#define ScriptParser_APT_Variable_H_
#pragma once

#include "StructMember.h"
#include "Expression.h"
#include "Traits.h"
#include "Visitor.h"

#include <string>
#include <memory>

namespace ScriptParser{
	namespace APT{
		class Variable: public StructMember, public Named, public Typed
		{
		public:
			Variable( std::string name, std::unique_ptr<Expression> expression)
				: StructMember()
				, Named( name )
				//, Typed( std::move( type ) )
				, Typed( nullptr )
				, expression_( std::move( expression ) )
			{
			}

			virtual ~Variable()
			{
			}

			virtual Expression& inspectExpression()
			{
				return *expression_.get();
			}

			virtual void accept( Visitor * visitor )
			{
				visitor->visit( *this );
			}

		private:
			std::unique_ptr<Expression> expression_;
		};
	}
}

#endif
