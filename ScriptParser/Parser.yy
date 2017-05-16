// TODO: better error handling and memory management on errors. Now it throws access violations. Maybe because of the implied deletions of the recovery rules or the incomplete types.
/*
 * Bison source file that generates the parser to use in C++.
 * The parser needs a companion lexer. In this project, It is genetared with 
 * flex from the file Scanner.l.
 * 
 * After invoking Bison, the following files are generated:
 *		location.hh		- Locations for Bison parser in C++
 *		Parser.tab.cc	- Implementation for the Bison LALR(1) parser in C++
 *		Parser.tab.hh	- interface for Bison LALR(1) parsers in C++
 *		position.hh		- Positions for Bison parsers in C++
 *		stack.hh		- Stack handling for Bison parsers in C++
 *
 * The main class of the parser is ScriptParser::Parser (defined in Parser.tab.hh)
 * The tokens that the lexer must generate to feed the parser are defined in the
 * enum StructParser::Parser::token::yytokenType (in Parser.tab.hh)
 */
 
%require "2.4.1"
%skeleton "lalr1.cc"

/* Write a Header file containing the token defines */
%defines

/* Set the lanuage to C++ */
%language "C++"

/* Set the namespace to ScriptParser instead of the default yy */
%define namespace "ScriptParser"

/* Set the class name to be Parser */
%define parser_class_name "Parser"

/* Enable debugging and verbose error messages */
%debug
%error-verbose

/* Track the locatinons of the tokens at the input file */
%locations




%code requires{
// This code will be insertd in the header file Parser.tab.hh

// The names "yylval_param" and "yylloc_param" are needed for the
// flex-bison bridge (through the bison-brigde option in the scanner )

#define YY_DECL\
	ScriptParser::Parser::token_type \
	yylex( \
		ScriptParser::Parser::semantic_type *yylval_param, \
		ScriptParser::Parser::location_type *yylloc_param \
	)

// Forward declaratinos of types to be used in the constructor
namespace ScriptParser{
	class Driver;
	namespace APT{
		class TranslationUnit;
	}
}

// Include the abstract parsing tree node definitions
#include "APT/APT.h"

}


//The parameners that will be used for the constuctor of the Parser object

%parse-param { Driver &driver }
%parse-param { APT::TranslationUnit &translationUnit }


%initial-action
{
	//initialize the filename for the location tracking
	@$.begin.filename = @$.end.filename = &driver.getFilename();
}

// Semantic values vannot use "real" objects but only pointers to them
// because the data are stored in a union instead a class or a struct
%union
{
	long																ival;
	std::string*														sval;
	std::vector<std::unique_ptr<ScriptParser::APT::StructDefinition>>*	structDefinitionList;
	ScriptParser::APT::StructDefinition*								structDefinition;
	std::vector<std::unique_ptr<ScriptParser::APT::StructMember>>*		structMembersList;
	ScriptParser::APT::StructMember*									structMember;
	ScriptParser::APT::Type*											type;
	ScriptParser::APT::Field*											field;
	ScriptParser::APT::Array*											array;
	ScriptParser::APT::Variable*										variable;
	ScriptParser::APT::Statement*										statement;
	ScriptParser::APT::If*												ifStatement;

	ScriptParser::APT::Expression*										expression;
	ScriptParser::APT::BooleanExpression*								booleanExpression;
}

//%token ID actual value "descriptive name for debugging"
%token END 0 "end_of_file"
%token <sval> BAD_CHAR

%token LPAR "(" RPAR ")" LBR "{" RBR "}" LSBR "[" RSBR "]" SEMICOLON ";" DOT "." AT "@"

%token IF "if" ELSE "else" STRUCT "struct" VAR "var"

%token TRUE "true" FALSE "false"

%token ADD "+" SUB "-" MUL "*" DIV "/" MOD "%"
%token ASSIGN "="

%token AND "&&" OR "||" XOR "^" NOT "!"
%token EQ "==" NOTEQ "!=" GREATER ">" LESSER "<" GREATEREQ ">=" LESSEREQ "<="

%token <sval> IDENTIFIER "identifier"
%token <ival> NUMBER     "number"

%type <structDefinitionList>	struct_definition_list;
%type <structDefinition>		struct_definition;
%type <structMembersList>		struct_members_list;
%type <structMember>			struct_member;
%type <type>					field_type;

%type <field>					field_definition;
%type <array>					array_definition;
%type <variable>				variable_definition;
%type <statement>				statement;
%type <ifStatement>				if_statement;

%type <expression>				expression;
%type <booleanExpression>		boolean_expression;
%type <booleanExpression>		comparison_expression;



/* Memory deallocation during recovery */
%printer	{ debug_stream() << *$$;	} "identifier"
%destructor	{ delete $$;				} "identifier"

%printer	{ debug_stream() << $$;		} "number"

%printer	{ debug_stream() << *$$;	} BAD_CHAR
%destructor	{ delete $$;				} BAD_CHAR



//set the start token
%start translation_unit

%left "=";
%left "+" "-";
%left "/" "*";
%left "%";
%right UNIMUS;
%right "!";
%nonassoc "||" "&&" "^";
%nonassoc "==" "!=" ">" "<" ">=" "<=";

%code{
#include <string>
#include <sstream>
#include <iostream>
#include <memory>

#include "Driver.h"

YY_DECL;

using namespace ScriptParser::APT;

}

%%

translation_unit
	: struct_definition_list declaration
		{
			translationUnit.importDefinitions( *$1 );

		}
	;

declaration
	: /* empty */
	;

struct_definition_list
	: struct_definition struct_definition_list
		{
			// Insert definition at the beginning of hte table
			$2->insert( $2->begin() ,  std::unique_ptr<StructDefinition>( $1 ) );
			$$ = $2;
		}
	| /* empty */
		{
			$$ = new std::vector<std::unique_ptr<StructDefinition>>();
		}
	;
	
struct_definition
	: "struct" "identifier"
	"{" struct_members_list "}"
		{
			// dereference $2 because is std::string*
			$$ = new StructDefinition( *$2 );
			$$->append( *$4 );
		}
	;

struct_members_list
	: struct_member struct_members_list
		{
			// add the element to the beginning of the list
			$2->insert( $2->begin(), std::unique_ptr<StructMember>( $1 ) );
			$$ = $2;
		}
	| /* empty */
		{
			//create an empty vector
			$$ = new std::vector<std::unique_ptr<StructMember>>();
		}
	| error
		{
			$$ = new std::vector<std::unique_ptr<StructMember>>();
		}

	;

struct_member
	: field_definition ";"
		{
			$$ = $1;
		}
	| array_definition ";"
		{
			$$ = $1;
		}
	| variable_definition ";"
		{
			$$ = $1;
		}
	| statement
		{
			$$ = $1;
		}
	| error
		{
			$$ = new Field( "error", std::unique_ptr<Type>( new Typename( "error" ) ) );
		}
	;

field_definition
	: field_type "identifier"
		{
			// create a new field with the scanned name
			$$ = new Field( *$2, std::unique_ptr<Type>( $1 ) );
		}
	;

array_definition
	: field_type "identifier" "[" expression "]"
		{
			$$ = new Array( *$2, std::unique_ptr<Type>( $1 ), std::unique_ptr<Expression>( $4 ) );
		}
	;

field_type
	: "identifier"
		{
			$$ = new Typename( *$1 );
		}
	| struct_definition
		{
			$$ = $1;
		}
	;

variable_definition
	: "var" "identifier" "=" boolean_expression
		{
			$$ = new Variable( *$2, std::unique_ptr<Expression>( $4 ) );
		}
	| "var" "identifier" "=" expression
		{
			$$ = new Variable( *$2, std::unique_ptr<Expression>( $4 ) );
		}
	;

statement
	: if_statement
		{
			$$ = $1;
		}
	/*fill in other statement types */
	;

if_statement
	: "if" "(" boolean_expression ")"
	"{" struct_members_list "}"
		{
			$$ = new If( std::unique_ptr<BooleanExpression>( $3 ));
			$$->append( *$6 );
		}
	;

expression
	: expression "+" expression
		{
			$$ = new Add( std::unique_ptr<Expression>( $1 ), std::unique_ptr<Expression>( $3 ) );
		}
	| expression "-" expression
		{
			$$ = new Sub( std::unique_ptr<Expression>( $1 ), std::unique_ptr<Expression>( $3 ) );
		}
	| expression "*" expression
		{
			$$ = new Mul( std::unique_ptr<Expression>( $1 ), std::unique_ptr<Expression>( $3 ) );
		}
	| expression "/" expression
		{
			$$ = new Div( std::unique_ptr<Expression>( $1 ), std::unique_ptr<Expression>( $3 ) );
		}
	| expression "%" expression
		{
			$$ = new Mod( std::unique_ptr<Expression>( $1 ), std::unique_ptr<Expression>( $3 ) );
		}
	| "-" expression %prec UNIMUS
		{
			//Don't create a specal case. Just reuse the sub with 0 as the first parameter
			$$ = new Sub( std::unique_ptr<Expression>( new Number( 0 ) ), std::unique_ptr<Expression>( $2 ) );
		}
	| "number"
		{
			$$ = new Number( $1 );
		}
	| "identifier"
		{
			$$ = new Identifier( *$1 );
		}
	| "(" expression ")"
		{
			$$ = $2;
		}
	| error
		{
			$$ = new Identifier( "error" );
		}
	| "(" error ")"
		{
			$$ = new Identifier( "error" );
		}
	;

boolean_expression
	: NOT boolean_expression
		{
			$$ = new Not( std::unique_ptr<BooleanExpression>( $2 ) );
		}
	| boolean_expression "||" boolean_expression
		{
			$$ = new Or( std::unique_ptr<BooleanExpression>( $1 ), std::unique_ptr<BooleanExpression>( $3 ) );
		}
	| boolean_expression "&&" boolean_expression
		{
			$$ = new And( std::unique_ptr<BooleanExpression>( $1 ), std::unique_ptr<BooleanExpression>( $3 ) );
		}
	| boolean_expression "^" boolean_expression
		{
			$$ = new Xor( std::unique_ptr<BooleanExpression>( $1 ), std::unique_ptr<BooleanExpression>( $3 ) );
		}
	| comparison_expression
		{
			$$ = $1;
		}
	| "true"
		{
			$$ = new BooleanValue( true );
		}
	| "false"
		{
			$$ = new BooleanValue( false );
		}
	| "(" boolean_expression ")"
		{
			$$ = $2;
		}
	| error
		{
			$$ = new BooleanValue( false );
		}
	| "(" error ")"
		{
			$$ = new BooleanValue( false );
		}
	;

comparison_expression
	: expression "==" expression
		{
			$$ = new Equal( std::unique_ptr<Expression> $1, std::unique_ptr<Expression> $3 );
		}
	|  boolean_expression "==" boolean_expression
		{
			$$ = new Equal( std::unique_ptr<Expression> $1, std::unique_ptr<Expression> $3 );
		}
	| expression "!=" expression
		{
			// It's the same as ! (expression == expression )
			// != is used as a shortcut
			$$ = new Not(
				std::unique_ptr<BooleanExpression>(
					new Equal(
						std::unique_ptr<Expression> $1,
						std::unique_ptr<Expression> $3
					)
				)
			);
		}
	| boolean_expression "!=" boolean_expression
		{
			// It's the same as ! (expression == expression )
			// != is used as a shortcut
			$$ = new Not(
				std::unique_ptr<BooleanExpression>(
					new Equal(
						std::unique_ptr<Expression> $1,
						std::unique_ptr<Expression> $3
					)
				)
			);
		}
	| expression ">"  expression
		{
			$$ = new Greater( std::unique_ptr<Expression> $1, std::unique_ptr<Expression> $3 );
		}
	| expression "<"  expression
		{
			$$ = new Lesser( std::unique_ptr<Expression> $1, std::unique_ptr<Expression> $3 );
		}
	| expression ">=" expression
		{
			// It's the same as !(expression < expression )
			// >= is used as a shortcut
			$$ = new Not(
				std::unique_ptr<BooleanExpression>(
					new Lesser(
						std::unique_ptr<Expression> $1,
						std::unique_ptr<Expression> $3
					)
				)
			);
		}
	| expression "<=" expression
		{
			// It's the same as !(expression > expression )
			// <= is used as a shortcut
			$$ = new Not(
				std::unique_ptr<BooleanExpression>(
					new Greater(
						std::unique_ptr<Expression> $1,
						std::unique_ptr<Expression> $3
					)
				)
			);
		}
	;

%%

/* Formats the error message and forwards it to the parsing driver for reporting */
void ScriptParser::Parser::error(const ScriptParser::Parser::location_type &loc, const std::string &message)
{
	std::stringstream ss;

	ss << loc << ": " << message << std::endl;
	driver.error( ss.str() );
}
