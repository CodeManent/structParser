#ifndef ScriptParser_APT_Statement_H_
#define ScriptParser_APT_Statement_H_
#pragma once

#include "StructMember.h"

#include <memory>

namespace ScriptParser{
	namespace APT{
		class Statement: public StructMember
		{
		public:
			Statement()
				: StructMember()

			{
			}

			virtual ~Statement()
			{
			}
		};
	}
}


#endif
