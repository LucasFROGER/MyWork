#include "Window.h"

engine::fenestration::Window::Window(int id, int width, int height, engine::core::maths::Vec4 clearColor, Viewport viewport, Scissor scissor, engine::rhi::RHI* rhi, WindowsWrapper* winWrap) :
	m_id{ id },
	m_width{ width },
	m_height{ height },
	m_clearColor{ clearColor },
	m_viewport{ viewport },
	m_scissor{ scissor },
	m_rhi{ rhi },
	m_winWrap{ winWrap }
{
	m_hwnd = m_rhi->GetWindowById(m_id)->GetHWND();
}

engine::fenestration::Window::~Window()
{

}

int engine::fenestration::Window::GetId() const
{
	return m_id;
}

int engine::fenestration::Window::GetHeight() const
{
	return m_height;
}

int engine::fenestration::Window::GetWidth() const
{
	return m_width;
}

engine::core::maths::Vec4 engine::fenestration::Window::GetClearColor() const
{
	return m_clearColor;
}

engine::fenestration::Scissor engine::fenestration::Window::GetScissor() const
{
	return m_scissor;
}

engine::fenestration::Viewport engine::fenestration::Window::GetViewport() const
{
	return m_viewport;
}

HWND engine::fenestration::Window::GetHWND() const
{
	return m_hwnd;
}

void engine::fenestration::Window::SetResolution(unsigned int newWidth, unsigned int newHeight)
{
	m_width = newWidth;
	m_height = newHeight;
	m_rhi->SetResolution(newWidth, newHeight, m_id);
	SetWindowPos(m_hwnd, HWND_TOP, 0, 0, newWidth, newHeight, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
}

void engine::fenestration::Window::SetClearColor(float r, float g, float b, float a)
{
	m_rhi->SetClearColor(r, g, b, a, m_id);
	m_clearColor = { r,g,b,a };
}

void engine::fenestration::Window::SetViewport(Viewport viewport)
{
	m_viewport = viewport;
	m_rhi->SetViewPort(viewport.m_leftCorner.m_x, viewport.m_leftCorner.m_y, viewport.m_height, viewport.m_width, viewport.m_minDepth, viewport.m_maxDepth, m_id);
}

void engine::fenestration::Window::SetScissorRectangle(Scissor scissor)
{
	m_scissor = scissor;
	m_rhi->SetScissorRectangle(scissor.m_leftCorner.m_x, scissor.m_leftCorner.m_y, scissor.m_height, scissor.m_width, m_id);
}
