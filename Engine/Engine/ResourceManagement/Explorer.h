#ifndef _EXPLORER_H_
#define _EXPLORER_H_

#include "../Resource/ResourceMgr.h"

namespace engine
{
	namespace resource { class Folder; }

	namespace resource_management
	{
		class Explorer
		{
		public:
			Explorer(resource::ResourceMgr* resourceMgr);

			resource::Folder* NewFolder(resource::Folder* destination, const std::string& folderName);

			resource::Folder* GetMainFolder() const;

		private:
			resource::ResourceMgr* m_resourceMgr;
			resource::Folder* m_mainFolder;
		};
	}
}
#endif