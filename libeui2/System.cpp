#include "System.h"
namespace EUI2 {
	bool System::m_is_run;
	std::string System::m_title;
	Vector2i System::m_size;
	int System::m_close_code;
	std::queue<Event> System::m_events;
	Property<bool, PropertyMode::Read> System::IsRun;
	Property<std::string, PropertyMode::ReadWrite> System::Title;
	Property<int, PropertyMode::Read> System::ErrCode;
	void System::Init(const Vector2i& size,
					  const std::string& title)
	{
		m_size = size;
		m_title = title;
		m_is_run = false;
		m_close_code = 0;

		IsRun.Init(m_is_run);
		Title.Init(m_title);
	}
	void System::Run()
	{
		initgraph(m_size.x, m_size.y);
		m_is_run = true;
		while (m_is_run) {
			ProcessEvent();
			Update();
			Display();
		}
	}
	void System::Close(int close_code)
	{
		m_is_run = false;
		m_close_code = close_code;
	}
	void System::ProcessEvent()
	{
	}
	void System::Update()
	{
	}
	void System::Display()
	{
	}
}