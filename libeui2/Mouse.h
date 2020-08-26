#pragma once
namespace EUI2 {
	class Mouse {
	public:
		enum Button {
			Left,Right,Middle
		};
		int x, y;
		Mouse():x(0),y(0){}
		~Mouse(){}
	};
}