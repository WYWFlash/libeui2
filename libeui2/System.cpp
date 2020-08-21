#include "System.h"
namespace EUI2 {
	bool System::m_is_run;
	std::string System::m_title;
	Vector2i System::m_size;
	Property<bool, PropertyMode::Read> System::IsRun;
	Property<std::string, PropertyMode::ReadWrite> System::Title;
	Property<int, PropertyMode::Read> System::ErrCode;
	void System::Init(const Vector2i& size,
					  const std::string& title)
	{
		m_size = size;
		m_title = title;
		m_is_run = false;

		IsRun.Init(m_is_run);
		Title.Init(m_title);
	}
	void System::Run()
	{
		m_is_run = true;
		while (m_is_run) {
			ProcessEvent();
			Update();
			Display();
		}
	}
	void System::Close(int err_code)
	{
		m_is_run = false;
		m_err_code = err_code;
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