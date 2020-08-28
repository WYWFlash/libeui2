#pragma once
#include<easyx.h>
#include<functional>
#include<string>
#include<windows.h>
#include"Property.h"
class Button
{
public:
	Button();
	virtual void Draw(IMAGE* working_image=0);
	virtual void Update(){}
	virtual void MousePressedEvent();
	virtual void MouseReleasedEvent();
	virtual void MouseOnEvent();
	virtual void MouseLeaveEvent();
	bool PtInThis(int x, int y);
	Property<int, PropertyMode::ReadWrite>X, Y, Width, Height;
	Property<COLORREF, PropertyMode::ReadWrite>
		LineColor, FillColor, TextColor, MouseOnColor, MousePressedColor;
	Property<bool, PropertyMode::Read>MouseOn, MousePressed;
	Property<std::wstring, PropertyMode::ReadWrite>
		Text,FontName;
	Property<int, PropertyMode::ReadWrite>FontHeight;
	std::function<void()> Clicked;
	bool m_mouse_on, m_mouse_pressed;
protected:
	int m_x, m_y, m_width, m_height;
	COLORREF m_linecolor, m_fillcolor, m_textcolor;
	COLORREF m_mouse_on_color, m_mouse_pressed_color;
	//bool m_mouse_on, m_mouse_pressed;
	std::wstring m_text,m_font_name;
	int m_font_height;
};

