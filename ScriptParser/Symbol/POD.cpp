#include "POD.h"

namespace ScriptParser{
	namespace Symbol{
		POD::POD( const DataType &typeInfo )
			: Type( typeInfo )
		{
		}

		POD::~POD()
		{
		}

		const DataType& POD::getTypeInfo() const
		{
			return Type::getTypeInfo();
		}
	}
}