#include "Visitor.h"
#include "APT.h"

namespace ScriptParser{
	namespace APT{
		void Visitor::visit( TranslationUnit& unit )
		{
			for( auto i = unit.begin(); i !=unit.end();++i )
			{
				(*i)->accept( this );
			}
		}

		void Visitor::visit( StructDefinition& def )
		{
			for( auto i = def.begin(); i != def.end(); ++i )
			{
				(*i)->accept( this );
			}
		}

		void Visitor::visit( Field& field )
		{
			field.inspectType().accept( this );
		}

		void Visitor::visit( Array& array )
		{
			array.inspectType().accept( this );
			array.inspectExpression().accept( this );
		}

		void Visitor::visit( Variable& var)
		{
			//var.inspectType().accept( this ); // TODO: variable type
			var.inspectExpression().accept( this );
		}

		/*
		 * Visits the expression node and the member nodes in the
		 */
		void Visitor::visit( If& ifNode )
		{
			ifNode.inspectExpression()->accept( this );
			for( auto i = ifNode.begin(); i != ifNode.end(); ++i )
			{
				(*i)->accept( this );
			}
		}

		void Visitor::visit( BinaryExpression& binExpr )
		{
			binExpr.inspectLhs().accept( this );
			binExpr.inspectRhs().accept( this );
		}

		void Visitor::visit( Add& add )
		{
			visit( dynamic_cast<BinaryExpression&>( add ) );
		}

		void Visitor::visit( Sub& sub )
		{
			visit( dynamic_cast<BinaryExpression&>( sub ) );
		}

		void Visitor::visit( Mul& mul )
		{
			visit( dynamic_cast<BinaryExpression&>( mul ) );
		}

		void Visitor::visit( Div& div )
		{
			visit( dynamic_cast<BinaryExpression&>( div ) );
		}

		void Visitor::visit( Mod& mod )
		{
			visit( dynamic_cast<BinaryExpression&>( mod ) );
		}

		void Visitor::visit( And& andNode )
		{
			visit( dynamic_cast<BinaryExpression&>( andNode) );
		}

		void Visitor::visit( Or& orNode )
		{
			visit( dynamic_cast<BinaryExpression&>( orNode ) );
		}

		void Visitor::visit( Not& notNode )
		{
			notNode.inspectExpression().accept( this );
		}

		void Visitor::visit( Xor& xorNode )
		{
			visit( dynamic_cast<BinaryExpression&>( xorNode ) );
		}

		void Visitor::visit( Equal& equal )
		{
			visit( dynamic_cast<BinaryExpression&>( equal ) );
		}

		void Visitor::visit( Greater& greater )
		{
			visit( dynamic_cast<BinaryExpression&>( greater ) );
		}

		void Visitor::visit( Lesser& lesser )
		{
			visit( dynamic_cast<BinaryExpression&>( lesser ) );
		}

	}
}