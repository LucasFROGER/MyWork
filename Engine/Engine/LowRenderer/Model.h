#ifndef _MODEL_H_
#define _MODEL_H_

#include "Vertex.h"
#include <vector>

namespace engine
{
	namespace low_renderer
	{
		class Model
		{
		public:
			Model(const char* path, std::vector<Vertex> vertices, std::vector<int> indices);
			~Model();
			const char* GetPath();
			float* GetVertices();
			int* GetIndices();

			int GetVerticesSize() const;
			int GetIndicesSize() const;

		private:
			const char* m_path;
			float* m_vertexData;
			int* m_indicesData;

			int m_verticesSize;
			int m_indicesSize;

			float* CreateVerticesData(std::vector<Vertex> vertices);
			int* CreateIndicesData(std::vector<int> indices);

		};
	}
}
#endif // !_MODEL_H_

