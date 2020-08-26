#include "Calendar.h"

constexpr COLORREF Calendar::m_gray_color;
Calendar::Calendar() :
	m_x(), m_y(), m_size(200),
	m_year(1990), m_month(1), m_date(1),
	m_first_day(1), m_ldlm(31),
	m_days(),
	m_theme_color(GREEN)
{
	X.Init(m_x);
	Y.Init(m_y);
	Size.Init(m_size, [this](const int& size) {if (size > 0)m_size = size; });
	Year.Init(m_year, [this](const int& year) {if (year >= 1990)m_year = year; });
	Month.Init(m_month, [this](const int& month) {if (month > 0)m_month = month; });
	Date.Init(m_date, [this](const int& date) {if (date > 0)m_date = date; });
	m_bt_left.Init();
	m_bt_right.Init();
	m_bt_left.ch = _T('<');
	m_bt_right.ch = _T('>');
	m_bt_right.x = m_size - 30;
	ThemeColor.Init(m_theme_color);
	TurnToNow();
}

void Calendar::Update()
{
	m_bt_left.Update();
	m_bt_right.Update();
}

void Calendar::Draw(IMAGE* working_image)
{
	static constexpr LPCTSTR m_months[12] =
	{ _T("一"),_T("二"),_T("三") ,_T("四") ,_T("五") ,_T("六") ,
		_T("七") ,_T("八") ,_T("九") ,_T("十") ,_T("十一") ,_T("十二") };

	static constexpr LPCTSTR m_weekdays[7] =
	{ _T("一"),_T("二"),_T("三") ,_T("四") ,_T("五") ,_T("六") ,_T("日") };

	setorigin(m_x, m_y);

	SetWorkingImage(working_image);
	setfillstyle(BS_SOLID);
	setlinestyle(PS_SOLID, 1);
	setlinecolor(m_gray_color);
	setfillcolor(m_theme_color);
	fillrectangle(0, 0, m_size, 30);
	TCHAR* str = new TCHAR[16];


	_stprintf_s(str, 16, _T("%s月 %i"), m_months[m_month - 1], m_year);
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	drawtext(str,
			 new RECT{ 0, 0, m_size, 30 },
			 DT_SINGLELINE | DT_VCENTER | DT_CENTER);


	int width = textwidth(_T("一"));
	int height = textheight(_T("一"));
	double offset = (m_size - width * 7) / 8.0;
	double x = offset;
	int y = 30 + 5;

	rectangle(0, 30, m_size, 30 + height * 7 + 40);
	settextcolor(GREEN);

	for (int i = 0; i < 7; i++) {
		outtextxy(int(x), y, m_weekdays[i]);
		x += offset + width;
	}
	y += height + 5;
	x = offset;
	settextcolor(m_gray_color);
	for (int i = 0; i < m_first_day; i++) {
		ZeroMemory(str, sizeof str);
		_stprintf_s(str, 16, _T("%d"), m_ldlm - m_first_day + i + 1);
		outtextxy(int(x), y, str);
		x += offset + width;
	}
	settextcolor(BLACK);
	int tmp = m_first_day;
	for (int i = 0; i < m_days; i++) {
		if (i + 1 == m_date) {
			setfillcolor(m_theme_color);
			setlinestyle(PS_NULL);
			fillcircle(int(x + width / 2),
					   y + height / 2, width / 2 + 3);
		}
		ZeroMemory(str, sizeof str);
		_stprintf_s(str, 16, _T("%d"), i + 1);
		outtextxy(int(x) + (i < 9 ? textwidth('1') / 2 : 0),
				  y, str);
		x += offset + width;
		if (++tmp % 7 == 0)y += height + 5, x = offset;
	}
	settextcolor(m_gray_color);
	tmp = (m_first_day + m_days) % 7;
	for (int i = 0; i < 7 - (m_first_day + m_days) % 7; i++) {
		ZeroMemory(str, sizeof str);
		_stprintf_s(str, 16, _T("%d"), i + 1);
		outtextxy(int(x) + (i < 9 ? textwidth('1') / 2 : 0),
				  y, str);
		x += offset + width;
	}
	m_bt_left.Draw(working_image);
	m_bt_right.Draw(working_image);
	SetWorkingImage();
}

void Calendar::TurnToNow()
{
	SYSTEMTIME time;
	GetLocalTime(&time);
	m_year = time.wYear;
	m_month = time.wMonth;
	m_date = time.wDay;
	calc();
}

void Calendar::TurnToDate(int year, int month, int date)
{
	Year = year;
	Month = month;
	Date = date;
	calc();
}

void Calendar::ToNextDay()
{
	if (++m_date > m_days) {
		m_date = 1;
		if (++m_month > 12) {
			m_month = 1;
			++m_year;
		}
	}
	TurnToDate(m_year, m_month, m_date);
}

void Calendar::ToNextMonth()
{
	if (++m_month > 12) {
		m_month = 1;
		++m_year;
	}
	calc();
	if (m_date > m_days)m_date = 1;
	TurnToDate(m_year, m_month, m_date);
}

void Calendar::ToNextYear()
{
	++m_year;
	calc();
	if (m_date > m_days)m_date = 1;
	TurnToDate(m_year, m_month, m_date);
}

bool Calendar::is_leap_year(int year)
{
	if (!year)year = m_year;
	if (year < 1990)throw std::runtime_error("年份过早");
	return (year % 100 == 0 ?
			(year % 400 == 0 ? 1 : 0) :
			(year % 4 == 0 ? 1 : 0));
}

void Calendar::calc()
{
	static int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	days[1] = 28;
	int year = 1990, month = 1;
	m_first_day = 0;
	while (!(year == m_year && month == m_month)) {
		m_ldlm = days[month - 1];
		m_first_day = (m_first_day + days[month - 1]) % 7;
		if (++month > 12) {
			month = 1;
			if (is_leap_year(++year))days[1] = 29;
			else days[1] = 28;
		}
	}
	m_days = days[month - 1];
}
