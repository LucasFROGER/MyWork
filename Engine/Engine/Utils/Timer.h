#ifndef _TIMER_H_
#define _TIMER_H_

namespace engine
{
	namespace utils
	{
		struct Timer
		{
			double timerFrequency = 0.0;
			long long lastFrameTime = 0;
			long long lastSecond = 0;
			double frameDelta = 0;
			int fps = 0;

			Timer()
			{
				LARGE_INTEGER li;
				QueryPerformanceFrequency(&li);

				// seconds
				timerFrequency = double(li.QuadPart);

				// milliseconds
				//timerFrequency = double(li.QuadPart) / 1000.0;

				// microseconds
				//timerFrequency = double(li.QuadPart) / 1000000.0;

				QueryPerformanceCounter(&li);
				lastFrameTime = li.QuadPart;
			}

			// Call this once per frame
			double GetFrameDelta()
			{
				LARGE_INTEGER li;
				QueryPerformanceCounter(&li);
				frameDelta = double(li.QuadPart - lastFrameTime) / timerFrequency;
				if (frameDelta > 0)
					fps = 1000 / frameDelta;
				lastFrameTime = li.QuadPart;
				return frameDelta;
			}
		};
	}
}

#endif // !_TIMER_H_

