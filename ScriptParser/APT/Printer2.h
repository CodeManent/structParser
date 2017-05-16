#ifndef ScriptParser_APT_Printer2_H_
#define Scriptparser_APT_Printer2_H_

#include "Visitor.h"
#include "APT.h"

#include <iostream>
#include <string>

#define bumper std::string( identation_, '\t' )

namespace ScriptParser{
	namespace APT{
		class Printer2: public Visitor
		{
		public:
			Printer2()
				: Visitor()
				, identation_( 0 )
				, result_( "" )
			{
			}

			virtual ~Printer2()
			{
			}


			virtual void visit( TranslationUnit& unit )
			{
				result_ += bumper + "Translation Unit {\n";
				++identation_;
				Visitor::visit( unit );
				--identation_;
				result_ += bumper +  "}\n";
			}

			virtual void visit( StructDefinition& sd )
			{
				result_ += bumper + "struct " + sd.getName() + " {\n";
				++identation_;
				Visitor::visit( sd );
				--identation_;
				result_ += bumper + "}\n";
			}

			virtual void visit( Typename& typeName )
			{
				result_ += bumper + typeName.getName() + ' ';
			}

			virtual void visit( Field& field )
			{
				//first print the type information
				field.inspectType().accept( this );
				if( !dynamic_cast<Typename*>( &field.inspectType() ) )
				{
					result_ += bumper;
				}
				result_ += field.getName() + ";\n";
			}

			virtual void visit( Array& array )
			{
				array.inspectType().accept( this );
				result_ += array.getName() + " [ ";
				array.inspectExpression().accept( this );
				result_ += "];\n";
			}


			virtual void visit( Variable& var )
			{
				result_ += bumper + "var " + var.getName() + " = ";
				var.inspectExpression().accept( this );
				result_ += ";\n";
			}

			virtual void visit( If& ifNode )
			{
				result_ += bumper + "if( ";
				ifNode.inspectExpression()->accept( this );
				result_ += ") {\n";
				++identation_;
				for( auto i = ifNode.begin(); i != ifNode.end(); ++i )
				{
					(*i)->accept( this );
				}
				--identation_;
				result_ += bumper + "}\n";
			}

			void visit( Number& number)
			{
				char buffer[1024];
				itoa( number.getValue(), buffer, 10 );
				result_ += buffer;
				result_ += " ";
			}

			virtual void visit( Identifier& i)
			{
				result_ += i.getName() + ' ';
			}

			void visit( Add& add )
			{
				add.inspectLhs().accept( this );
				result_ += "+ ";
				add.inspectRhs().accept( this );
			}

			void visit( Sub& sub )
			{
				sub.inspectLhs().accept( this );
				result_ += "- ";
				sub.inspectRhs().accept( this );
			}

			void visit( Mul& mul )
			{
				mul.inspectLhs().accept( this );
				result_ += "* ";
				mul.inspectRhs().accept( this );
			}

			void visit( Div& div)
			{
				div.inspectLhs().accept( this );
				result_ += "/ ";
				div.inspectRhs().accept( this );
			}

			void visit( Mod& mod)
			{
				mod.inspectLhs().accept( this );
				result_ += "/ ";
				mod.inspectRhs().accept( this );
			}


			virtual void visit( BooleanValue& bv )
			{
				result_ += (bv.getValue() ? "true " : "false ");
			}

			void visit( And& andNode)
			{
				andNode.inspectLhs().accept( this );
				result_ += "&& ";
				andNode.inspectRhs().accept( this );
			}

			void visit( Or& orNode)
			{
				orNode.inspectLhs().accept( this );
				result_ += "|| ";
				orNode.inspectRhs().accept( this );
			}

			void visit( Not& notNode )
			{
				result_ += "! ";
				notNode.inspectExpression().accept( this );
			}

			void visit( Xor& xorNode)
			{
				xorNode.inspectLhs().accept( this );
				result_ += "/ ";
				xorNode.inspectRhs().accept( this );
			}

			void visit( Equal& equal)
			{
				equal.inspectLhs().accept( this );
				result_ += "== ";
				equal.inspectRhs().accept( this );
			}

			void visit( Greater& greater)
			{
				greater.inspectLhs().accept( this );
				result_ += "> ";
				greater.inspectRhs().accept( this );
			}
			
			
			void visit( Lesser& lesser)
			{
				lesser.inspectLhs().accept( this );
				result_ += "/ ";
				lesser.inspectRhs().accept( this );
			}

			std::string getResult() const
			{
				return result_;
			}
			void itoa(long int getValue, char[1024] buffer, int arg3);
			void itoa(long int getValue, char[1024] buffer, int arg3);
			void itoa(long int getValue, char[1024] buffer, int arg3);
			void itoa(long int getValue, char[1024] buffer, int arg3);
			void itoa(long int getValue, char[1024] buffer, int arg3);
			void itoa(long int getValue, char[1024] buffer, int arg3);

		private:
			unsigned int identation_;
			std::string result_;
			void itoa(long int getValue, char[1024] buffer, int arg3);
		};
	}
}


#endif
