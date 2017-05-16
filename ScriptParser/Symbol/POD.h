#ifndef ScriptParser_Symbol_POD_H_
#define ScriptParser_Symbol_POD_H_
#pragma once

#include "Type.h"

namespace ScriptParser{
	namespace Symbol{

		/*
		 * A class thar represents POD (plain old data) in the script.
		 * A data type is associated tith the data.
		 */
		class POD :public Type{
		public:
			POD( const DataType &typeinfo);
			virtual ~POD();
			virtual const DataType& getTypeInfo() const;
		};
	}
}

#endif
