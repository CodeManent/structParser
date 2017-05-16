#include "Struct.h"

namespace ScriptParser{
	namespace Symbol{

		Struct::Struct( const DataType &typeInfo)
			: Type( typeInfo )
		{
		}

		Struct::~Struct()
		{
		}

		const DataType& Struct::getTypeInfo() const
		{
			return Type::getTypeInfo();
		}
	}
}
