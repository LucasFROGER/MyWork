#ifndef _WINDOWS_WRAPPER_H_
#define _WINDOWS_WRAPPER_H_

#include <vector>

#include "Inputs/Input.h"
#include "Window.h"

#undef CreateWindow

namespace engine
{
	namespace fenestration
	{
		class WindowsWrapper
		{
		public:
			WindowsWrapper(engine::rhi::RHI* rhi);
			~WindowsWrapper();

			void Update();

			Window* CreateWindow(int width, int height, const char* name, bool fullscreen);
			void DeleteWindow(Window* window);

			bool IsKeyDown(input::keys::EKeyCode code);
			bool IsKey(input::keys::EKeyCode code);
			void DisplayCursor(bool display);

			engine::core::maths::Vec2 GetMousePos(Window* window);
			Window* GetActiveWindow();
			void SetMousePos(Window* window, engine::core::maths::Vec2 pos);
		private:
			engine::rhi::RHI* m_rhi;
			input::Input* m_input;
			std::vector<Window*> m_windows;
		};
	}
}

#endif // !_WINDOWS_WRAPPER_H_