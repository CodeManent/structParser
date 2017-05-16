/* Flex source file that generates the scanner to use in C++ */
/*TODO: make the generated scanner reentrand/pure and redefine YYINPUT */

/* The scanner will be used with a parser generated from bison */
%option bison-bridge
/* Cooporation with bison's location tracking mechanism */
%option bison-locations
/* It's not an interactive scanner ( removes the reference to isatty() ) */
%option never-interactive
/* Don't need it because we don't use include files */
/* %option noyywrap ***** replaced by function in the end */
%option nounput
/* batch processing, manual says it's faster */
%option batch
/* ommit default scannin rules */
%option nodefault
/* TODO: remove for release version
%option debug
*/

%{

//fix compilation warnings
//remove definitions of INT*_MIN/MAX. They will be properly defined from the inclusion of the stdint.h
#undef INT8_MIN
#undef INT8_MAX
#undef UINT8_MIN
#undef UINT8_MAX
#undef INT16_MIN
#undef INT16_MAX
#undef UINT16_MIN
#undef UINT16_MAX
#undef INT32_MIN
#undef INT32_MAX
#undef UINT32_MAX
#undef UINT32_MAX

#include <stdint.h>

// declaration of the yywrap function to supress warning message generated when using option noyywrap
extern "C" int yywrap (void )
{
	return 1;
}


// include the parser header so the tokens to return are defined
#include "Parser.tab.hh"

// Import the parser's token type into a typedef to make them available on global scope
typedef ScriptParser::Parser::token token;
typedef ScriptParser::Parser::token_type token_type;


// omit the inclusion of the uinstd.h
#define YY_NO_UNISTD_H


// Semantic type definition (if not defined by default)
#ifndef YYSTYPE
	typedef ScriptParser::Parser::semantic_type YYSTYPE;
#endif

// Location type definition ( if not defined by default)
#ifndef YYLTYPE
	typedef ScriptParser::Parser::location_type YYLTYPE;
#endif


// By default yylex returns 0 (of type int) whitch is not of token_type
#define yyterminate() return token::END


#include <sstream>
#include <stdio.h>
#include <stdexcept>
#include "Driver.h"

%}


/*character followed by character letter or underscore */
id	[a-zA-Z][a-zA-Z0-9_]*

/* Number */
int	[0-9]

/* White space */
ws	[ \t\r]

/* Excluseive state: Comment */
%x COMMENT


%%

%{
	// Code to place at the beginning of yylex()
	// we use yyloc_param instead of yyloc because the initialization of
	// yylloc happens after this portion of code

	if( yytext != NULL )
	{
		yylloc_param->columns( strlen( yytext ) );
		yylloc_param->step();
	}
%}

[\n]+	{ yylloc->lines( yyleng );	}
{ws}+	{ yylloc->columns( strlen( yytext ) ); }

"+"		{ return token::ADD;		}
"-"		{ return token::SUB;		}
"*"		{ return token::MUL;		}
"/"		{ return token::DIV;		}
"%"		{ return token::MOD;		}
"="		{ return token::ASSIGN;		}

"&&"	{ return token::AND;		}
"||"	{ return token::OR;			}
"!"		{ return token::NOT;		}
"^"		{return token::XOR;			}

"=="	{ return token::EQ;			}
"!="	{ return token::NOTEQ;		}

">"		{ return token::GREATER;	}
"<"		{ return token::LESSER;		}
">="	{ return token::GREATEREQ;	}
"<="	{ return token::LESSEREQ;	}


"("		{ return token::LPAR;		}
")"		{ return token::RPAR;		}
"{"		{ return token::LBR;		}
"}"		{ return token::RBR;		}
"["		{ return token::LSBR;		}
"]"		{ return token::RSBR;		}
";"		{ return token::SEMICOLON;	}
"."		{ return token::DOT;		}
"@"		{ return token::AT;			}

"if"	{ return token::IF;			}
"else"	{ return token::ELSE;		}
"struct"	{ return token::STRUCT;	}
"var"	{ return token::VAR;		}

"true"	{ return token::TRUE;		}
"false"	{ return token::FALSE;		}


{int}+	{
			std::istringstream iss( yytext );
			long n;
			iss >> n;
			if( !iss )
				throw std::runtime_error("ScriptParser: Lexer: Error converting string to long" );

			yylval->ival = n;
			return token::NUMBER;
		}

{id}	{
			yylval->sval = new std::string( yytext );
			return token::IDENTIFIER;
		}

"//".*	{ /* comment until the end of the ine */ }


"/*"			{ BEGIN(COMMENT);					}
<COMMENT>"*/"	{ BEGIN(INITIAL);					}
<COMMENT>\n		{ yylloc->lines( yyleng );				}
<COMMENT>[^\n*]*	{ yylloc->columns( strlen( yytext ) );	}
<COMMENT>"*"	{ yylloc->columns( strlen( yytext ) );	}

.		{
			yylval->sval = new std::string( yytext );

			//put the offending character int the ival and return a BAD_CHAR token
			//yylval->ival = yytext[0];
			return token::BAD_CHAR;
		}

%%

/* Sets the input on the flex scanner to the opened file by the driver. TODO: must refactor scanner input */
void ScriptParser::Driver::setScannerInput(FILE* f)
{
	yyin = f;
}
