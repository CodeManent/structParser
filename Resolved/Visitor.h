#ifndef Resolved_Visitor_H_
#define Resolved_Visitor_H_
#pragma once

namespace Resolved{

	class Byte;
	class Integer;
	class Struct;
	class Array;

	// The visitor class to implement the visitor pattern on the resolved tree's nodes
	class Visitor
	{
	public:
		Visitor()
		{
		}

		virtual ~Visitor()
		{
		}

		virtual void visit( Byte&	){}
		virtual void visit( Integer&){}
		virtual void visit( Struct&	){}
		virtual void visit( Array&	){}
	};
}

#endif
