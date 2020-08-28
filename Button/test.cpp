#include"Button.h"
#include<time.h>
int WINAPI _tWinMain(HINSTANCE,HINSTANCE,LPTSTR,int) {
	initgraph(640, 480);
	BeginBatchDraw();

	Button bt;
	bt.X = 100;
	bt.Y = 20;
	bt.LineColor = RGB(92, 170, 21);
	bt.FillColor = WHITE;
	bt.MouseOnColor = RGB(125, 187, 68);
	bt.MousePressedColor = RGB(83, 153, 19);
	bt.Clicked = [&bt]() {
		bt.Text = _T("QWQ");
	};
	bool mouse_pressed=0;
	while (1) {
		if (MouseHit()) {
			MOUSEMSG msg = GetMouseMsg();
			if (msg.mkLButton ^ mouse_pressed) {
				if (msg.mkLButton) {
					mouse_pressed = 1;
					if (bt.PtInThis(msg.x, msg.y))
						bt.MousePressedEvent();
				}
				else {
					mouse_pressed = 0;
					if (bt.PtInThis(msg.x, msg.y))
						bt.MouseReleasedEvent();
				}
			}
			if (msg.uMsg == WM_MOUSEMOVE) {
				if (bt.PtInThis(msg.x, msg.y))
					bt.MouseOnEvent();
				else if (bt.MouseOn)
					bt.MouseLeaveEvent();
			}
		}
		graphdefaults();
		setbkcolor(WHITE);
		cleardevice();
		bt.Draw();
		FlushBatchDraw();
		Sleep(5);
	}
	EndBatchDraw();
	closegraph();
}