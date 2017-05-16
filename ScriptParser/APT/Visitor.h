#ifndef ScriptParser_APT_Visitor_H_
#define ScriptParser_APT_Visitor_H_
#pragma once

namespace ScriptParser{
	namespace APT{
		class TranslationUnit;

		class StructDefinition;
		class StructMember;

		class Type;
		class Typename;

		class Field;
		class Array;
		class Variable;
		class If;

		class Expression;
		class Number;
		class Identifier;
		class BinaryExpression;
		class Add;
		class Sub;
		class Mul;
		class Div;
		class Mod;

		class BooleanExpression;
		class BooleanValue;
		class And;
		class Or;
		class Xor;
		class Not;

		class Equal;
		class Greater;
		class Lesser;


		/*
		 * A base class to help us implement the visitor pattern on the abstract
		 * parsing tree. The default action is to do nothing. The actual functionality
		 * is implemented in the subclasses on a per node basis. Not all methods need
		 * to be overriden. Only the ones that are needed. For all the other, the
		 * default action will be taken ( doing nothing ).
		 */
		class Visitor
		{
		public:
			Visitor()
			{
			}

			virtual ~Visitor()
			{
			}

			virtual void visit( TranslationUnit&	);

			virtual void visit( StructDefinition&	);
			//virtual void visit( StructMember&		) {}

			//virtual void visit( Type&				) {}
			virtual void visit( Typename&			) {}

			virtual void visit( Field&				);
			virtual void visit( Array&				);
			virtual void visit( Variable&			);
			virtual void visit( If&					);

			//virtual void visit( Expression&		) {}
			virtual void visit( Number&				) {}
			virtual void visit( Identifier&			) {}
			virtual void visit( BinaryExpression&	);
			virtual void visit( Add&				);
			virtual void visit( Sub&				);
			virtual void visit( Mul&				);
			virtual void visit( Div&				);
			virtual void visit( Mod&				);

			//virtual void visit( BooleanExpression&	) {}
			virtual void visit( BooleanValue&		) {}
			virtual void visit( And&				);
			virtual void visit( Or&					);
			virtual void visit( Not&				);
			virtual void visit( Xor&				);

			virtual void visit( Equal&				);
			virtual void visit( Greater&			);
			virtual void visit( Lesser&				);
		};
	}
}
#endif
