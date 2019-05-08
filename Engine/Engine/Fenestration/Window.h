#ifndef _FENESTRATION_WINDOW_H_
#define _FENESTRATION_WINDOW_H_

#include "../RHI/RHI.h"
#include "Viewport.h"
#include "Scissor.h"
#include "../Core/Maths/Vector/Vec4.h"

namespace engine
{
	namespace fenestration
	{
		class WindowsWrapper;

		class Window
		{
		public:
			Window(int id, int width, int height, engine::core::maths::Vec4 clearColor, Viewport viewPort, Scissor Scissor, engine::rhi::RHI* rhi, WindowsWrapper*);
			~Window();
			
			int GetId() const;
			int GetHeight() const;
			int GetWidth() const;
			engine::core::maths::Vec4 GetClearColor() const;
			Scissor GetScissor() const;
			Viewport GetViewport() const;
			HWND GetHWND() const;

			void SetResolution(unsigned int newWidth, unsigned int newHeight);
			void SetClearColor(float r, float g, float b, float a);
			void SetScissorRectangle(Scissor size);
			void SetViewport(Viewport viewport);
		private:
			engine::rhi::RHI* m_rhi;
			WindowsWrapper* m_winWrap;

			HWND m_hwnd;
			int m_id;
			int m_width, m_height;
			engine::core::maths::Vec4 m_clearColor;
			Scissor m_scissor;
			Viewport m_viewport;
		};
	}
}



#endif // !_WINDOW_H_

