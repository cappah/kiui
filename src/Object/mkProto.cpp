//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Object/mkObjectConfig.h>
#include <Object/mkProto.h>

#define MAX_TYPES 1000

namespace mk
{
	Proto::Proto(Type& type)
		: IdObject(cls())
		, m_type(type)
		, m_numParts(0)
		, m_hashParts(MAX_TYPES) // Type::maxId() doesn't work because at the time Proto is instantiated not all types have been loaded
	{}

	ProtoType::ProtoType()
		: Type(PROTOTYPE)
		, m_proto(*this)
	{}
}
