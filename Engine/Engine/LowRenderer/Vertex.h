#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "../Core/Maths/Matrix/Mat4.h"
#include "../Core/Maths/Vector/Vec4.h"
#include "../Core/Maths/Vector/Vec3.h"
#include "../Core/Maths/Vector/Vec2.h"
namespace engine
{
	namespace low_renderer
	{
		struct Vertex
		{
			Vertex(float x, float y, float z, float nx, float ny, float nz, float u, float v, float tx, float ty, float tz) : m_position{ x, y, z }, m_normal{ nx, ny, nz }, m_texCoord{ u, v }, m_tangent{ tx, ty, tz } {}
			Vertex(engine::core::maths::Vec3 pos, engine::core::maths::Vec3 normal, engine::core::maths::Vec2 texCoord, engine::core::maths::Vec3 tangent) : m_position{ pos }, m_normal{ normal }, m_texCoord{ texCoord }, m_tangent{ tangent } {}
			engine::core::maths::Vec3 m_position;
			engine::core::maths::Vec3 m_normal;
			engine::core::maths::Vec2 m_texCoord;
			engine::core::maths::Vec3 m_tangent;
		};

		struct TextVertex
		{
			TextVertex(float r, float g, float b, float a, float u, float v, float tw, float th, float x, float y, float w, float h) : color(r, g, b, a), texCoord(u, v, tw, th), pos(x, y, w, h) {}
			engine::core::maths::Vec4 pos;
			engine::core::maths::Vec4 texCoord;
			engine::core::maths::Vec4 color;
		};

		struct ConstBoeuf
		{
			engine::core::maths::Vec4 colorMultiplier;
		};

		struct ConstantBufferPerObject
		{
			engine::core::maths::Mat4 wMat;
			engine::core::maths::Mat4 vpMat;
		};

		struct BufferPerText
		{
			engine::core::maths::Vec2 pos = engine::core::maths::Vec2(0.1f, 0.1f);
			engine::core::maths::Vec2 scale;
			engine::core::maths::Vec2 padding;
			engine::core::maths::Vec4 color;
		};
	}
}
#endif
