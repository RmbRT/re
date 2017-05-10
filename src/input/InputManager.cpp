#include "InputManager.hpp"
#include "../LogFile.hpp"

#include <GLFW/glfw3.h>

#include <cstring>

namespace re
{
	namespace input
	{
		namespace detail
		{
			Key glfw_constant_to_key(int glfw)
			{
				static util::Lookup<Key, unsigned short> const glfwKeys = {
					{Key::kUnknown, GLFW_KEY_UNKNOWN}, // will be handled separately because it has a negative value.
					{Key::kF1, GLFW_KEY_F1},
					{Key::kF2, GLFW_KEY_F2},
					{Key::kF3, GLFW_KEY_F3},
					{Key::kF4, GLFW_KEY_F4},
					{Key::kF5, GLFW_KEY_F5},
					{Key::kF6, GLFW_KEY_F6},
					{Key::kF7, GLFW_KEY_F7},
					{Key::kF8, GLFW_KEY_F8},
					{Key::kF9, GLFW_KEY_F9},
					{Key::kF10, GLFW_KEY_F10},
					{Key::kF11, GLFW_KEY_F11},
					{Key::kF12, GLFW_KEY_F12},
					{Key::kF13, GLFW_KEY_F13},
					{Key::kF14, GLFW_KEY_F14},
					{Key::kF15, GLFW_KEY_F15},
					{Key::kF16, GLFW_KEY_F16},
					{Key::kF17, GLFW_KEY_F17},
					{Key::kF18, GLFW_KEY_F18},
					{Key::kF19, GLFW_KEY_F19},
					{Key::kF20, GLFW_KEY_F20},
					{Key::kF21, GLFW_KEY_F21},
					{Key::kF22, GLFW_KEY_F22},
					{Key::kF23, GLFW_KEY_F23},
					{Key::kF24, GLFW_KEY_F24},
					{Key::kF25, GLFW_KEY_F25},

					{Key::kApostrophe, GLFW_KEY_APOSTROPHE},
					{Key::kComma, GLFW_KEY_COMMA},
					{Key::kMinus, GLFW_KEY_MINUS},
					{Key::kPeriod, GLFW_KEY_PERIOD},
					{Key::kSlash, GLFW_KEY_SLASH},
					{Key::kSemicolon, GLFW_KEY_SEMICOLON},
					{Key::kEqual, GLFW_KEY_EQUAL},
					{Key::kSpace, GLFW_KEY_SPACE},
					{Key::kLeftBracket, GLFW_KEY_LEFT_BRACKET},
					{Key::kBackslash, GLFW_KEY_BACKSLASH},
					{Key::kRightBracket, GLFW_KEY_RIGHT_BRACKET},
					{Key::kGraveAccent, GLFW_KEY_GRAVE_ACCENT},
					{Key::kWorld1, GLFW_KEY_WORLD_1},
					{Key::kWorld2, GLFW_KEY_WORLD_2},

					{Key::kEscape, GLFW_KEY_ESCAPE},
					{Key::kEnter, GLFW_KEY_ENTER},
					{Key::kTab, GLFW_KEY_TAB},
					{Key::kBackspace, GLFW_KEY_BACKSPACE},
					{Key::kInsert, GLFW_KEY_INSERT},
					{Key::kDelete, GLFW_KEY_DELETE},
					{Key::kPrintScreen, GLFW_KEY_PRINT_SCREEN},
					{Key::kPause, GLFW_KEY_PAUSE},
					{Key::kMenu, GLFW_KEY_MENU},

					{Key::k0, GLFW_KEY_0},
					{Key::k1, GLFW_KEY_1},
					{Key::k2, GLFW_KEY_2},
					{Key::k3, GLFW_KEY_3},
					{Key::k4, GLFW_KEY_4},
					{Key::k5, GLFW_KEY_5},
					{Key::k6, GLFW_KEY_6},
					{Key::k7, GLFW_KEY_7},
					{Key::k8, GLFW_KEY_8},
					{Key::k9, GLFW_KEY_9},

					{Key::kRight, GLFW_KEY_RIGHT},
					{Key::kLeft, GLFW_KEY_LEFT},
					{Key::kDown, GLFW_KEY_DOWN},
					{Key::kUp, GLFW_KEY_UP},

					{Key::kCapsLock, GLFW_KEY_CAPS_LOCK},
					{Key::kScrollLock, GLFW_KEY_SCROLL_LOCK},
					{Key::kNumLock, GLFW_KEY_NUM_LOCK},

					{Key::kA, GLFW_KEY_A},
					{Key::kB, GLFW_KEY_B},
					{Key::kC, GLFW_KEY_C},
					{Key::kD, GLFW_KEY_D},
					{Key::kE, GLFW_KEY_E},
					{Key::kF, GLFW_KEY_F},
					{Key::kG, GLFW_KEY_G},
					{Key::kH, GLFW_KEY_H},
					{Key::kI, GLFW_KEY_I},
					{Key::kJ, GLFW_KEY_J},
					{Key::kK, GLFW_KEY_K},
					{Key::kL, GLFW_KEY_L},
					{Key::kM, GLFW_KEY_M},
					{Key::kN, GLFW_KEY_N},
					{Key::kO, GLFW_KEY_O},
					{Key::kP, GLFW_KEY_P},
					{Key::kQ, GLFW_KEY_Q},
					{Key::kR, GLFW_KEY_R},
					{Key::kS, GLFW_KEY_S},
					{Key::kT, GLFW_KEY_T},
					{Key::kU, GLFW_KEY_U},
					{Key::kV, GLFW_KEY_V},
					{Key::kW, GLFW_KEY_W},
					{Key::kX, GLFW_KEY_X},
					{Key::kY, GLFW_KEY_Y},
					{Key::kZ, GLFW_KEY_Z},

					{Key::kKeyPad0, GLFW_KEY_KP_0},
					{Key::kKeyPad1, GLFW_KEY_KP_1},
					{Key::kKeyPad2, GLFW_KEY_KP_2},
					{Key::kKeyPad3, GLFW_KEY_KP_3},
					{Key::kKeyPad4, GLFW_KEY_KP_4},
					{Key::kKeyPad5, GLFW_KEY_KP_5},
					{Key::kKeyPad6, GLFW_KEY_KP_6},
					{Key::kKeyPad7, GLFW_KEY_KP_7},
					{Key::kKeyPad8, GLFW_KEY_KP_8},
					{Key::kKeyPad9, GLFW_KEY_KP_9},

					{Key::kPageUp, GLFW_KEY_PAGE_UP},
					{Key::kPageDown, GLFW_KEY_PAGE_DOWN},
					{Key::kHome, GLFW_KEY_HOME},
					{Key::kEnd, GLFW_KEY_END},
					{Key::kLeftShift, GLFW_KEY_LEFT_SHIFT},
					{Key::kLeftControl, GLFW_KEY_LEFT_CONTROL},
					{Key::kLeftAlt, GLFW_KEY_LEFT_ALT},
					{Key::kLeftSuper, GLFW_KEY_LEFT_SUPER},
					{Key::kRightShift, GLFW_KEY_RIGHT_SHIFT},
					{Key::kRightControl, GLFW_KEY_RIGHT_CONTROL},
					{Key::kRightAlt, GLFW_KEY_RIGHT_ALT},
					{Key::kRightSuper, GLFW_KEY_RIGHT_SUPER},

					{Key::kKeyPadDecimal, GLFW_KEY_KP_DECIMAL},
					{Key::kKeyPadDivide, GLFW_KEY_KP_DIVIDE},
					{Key::kKeyPadMultiply, GLFW_KEY_KP_MULTIPLY},
					{Key::kKeyPadSubtract, GLFW_KEY_KP_SUBTRACT},
					{Key::kKeyPadAdd, GLFW_KEY_KP_ADD},
					{Key::kKeyPadEnter, GLFW_KEY_KP_ENTER},
					{Key::kKeyPadEqual, GLFW_KEY_KP_EQUAL},
				};

				static bool initialised = false;
				static std::vector<Key> reverse_lookup(GLFW_KEY_LAST + 1);

				if(!initialised)
				{
					initialised = true;
					for(Key & key: reverse_lookup)
						key = Key::kUnknown;
					// skip the unknown key.
					for(size_t i = 1; i < RE_COUNT(Key); i++)
						reverse_lookup[glfwKeys[i]] = Key(i);
				}

				RE_DBG_ASSERT(glfw < GLFW_KEY_LAST);
				RE_DBG_ASSERT(glfw >= GLFW_KEY_UNKNOWN);

				if(glfw == GLFW_KEY_UNKNOWN)
					return Key::kUnknown;
				else
					return reverse_lookup[glfw];
			}

			MouseButton glfw_constant_to_mouse(int glfw)
			{
				static_assert(GLFW_MOUSE_BUTTON_LAST + 1 == RE_COUNT(MouseButton), "adjust enum");
				RE_DBG_ASSERT(RE_IN_ENUM(glfw, MouseButton));
				// the numerical values coincide.
				return MouseButton(glfw);
			}

			JoystickButton glfw_constant_to_joy(int glfw)
			{
				static_assert(GLFW_JOYSTICK_LAST + 1 == RE_COUNT(JoystickButton), "adjust enum");
				RE_DBG_ASSERT(RE_IN_ENUM(glfw, JoystickButton));
				// the numerical values coincide.
				return JoystickButton(glfw);
			}
		}

		KeyEvent::KeyEvent(): key(), pressed(false)	{	}
		KeyEvent::KeyEvent(Key key, bool pressed): key(key), pressed(pressed)	{	}

		void InputManager::onReceive(KeyEvent const& event)
		{
			RE_LOG("Key %i %s.", event.key, event.pressed?"pressed":"released");

			KeyState & ks = m_keyboard.keys[event.key];
			ks.changed = (ks.pressed != event.pressed);
			ks.pressed = event.pressed;
		}

		void InputManager::onReceive(
			MouseButtonEvent const& event)
		{
			KeyState &ks = m_mouse.buttons[event.button];
			ks.changed = ks.pressed != event.pressed;
			ks.pressed = event.pressed;
		}

		void InputManager::onReceive(
			MouseMoveEvent const& event)
		{
			RE_LOG("Mouse %f %f.", event.position.x, event.position.y);

			m_mouse.moved = event.position != m_mouse.position;
			m_mouse.position = event.position;
		}

		void InputManager::onReceive(
			JoystickAxesEvent const& event)
		{
			auto it = m_joysticks.find(event.joystick);
			RE_DBG_ASSERT(it != m_joysticks.end());
			RE_DBG_ASSERT(it->second.axes.size() == event.axes.size());

			it->second.axes = event.axes;
		}

		void InputManager::onReceive(
			JoystickButtonEvent const& event)
		{
			auto it = m_joysticks.find(event.joystick);
			RE_DBG_ASSERT(it != m_joysticks.end());

			KeyState &ks = it->second.buttons[event.button];
			ks.changed = ks.pressed != event.pressed;
			ks.pressed = event.pressed;
		}

		void InputManager::onReceive(
			JoystickConnectedEvent const& event)
		{
			Joystick stick;
			stick.axes.resize(event.axes);
			for(size_t i = 0; i < stick.buttons.size(); i++)
			{
				stick.buttons[i].pressed = false;
				stick.buttons[i].changed = false;
			}
			m_joysticks.emplace(event.joystick, std::move(stick));
		}

		void InputManager::onReceive(
			JoystickDisconnectedEvent const& event)
		{
			auto it = m_joysticks.find(event.joystick);
			RE_DBG_ASSERT(it != m_joysticks.end());

			m_joysticks.erase(it);
		}

		void InputManager::updateKeyStates()
		{
			m_keyboard.update_states();
			m_mouse.update_states();
			for(auto & joystick : m_joysticks)
				joystick.second.update_states();
		}

		void Keyboard::update_states()
		{
			for(size_t i = 0; i < RE_COUNT(Key); i++)
				keys[i].changed = false;
		}

		void Mouse::update_states()
		{
			for(size_t i = 0; i < RE_COUNT(MouseButton); i++)
				buttons[i].changed = false;
		}

		void Joystick::update_states()
		{
			for(size_t i = 0; i < RE_COUNT(JoystickButton); i++)
				buttons[i].changed = false;
		}
	}
}