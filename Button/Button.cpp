#include "Button.h"

Button::Button() :
	m_x(), m_y(), m_width(100), m_height(25),
	m_linecolor(RGB(204, 204, 204)),
	m_fillcolor(RGB(225, 225, 225)),
	m_textcolor(BLACK),
	m_mouse_on_color(RGB(229, 241, 251)),
	m_mouse_pressed_color(RGB(204, 228, 247)),
	m_mouse_on(), m_mouse_pressed(),
	m_text(_T("button")),
	m_font_name(_T("Î¢ÈíÑÅºÚ")),
	m_font_height(20),
	Clicked()
{
	X.Init(m_x);
	Y.Init(m_y);
	Width.Init(m_width);
	Height.Init(m_height);
	LineColor.Init(m_linecolor);
	FillColor.Init(m_fillcolor);
	TextColor.Init(m_textcolor);
	MouseOnColor.Init(m_mouse_on_color);
	MousePressedColor.Init(m_mouse_pressed_color);
	MouseOn.Init(m_mouse_on);
	MousePressed.Init(m_mouse_pressed);
	Text.Init(m_text);
	FontName.Init(m_font_name);
	FontHeight.Init(m_font_height);
}

void Button::Draw(IMAGE* working_image)
{
	SetWorkingImage(working_image);
	setlinecolor(m_linecolor);
	if (m_mouse_pressed)
		setfillcolor(m_mouse_pressed_color);
	else if (m_mouse_on)
		setfillcolor(m_mouse_on_color);
	else
		setfillcolor(m_fillcolor);
	setlinestyle(PS_SOLID,1);
	setfillstyle(BS_SOLID);
	settextstyle(m_font_height, 0, m_font_name.c_str(),0,0,0,0,0,0,0,0,0, PROOF_QUALITY,0);
	if (m_mouse_on)
		settextcolor(WHITE);
	else
		settextcolor(m_textcolor);
	setbkmode(TRANSPARENT);
	fillroundrect(m_x, m_y, m_x + m_width, m_y + m_height,5,5);
	drawtext(m_text.c_str(),
			 new RECT{ m_x,m_y,m_x + m_width,m_y + m_height },
			 DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void Button::MousePressedEvent()
{
	m_mouse_on = m_mouse_pressed = 1;
}

void Button::MouseReleasedEvent()
{
	if (m_mouse_pressed) {
		m_mouse_pressed = 0;
		if(Clicked)Clicked();
	}
}

void Button::MouseOnEvent()
{
	m_mouse_on = true;
}

void Button::MouseLeaveEvent()
{
	m_mouse_on = m_mouse_pressed = 0;
}

bool Button::PtInThis(int x, int y)
{
	return (x >= m_x && y >= m_y &&
			x <= m_x + m_width &&
			y <= m_y + m_height);
}
