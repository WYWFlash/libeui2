#pragma once
#include"Vector2.h"
#include"Mouse.h"
#include"Keyboard.h"
namespace EUI2 {
	class Event {
	public:
		enum {
			Close,
			MouseButton,
			MouseMoved,
			MouseWheel,
			KeyboardButton
		}Type;

	public:
		union {
			struct {
				int close_code;
			}CloseEvent;
			struct {
				Mouse::Button Button;
				bool Pressed;
				Vector2i Position;
			} MouseButtonEvent;

			struct {
				Vector2i Position;
			} MouseMovedEvent;

			struct {
				int Offset;
				Vector2i Position;
			} MouseWheelEvent;

			struct {
				Keyboard::Key Key;
				bool Pressed;
			}KeyboardButtonEvent;
		};
	};
}