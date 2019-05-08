#ifndef _MESH_H_
#define _MESH_H_

#include <vector>
#include <string>

#include "Vertex.h"
namespace engine
{
	namespace resource
	{
		class Mesh
		{
		public:
			Mesh(const Mesh& other) = default;
			Mesh(Mesh&& other) = default;
			Mesh(const std::string& name);
			Mesh(const std::string& name, const std::vector<Vertex> vbo, std::vector<int> ibo);
			~Mesh() = default;

			void AddVertex(const Vertex& vertex);
			void AddIndex(int index);

			const std::string& GetName() const;
			const std::vector<Vertex>& GetVBO() const;
			const std::vector<int>& GetIBO() const;
			float* GetVBOAddress();
			int* GetIBOAddress();
			int GetSizeOfVBO() const;
			int GetSizeOfIBO() const;

			void SetVBO(const std::vector<Vertex>& vbo);
			void SetIBO(const std::vector<int>& ibo);

			void SetVBOCapacity(size_t capacity);
			void SetIBOCapacity(size_t capacity);

			Mesh& operator=(const Mesh& other) = default;
			Mesh& operator=(Mesh&& other) = default;

		private:
			std::string m_name;

			std::vector<Vertex> m_vbo;
			std::vector<int> m_ibo;
		};
	}
}
#endif