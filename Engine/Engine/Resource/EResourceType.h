#ifndef _E_RESOURCE_TYPE_H_
#define _E_RESOURCE_TYPE_H_

namespace resource
{
	enum class EResourceType
	{
		UNKNOWN = -1,
		VERTEX,
		MESH,
		TEXTURE,
		MATERIAL,
		SHADER,
		SHADER_PROGRAM,
		COUNT
	};
}

#endif