#include "SfmlHelpers.h"

namespace sf
{
	dragon::Key ConvertKey(Keyboard::Key key)
	{
		switch (key)
		{
		case Keyboard::Key::Unknown: return dragon::Key::Unknown; ///< Unhandled key
		case Keyboard::Key::A: return dragon::Key::A;        ///< The A key
		case Keyboard::Key::B: return dragon::Key::B;            ///< The B key
		case Keyboard::Key::C: return dragon::Key::C;            ///< The C key
		case Keyboard::Key::D: return dragon::Key::D;            ///< The D key
		case Keyboard::Key::E: return dragon::Key::E;            ///< The E key
		case Keyboard::Key::F: return dragon::Key::F;            ///< The F key
		case Keyboard::Key::G: return dragon::Key::G;            ///< The G key
		case Keyboard::Key::H: return dragon::Key::H;            ///< The H key
		case Keyboard::Key::I: return dragon::Key::I;            ///< The I key
		case Keyboard::Key::J: return dragon::Key::J;            ///< The J key
		case Keyboard::Key::K: return dragon::Key::K;            ///< The K key
		case Keyboard::Key::L: return dragon::Key::L;            ///< The L key
		case Keyboard::Key::M: return dragon::Key::M;            ///< The M key
		case Keyboard::Key::N: return dragon::Key::N;            ///< The N key
		case Keyboard::Key::O: return dragon::Key::O;            ///< The O key
		case Keyboard::Key::P: return dragon::Key::P;            ///< The P key
		case Keyboard::Key::Q: return dragon::Key::Q;            ///< The Q key
		case Keyboard::Key::R: return dragon::Key::R;            ///< The R key
		case Keyboard::Key::S: return dragon::Key::S;            ///< The S key
		case Keyboard::Key::T: return dragon::Key::T;            ///< The T key
		case Keyboard::Key::U: return dragon::Key::U;            ///< The U key
		case Keyboard::Key::V: return dragon::Key::V;            ///< The V key
		case Keyboard::Key::W: return dragon::Key::W;            ///< The W key
		case Keyboard::Key::X: return dragon::Key::X;            ///< The X key
		case Keyboard::Key::Y: return dragon::Key::Y;            ///< The Y key
		case Keyboard::Key::Z: return dragon::Key::Z;            ///< The Z key
		case Keyboard::Key::Num0: return dragon::Key::Num0;         ///< The 0 key
		case Keyboard::Key::Num1: return dragon::Key::Num1;         ///< The 1 key
		case Keyboard::Key::Num2: return dragon::Key::Num2;         ///< The 2 key
		case Keyboard::Key::Num3: return dragon::Key::Num3;         ///< The 3 key
		case Keyboard::Key::Num4: return dragon::Key::Num4;         ///< The 4 key
		case Keyboard::Key::Num5: return dragon::Key::Num5;         ///< The 5 key
		case Keyboard::Key::Num6: return dragon::Key::Num6;         ///< The 6 key
		case Keyboard::Key::Num7: return dragon::Key::Num7;         ///< The 7 key
		case Keyboard::Key::Num8: return dragon::Key::Num8;         ///< The 8 key
		case Keyboard::Key::Num9: return dragon::Key::Num9;         ///< The 9 key
		case Keyboard::Key::Escape: return dragon::Key::Escape;       ///< The Escape key
		case Keyboard::Key::LControl: return dragon::Key::LControl;     ///< The left Control key
		case Keyboard::Key::LShift: return dragon::Key::LShift;       ///< The left Shift key
		case Keyboard::Key::LAlt: return dragon::Key::LAlt;         ///< The left Alt key
		case Keyboard::Key::LSystem: return dragon::Key::LSystem;      ///< The left OS specific key: window (Windows and Linux): apple (MacOS X): ...
		case Keyboard::Key::RControl: return dragon::Key::RControl;     ///< The right Control key
		case Keyboard::Key::RShift: return dragon::Key::RShift;       ///< The right Shift key
		case Keyboard::Key::RAlt: return dragon::Key::RAlt;         ///< The right Alt key
		case Keyboard::Key::RSystem: return dragon::Key::RSystem;      ///< The right OS specific key: window (Windows and Linux): apple (MacOS X): ...
		case Keyboard::Key::Menu: return dragon::Key::Menu;         ///< The Menu key
		case Keyboard::Key::LBracket: return dragon::Key::LBracket;     ///< The [ key
		case Keyboard::Key::RBracket: return dragon::Key::RBracket;     ///< The ] key
		case Keyboard::Key::Semicolon: return dragon::Key::Semicolon;    ///< The ; key
		case Keyboard::Key::Comma: return dragon::Key::Comma;        ///< The : key
		case Keyboard::Key::Period: return dragon::Key::Period;       ///< The . key
		case Keyboard::Key::Quote: return dragon::Key::Quote;        ///< The ' key
		case Keyboard::Key::Slash: return dragon::Key::Slash;        ///< The / key
		case Keyboard::Key::Backslash: return dragon::Key::Backslash;    ///< The \ key
		case Keyboard::Key::Tilde: return dragon::Key::Tilde;        ///< The ~ key
		case Keyboard::Key::Equal: return dragon::Key::Equal;        ///< The = key
		case Keyboard::Key::Hyphen: return dragon::Key::Hyphen;       ///< The - key (hyphen)
		case Keyboard::Key::Space: return dragon::Key::Space;        ///< The Space key
		case Keyboard::Key::Enter: return dragon::Key::Enter;        ///< The Enter/Return keys
		case Keyboard::Key::Backspace: return dragon::Key::Backspace;    ///< The Backspace key
		case Keyboard::Key::Tab: return dragon::Key::Tab;          ///< The Tabulation key
		case Keyboard::Key::PageUp: return dragon::Key::PageUp;       ///< The Page up key
		case Keyboard::Key::PageDown: return dragon::Key::PageDown;     ///< The Page down key
		case Keyboard::Key::End: return dragon::Key::End;          ///< The End key
		case Keyboard::Key::Home: return dragon::Key::Home;         ///< The Home key
		case Keyboard::Key::Insert: return dragon::Key::Insert;       ///< The Insert key
		case Keyboard::Key::Delete: return dragon::Key::Delete;       ///< The Delete key
		case Keyboard::Key::Add: return dragon::Key::Add;          ///< The + key
		case Keyboard::Key::Subtract: return dragon::Key::Subtract;     ///< The - key (minus: usually from numpad)
		case Keyboard::Key::Multiply: return dragon::Key::Multiply;     ///< The * key
		case Keyboard::Key::Divide: return dragon::Key::Divide;       ///< The / key
		case Keyboard::Key::Left: return dragon::Key::Left;         ///< Left arrow
		case Keyboard::Key::Right: return dragon::Key::Right;        ///< Right arrow
		case Keyboard::Key::Up: return dragon::Key::Up;           ///< Up arrow
		case Keyboard::Key::Down: return dragon::Key::Down;         ///< Down arrow
		case Keyboard::Key::Numpad0: return dragon::Key::Numpad0;      ///< The numpad 0 key
		case Keyboard::Key::Numpad1: return dragon::Key::Numpad0;      ///< The numpad 1 key
		case Keyboard::Key::Numpad2: return dragon::Key::Numpad0;      ///< The numpad 2 key
		case Keyboard::Key::Numpad3: return dragon::Key::Numpad0;      ///< The numpad 3 key
		case Keyboard::Key::Numpad4: return dragon::Key::Numpad0;      ///< The numpad 4 key
		case Keyboard::Key::Numpad5: return dragon::Key::Numpad0;      ///< The numpad 5 key
		case Keyboard::Key::Numpad6: return dragon::Key::Numpad0;      ///< The numpad 6 key
		case Keyboard::Key::Numpad7: return dragon::Key::Numpad0;      ///< The numpad 7 key
		case Keyboard::Key::Numpad8: return dragon::Key::Numpad0;      ///< The numpad 8 key
		case Keyboard::Key::Numpad9: return dragon::Key::Numpad0;      ///< The numpad 9 key
		case Keyboard::Key::F1: return dragon::Key::F1;           ///< The F1 key
		case Keyboard::Key::F2: return dragon::Key::F2;           ///< The F2 key
		case Keyboard::Key::F3: return dragon::Key::F3;           ///< The F3 key
		case Keyboard::Key::F4: return dragon::Key::F3;           ///< The F4 key
		case Keyboard::Key::F5: return dragon::Key::F3;           ///< The F5 key
		case Keyboard::Key::F6: return dragon::Key::F3;           ///< The F6 key
		case Keyboard::Key::F7: return dragon::Key::F3;           ///< The F7 key
		case Keyboard::Key::F8: return dragon::Key::F3;           ///< The F8 key
		case Keyboard::Key::F9: return dragon::Key::F3;           ///< The F9 key
		case Keyboard::Key::F10: return dragon::Key::F3;          ///< The F10 key
		case Keyboard::Key::F11: return dragon::Key::F3;          ///< The F11 key
		case Keyboard::Key::F12: return dragon::Key::F3;          ///< The F12 key
		case Keyboard::Key::F13: return dragon::Key::F3;          ///< The F13 key
		case Keyboard::Key::F14: return dragon::Key::F3;          ///< The F14 key
		case Keyboard::Key::F15: return dragon::Key::F3;          ///< The F15 key
		case Keyboard::Key::Pause: return dragon::Key::Pause;        ///< The Pause key
		}

		return dragon::Key::Unknown;
	}

	dragon::MouseButton sf::ConvertButton(Mouse::Button button)
	{
		switch (button)
		{
		case Mouse::Button::Left: return dragon::MouseButton::Left;
		case Mouse::Button::Middle: return dragon::MouseButton::Middle;
		case Mouse::Button::Right: return dragon::MouseButton::Right;
		}

		return dragon::MouseButton::Unknown;
	}
	
	PrimitiveType ConvertPrimitiveType(dragon::PrimitiveType primitiveType)
	{
		switch (primitiveType)
		{
		case dragon::PrimitiveType::Points: return PrimitiveType::Points;
		case dragon::PrimitiveType::Lines: return PrimitiveType::Lines;
		case dragon::PrimitiveType::LineStrip: return PrimitiveType::LineStrip;
		case dragon::PrimitiveType::Triangles: return PrimitiveType::Triangles;
		case dragon::PrimitiveType::TriangleStrip: return PrimitiveType::TriangleStrip;
		case dragon::PrimitiveType::TriangleFan: return PrimitiveType::TrianglesFan;
		default: assert("Invalid Primitive Type"); return PrimitiveType::Lines;
		}
	}
}
