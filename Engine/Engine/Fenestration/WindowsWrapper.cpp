#include "../../stdafx.h"

#include "WindowsWrapper.h"

engine::fenestration::WindowsWrapper::WindowsWrapper(engine::rhi::RHI* rhi) :
	m_input{ new input::Input() },
	m_rhi{ rhi }
{

}

engine::fenestration::WindowsWrapper::~WindowsWrapper()
{
	delete m_input;
	SAFE_DELETE_VECTOR(m_windows);
}

engine::fenestration::Window* engine::fenestration::WindowsWrapper::CreateWindow(int width, int height, const char* name, bool fullscreen)
{
	if (name)
	{
		Viewport view{ {0.f,0.f},height, width, 0.0f, 1.0f };
		Scissor scissor{ { 0.f,0.f },height, width };

		int id = m_rhi->GenWindow(width, height, name, name, fullscreen);
		engine::fenestration::Window* win = new Window(id, width, height, { 0.5f, 0.5f, 0.5f, 1.0f }, view, scissor, m_rhi, this);
		m_windows.push_back(win);
		return win;
	}
	return nullptr;
}

void engine::fenestration::WindowsWrapper::DeleteWindow(Window* window)
{
	m_rhi->DeleteWindow(window->GetId());
	for (size_t i = 0; i < m_windows.size(); i++)
	{
		if (m_windows[i]->GetId() == window->GetId())
		{
			delete m_windows[i];
			m_windows[i] = nullptr;
			m_windows.erase(m_windows.begin() + i);
		}
	}
}

void engine::fenestration::WindowsWrapper::Update()
{
	m_input->Update();

	for (int i{ 0 }; i < m_windows.size(); ++i)
	{
		if (m_windows[i])
		{
			engine::rhi::Window* rhiWin = m_rhi->GetWindowById(m_windows[i]->GetId());
			if (rhiWin)
			{
				RECT rect;
				if (GetWindowRect(rhiWin->GetHWND(), &rect))
				{
					if (rect.right - rect.left != m_windows[i]->GetWidth() || rect.bottom - rect.top != m_windows[i]->GetHeight())
					{
						m_windows[i]->SetResolution(rect.right - rect.left, rect.bottom - rect.top);

						Viewport newViewport{ m_windows[i]->GetViewport().m_leftCorner, rhiWin->GetWidth(), rhiWin->GetHeight(),
							m_windows[i]->GetViewport().m_minDepth, m_windows[i]->GetViewport().m_maxDepth };

						Scissor newScissor{ m_windows[i]->GetScissor().m_leftCorner, rhiWin->GetWidth(), rhiWin->GetHeight() };

						m_windows[i]->SetViewport(newViewport);
						m_windows[i]->SetScissorRectangle(newScissor);
					}
				}


			}
		}
	}
}

bool engine::fenestration::WindowsWrapper::IsKeyDown(input::keys::EKeyCode code)
{
	return m_input->IsKeyDown(code);
}

bool engine::fenestration::WindowsWrapper::IsKey(input::keys::EKeyCode code)
{
	return m_input->IsKey(code);
}

void engine::fenestration::WindowsWrapper::DisplayCursor(bool display)
{
	m_input->DisplayCursor(display);
}

engine::core::maths::Vec2 engine::fenestration::WindowsWrapper::GetMousePos(Window* window)
{
	return m_input->GetMousePos(window->GetHWND());
}

engine::fenestration::Window* engine::fenestration::WindowsWrapper::GetActiveWindow()
{
	if (m_rhi->GetCurrentWindow())
	{
		for (int i{ 0 }; i < m_windows.size(); ++i)
			if(m_windows[i])
				if (m_windows[i]->GetHWND() == m_rhi->GetCurrentWindow()->GetHWND())
					return m_windows[i];
	}
	return nullptr;
}


void engine::fenestration::WindowsWrapper::SetMousePos(Window* window, engine::core::maths::Vec2 pos)
{
	m_input->SetMousePos(window->GetHWND(), pos);
}