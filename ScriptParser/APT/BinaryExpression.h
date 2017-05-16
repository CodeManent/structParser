#ifndef ScriptParser_APT_BinaryExpression_H_
#define ScriptParser_ATP_BinaryExpression_H_
#pragma once


#include "Expression.h"
#include "Visitor.h"

#include <memory>

namespace ScriptParser{
	namespace APT{
		class BinaryExpression: public Expression
		{
		public:
			BinaryExpression( std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs )
				: Expression()
				, lhs_( std::move( lhs ) )
				, rhs_( std::move( rhs ) )
			{
			}

			virtual ~BinaryExpression()
			{
			}

			virtual Expression& inspectLhs()
			{
				return *lhs_.get();
			}

			virtual Expression& inspectRhs()
			{
				return *rhs_.get();
			}


			virtual void accept( Visitor* visitor )
			{
				lhs_->accept( visitor );
				rhs_->accept( visitor );
			}

		private:
			std::unique_ptr<Expression> lhs_;
			std::unique_ptr<Expression> rhs_;
		};
	}
}
#endif
 