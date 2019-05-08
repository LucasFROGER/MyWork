#ifndef _DRAWINGTAGS_H_
#define _DRAWINGTAGS_H_

namespace engine
{
	namespace rhi
	{
		enum EDrawingType : unsigned int
		{
			DPOINT = 0,
			DLINE = 1,
			DTRIANGLES = 2,
		};
	}
}
#endif