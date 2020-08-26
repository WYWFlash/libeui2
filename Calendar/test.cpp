#include<easyx.h>
#include"Calendar.h"
int main() {
	initgraph(640, 480);
	Calendar c;
	c.X = 10;
	c.Y = 10;
	c.Size = 200;
	BeginBatchDraw();
	auto start = clock();
	while (1) {
		graphdefaults();
		setbkcolor(WHITE);
		c.Update();
		cleardevice();
		c.Draw();
		FlushBatchDraw();
		if (clock() - start > 100) {
			c.ToNextDay();
			start = clock();
		}
		Sleep(5);
	}
	EndBatchDraw();
	closegraph();
	return 0;
}