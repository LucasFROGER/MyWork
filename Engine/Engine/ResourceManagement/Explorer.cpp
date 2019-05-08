#include "Explorer.h"

#include "../Resource/Folder.h"
#include "../Loader/Extractor.h"

using namespace engine::resource_management;
using namespace engine::resource;
using namespace engine::loader;

#define MAIN_FOLDER_NAME "MainFolder"

Explorer::Explorer(ResourceMgr* resourceMgr) : m_resourceMgr{ resourceMgr }
{
	Folder mainFolder(this, MAIN_FOLDER_NAME);
	m_mainFolder = m_resourceMgr->Add<Folder>(mainFolder);
}

Folder* Explorer::NewFolder(Folder* destination, const std::string& folderName)
{
	if (destination == nullptr)
		return nullptr;

	std::string name;
	Extractor::FindValidFolderName(name, destination, folderName);

	Folder folder(this, name);
	Folder* folderPtr{ m_resourceMgr->Add<Folder>(folder) };
	destination->Add(folderPtr);

	return folderPtr;
}

Folder* Explorer::GetMainFolder() const
{
	return m_mainFolder;
}