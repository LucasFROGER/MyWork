#ifndef _RESOURCE__VERTEX_H_
#define _RESOURCE__VERTEX_H_

#include "../Core/Maths/Vector/Vec2.h"
#include "../Core/Maths/Vector/Vec3.h"
#include "../Core/Maths/Vector/Vec4.h"

namespace engine
{
	namespace resource
	{
		struct Vertex
		{
			engine::core::maths::Vec3 m_position;
			engine::core::maths::Vec3 m_normal;
			engine::core::maths::Vec2 m_uv;
			engine::core::maths::Vec3 m_tangent;

			Vertex() = default;
			Vertex(const Vertex& other) = default;
			Vertex(Vertex&& other) = default;
			Vertex(engine::core::maths::Vec3 position, engine::core::maths::Vec3 normal, engine::core::maths::Vec2 uv);
			~Vertex() = default;

			float* GetAddress();

			Vertex&	operator=(const Vertex& other) = default;
			Vertex&	operator=(Vertex&& other) = default;
			bool	operator==(const Vertex& other);
			bool	operator!=(const Vertex& other);
		};

		struct TextVertex
		{
			TextVertex(float r, float g, float b, float a, float u, float v, float tw, float th, float x, float y, float w, float h) : color(r, g, b, a), texCoord(u, v, tw, th), pos(x, y, w, h) {}
			engine::core::maths::Vec4 pos;
			engine::core::maths::Vec4 texCoord;
			engine::core::maths::Vec4 color;
		};
	}
}
#endif