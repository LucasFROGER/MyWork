#ifndef _ID_ALLOCATOR_H_
#define _ID_ALLOCATOR_H_

#include <vector>

namespace engine
{
	namespace utils
	{
		class IdAllocator
		{
		public:	
			IdAllocator();
			~IdAllocator();
		
			int GetNewId();
			bool CheckExistingId(int id);
			bool CheckFreeId(int id);
			bool ReleaseId(int id);

		private:
			std::vector<int> m_freeId;
			int m_currentId;

		};
	}
}


#endif // !_ID_ALLOCATOR_H_
