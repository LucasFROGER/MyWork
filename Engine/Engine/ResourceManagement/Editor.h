#ifndef _EDITOR_H_
#define _EDITOR_H_

#include "../Resource/ResourceMgr.h"
#include "../Loader/Importer.h"
#include "Explorer.h"
#include "..\SceneGraph\Scene.h"

namespace engine
{
	namespace resource_management
	{
		class Editor
		{
		public:
			Editor(resource::ResourceMgr* resourceMgr, Explorer* explorer, engine::rhi::RHI* rhi, engine::physic::PhysicMgr* physMgr);

			bool Run();

		private:
			resource::ResourceMgr* m_resourceMgr;
			Explorer* m_explorer;
			engine::rhi::RHI* m_rhi;
			engine::physic::PhysicMgr* m_physMgr;

			///////////
			// proto //
			engine::scene_graph::Scene m_mainScene;
			///////////

			bool Play();
			void Stop();
		};
	}
}
#endif