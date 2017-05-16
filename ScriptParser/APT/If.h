#ifndef ScriptParser_APT_If_H_
#define ScriptParser_APT_If_H_
#pragma once

#include "Statement.h"
#include "BooleanExpression.h"
#include "Traits.h"
#include "StructMember.h"
#include "Visitor.h"

#include <memory>

namespace ScriptParser{
	namespace APT{
		class If: public Statement, public Container<StructMember>
		{
		public:
			If( std::unique_ptr<BooleanExpression> expression)
				: Statement()
				, Container()
				, expression_( std::move( expression ) )
			{
			}

			virtual ~If()
			{
			}

			virtual BooleanExpression* inspectExpression() const
			{
				return expression_.get();
			}

			virtual void accept( Visitor *visitor )
			{
				visitor->visit( *this );
			}

		private:
			std::unique_ptr<BooleanExpression> expression_;
		};
	}
}

#endif
