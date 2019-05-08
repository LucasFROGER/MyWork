#ifndef _FBX_LOADER_H_
#define _FBX_LOADER_H_

#include "Model.h"
//si vous souhaiter inclure dynamiquement mettre ca avant
#define FBXSDK_SHARED
//#include "fbxsdk.h"

/*
#ifdef FBXSDK_SHARED
//attention : seulement avec la dll sinon : libfbxsdk-md.lib

#pragma comment(lib, "libfbxsdk.lib")
#else
#pragma comment(lib, "libfbxsdk-md.lib")
#endif
*/

namespace engine
{
	namespace low_renderer
	{
		class ModelLoader
		{
		public:
			ModelLoader();
			~ModelLoader();

			Model* GetCube();
			Model* GetPyramid();

		private:
			std::vector<Model* > m_models;
			Model* GetModel(const char* path);

			void CreateCube();
			void CreatePyramid();
		};
	}
}

#endif
