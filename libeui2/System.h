#pragma once
#include"Vector2.h"
#include"Property.h"
#include<string>
namespace EUI2 {
	//EUI2µÄµ×²ã¿ØÖÆÆ÷
	class System
	{
	public:
		System() = delete;
		static void Init(const Vector2i& size,
						 const std::string& title);
		static void Run();
		static void Close(int err_code = 0);

		static Property<bool,PropertyMode::Read>IsRun;
		static Property<std::string, PropertyMode::ReadWrite>Title;
		static Property<int, PropertyMode::Read>ErrCode;
	private:
		static void ProcessEvent();
		static void Update();
		static void Display();
	private:
		static bool m_is_run;
		static std::string m_title;
		static Vector2i m_size;
		static int m_err_code;
	};
}

