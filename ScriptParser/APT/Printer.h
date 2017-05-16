#ifndef ScriptParser_APT_Printer_H_
#define ScriptParser_Apt_Printer_H_
#pragma once

#include "Visitor.h"
#include "APT.h"

#include <string>
#include <sstream>

#define bumper std::string( identation_, '\t' )

namespace ScriptParser{
	namespace APT{
		/*
		 * A visitor that pretty-prints the input script to the console.
		 */
		class Printer: public Visitor
		{
		public:
			Printer()
				:identation_( 0 )
			{
			}

			virtual ~Printer()
			{
			}

			virtual void visit( TranslationUnit& unit ) override
			{
				result_ +=  bumper + "Translation Unit {\n";
				++identation_;
				for( auto i = unit.begin(); i != unit.end(); ++i )
				{
					(*i)->accept( this );
					result_ += '\n';
				}
				--identation_;
				result_ += bumper + '}';
			}

			virtual void visit( StructDefinition& sd ) override
			{
				result_ += bumper + "struct " + sd.getName() + " {\n";
				++identation_;
				for( auto i = sd.begin(); i != sd.end(); ++i )
				{
					(*i)->accept( this );
					result_ += '\n';
				}
				--identation_;
				result_ += bumper + "}";
			}

			virtual void visit( Array& array) override
			{
				//print the type
				array.inspectType().accept( this );

				result_ += ' ' + array.getName() + " [ ";
				array.inspectExpression().accept( this );
				result_ += " ];";
			}

			virtual void visit( Field& field ) override
			{
				field.inspectType().accept( this );
				result_ += ' ' + field.getName() + ';';
			}

			virtual void visit( Typename& tname ) override
			{
				result_ += bumper + tname.getName();
			}

			virtual void visit ( Number& number ) override
			{
				std::ostringstream oss;
				oss << number.getValue() << ' ';

				result_ += oss.str();
			}

			virtual void visit( Identifier& id ) override
			{
				result_ += id.getName();
			}

			virtual void visit( Variable& var ) override
			{
				result_ += bumper +  "var " + var.getName() + " = ";
				var.inspectExpression().accept( this );
				result_ += ';';
			}
			
			virtual void visit( If& ifStatement) override
			{
				result_ += bumper + "if ( ";
				ifStatement.inspectExpression()->accept( this );
				result_ +=  "){\n";
				++identation_;
				for( auto i = ifStatement.begin(); i != ifStatement.end(); ++i )
				{
					(*i)->accept( this );
					result_ += '\n';
				}
				--identation_;
				result_ += bumper + "}";

			}

			virtual void visit( Add& ) override
			{
				result_ += "+ ";
			}

			virtual void visit( Sub& ) override
			{
				result_ += "- ";
			}

			virtual void visit( Mul& ) override
			{
				result_ += "* ";
			}

			virtual void visit( Div * ) override
			{
				result_ += "/ ";
			}

			virtual void visit( Mod& ) override
			{
				result_ += "% ";
			}

			virtual void visit( BooleanValue& boolVal ) override
			{
				result_ += boolVal.getValue() ? "true " : "false ";
			}

			virtual void visit( And& ) override
			{
				result_ += "&& ";
			}

			virtual void visit( Or& ) override
			{
				result_ += "|| ";
			}

			virtual void visit( Not& ) override
			{
				result_ += "! ";
			}

			virtual void visit( Xor& ) override
			{
				result_ += "^ ";
			}

			virtual void visit( Equal& ) override
			{
				result_ += "== ";
			}

			virtual void visit( Greater& ) override
			{
				result_ += "> ";
			}

			virtual void visit( Lesser& ) override
			{
				result_ += "< ";
			}



			std::string getResult() const
			{
				return result_;
			}


		private:
			unsigned int identation_;
			std::string result_;
		};
	}
}

#endif
