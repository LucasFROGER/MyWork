#ifndef _SHADER_ENUM_H_
#define _SHADER_ENUM_H_

namespace engine
{
	namespace rhi
	{
		namespace resources
		{
			enum class EShaderEnum : unsigned int
			{
				VERTEX_SHADER = 0,
				PIXEL_SHADER = 1,
				GEOMETRY_SHADER = 2,
				HULL_SHADER = 3,
				DOMAIN_SHADER = 4,

				COUNT = 5
			};
		}
	}
}
#endif