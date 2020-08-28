#include<easyx.h>
#include"Calendar.h"
int WINAPI _tWinMain(HINSTANCE,HINSTANCE,LPTSTR,int) {
	initgraph(320,215);
	Calendar c;
	c.ThemeColor = RGB(90, 170, 20);
	c.X = 10;
	c.Y = 10;
	c.Size = 300;
	BeginBatchDraw();
	auto start = clock();
	bool mouse_down = false;
	while (1) {
		graphdefaults();
		if (MouseHit()) {
			auto msg = GetMouseMsg();
			if (msg.mkLButton ^ mouse_down) {
				bool handled = false;
				if (msg.mkLButton) {
					mouse_down = true;
					c.MousePress(msg.x, msg.y, &handled);
				}
				else {
					mouse_down = false;
					c.MouseRelease(msg.x, msg.y, &handled);
				}
			}
		}
		c.Update();
		setbkcolor(WHITE);
		cleardevice();
		c.Draw();
		FlushBatchDraw();
		Sleep(5);
	}
	EndBatchDraw();
	closegraph();
	return 0;
}