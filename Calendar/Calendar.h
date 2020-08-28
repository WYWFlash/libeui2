#pragma once
#include<stdexcept>
#include<functional>
#include<easyx.h>
#include<windows.h>
#include<time.h>
#include<stdio.h>
#include"Property.h"
class Calendar {
public:
	Calendar();
	void Update();
	void Draw(IMAGE* working_image = nullptr);
	void TurnToNow();
	void TurnToDate(int year, int month, int date);
	void ToNextDay();
	void ToLastMonth();
	void ToNextMonth();
	void ToNextYear();
	bool PtInThis(int x, int y);
	void MousePress(int x,int y,bool* handled);
	void MouseRelease(int x,int y,bool* handled);
	Property<int, PropertyMode::ReadWrite>X, Y;
	Property<int, PropertyMode::ReadWrite>Size;
	Property<int, PropertyMode::ReadWrite>Year, Month, Date;
	Property<COLORREF, PropertyMode::ReadWrite>ThemeColor;
private:
	//判断某一年是否是闰年，如果year为0（不填），则默认为日历中显示的年份
	bool is_leap_year(int year = 0);

	//计算日期
	void calc();

	void pt_in_date(int x, int y, bool* handled);
private:
	int m_x, m_y;
	int m_size;
	int m_year, m_month, m_date;
	int m_syear, m_smonth, m_sdate;
	int m_tyear, m_tmonth, m_tdate;
	int m_first_day;			//这个月的第一天是星期几
	int m_ldlm;					//last day of last month
	int m_days;					//当月的天数
	COLORREF m_theme_color;
	LOGFONT m_font;
	static constexpr COLORREF m_gray_color = RGB(200, 200, 200);
public:
	class {
	public:
		int x, y, size;
		TCHAR ch;
		COLORREF theme_color;
		COLORREF final_color;
		std::function<void()>clicked;
		int font_height;
		void Init() {
			x = 1;
			y = 1;
			size = 29;
			ch = 0;
			theme_color = GREEN;
			final_color = RGB(133, 191, 79);
			m_current_color = theme_color;
			m_mouse_on = false;
			m_start = 0;
		}
		void Draw(IMAGE* working_image) {
			SetWorkingImage(working_image);
			setlinestyle(PS_NULL);
			setfillstyle(BS_SOLID);
			setfillcolor(m_current_color);
			fillrectangle(x, y, x + size, y + size);
			settextcolor(WHITE);
			drawtext(ch, new RECT{ x,y,x + size,y + size },
					 DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			SetWorkingImage();
		}
		void Update() {
			if (m_mouse_on) {
				int r = GetRValue(theme_color);
				int g = GetGValue(theme_color);
				int b = GetBValue(theme_color);
				int r1 = GetRValue(final_color);
				int g1 = GetGValue(final_color);
				int b1 = GetBValue(final_color);
				double t =
					double(clock() - m_start) * 4 / CLOCKS_PER_SEC;
				if (t > 1)t = 1;
				int r2 = r + int((r1 - r) * t);
				int g2 = g + int((g1 - g) * t);
				int b2 = b + int((b1 - b) * t);
				m_current_color = RGB(r2, g2, b2);
			}
			else if (m_current_color != theme_color) {
				int r = GetRValue(theme_color);
				int g = GetGValue(theme_color);
				int b = GetBValue(theme_color);
				int r1 = GetRValue(final_color);
				int g1 = GetGValue(final_color);
				int b1 = GetBValue(final_color);
				double t =
					double(clock() - m_start) * 4 / CLOCKS_PER_SEC;
				if (t > 1)t = 1;
				int r2 = r1 - int((r1 - r) * t);
				int g2 = g1 - int((g1 - g) * t);
				int b2 = b1 - int((b1 - b) * t);
				m_current_color = RGB(r2, g2, b2);
			}
		}
		bool PtInThis(int x, int y) {
			return x >= this->x && y >= this->y &&
				x <= this->x + this->size &&
				y <= this->y + this->size;
		}
		void MousePress() {
			m_mouse_on = true;
			m_start = clock();
		}
		void MouseRelease() {
			m_mouse_on = false;
			if ((clock() - m_start) * 4 >= CLOCKS_PER_SEC)m_start = clock();
			else m_start = clock() - (CLOCKS_PER_SEC - clock() + m_start);
			clicked();
		}
		bool MouseDown() {
			return m_mouse_on;
		}
	private:
		COLORREF m_current_color;//当前渐变色
		bool m_mouse_on;//鼠标是否按下按钮
		clock_t m_start;//鼠标按下按钮的时间
	}m_bt_left, m_bt_right;
};