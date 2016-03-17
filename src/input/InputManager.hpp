#ifndef __re_inputmanager_hpp_defined
#define __re_inputmanager_hpp_defined

#include "../defines.hpp"
#include "../messaging/Emitter.hpp"
#include "../types.hpp"

#ifdef MB_RIGHT
#undef MB_RIGHT
#endif

namespace re
{
	namespace input
	{
		
		struct KeyEvent;
		class InputManager;

		enum class ModifierKey
		{
			MODIFIER_SHIFT = 1,
			MODIFIER_CONTROL = 2,
			MODIFIER_ALT = 4,
			MODIFIER_SUPER = 8
		};

		/*Contains all the Keys used for input by the Engine. The values are continuous from 0 to KEY_COUNT-1.
		The keys 0-9, A-Z have their character (uppercase) values as enum values.
		@see KEY_COUNT: The count of enum values. Also the first invalid key value.*/
		enum class Key
		{
			
			K_F1,K_F2,K_F3,K_F4,K_F5,K_F6,K_F7,K_F8,K_F9,K_F10,K_F11,K_F12,K_F13,K_F14,K_F15,K_F16,K_F17,K_F18,K_F19,K_F20,K_F21,K_F22,K_F23,K_F24,K_F25,
			/*Printable keys.*/
			K_APOSTROPHE,K_COMMA,K_MINUS,K_PERIOD,K_SLASH,K_SEMICOLON,K_EQUAL,K_SPACE,K_LEFT_BRACKET,K_BACKSLASH,K_RIGHT_BRACKET,K_GRAVE_ACCENT,K_WORLD_1,K_WORLD_2,
			/*Function keys.*/
			K_ESCAPE,K_ENTER,K_TAB,K_BACKSPACE,K_INSERT,K_DELETE,K_PRINT_SCREEN,K_PAUSE,K_MENU,
			/*Number keys.*/
			K_0='0',K_1,K_2,K_3,K_4,K_5,K_6,K_7,K_8,K_9,
			
			K_RIGHT,K_LEFT,K_DOWN,K_UP,
			K_CAPS_LOCK,K_SCROLL_LOCK,K_NUM_LOCK,

			/*Letter keys.*/
			K_A='A',K_B,K_C,K_D,K_E,K_F,K_G,K_H,K_I,K_J,K_K,K_L,K_M,K_N,K_O,K_P,K_Q,K_R,K_S,K_T,K_U,K_V,K_W,K_X,K_Y,K_Z,
			K_KP0,K_KP1,K_KP2,K_KP3,K_KP4,K_KP5,K_KP6,K_KP7,K_KP8,K_KP9,
			
			K_PAGE_UP,K_PAGE_DOWN,K_HOME,K_END,
			K_LEFT_SHIFT,K_LEFT_CONTROL,K_LEFT_ALT,K_LEFT_SUPER,K_RIGHT_SHIFT,K_RIGHT_CONTROL,K_RIGHT_ALT,K_RIGHT_SUPER,
			K_KP_DECIMAL,K_KP_DIVIDE,K_KP_MULTIPLY,K_KP_SUBTRACT,K_KP_ADD,K_KP_ENTER,K_KP_EQUAL,

			/*Mouse buttons*/
			MB_1,MB_LEFT=MB_1,MB_2,MB_RIGHT=MB_2,MB_3,MB_MIDDLE=MB_3,MB_4,MB_5,MB_6,MB_7,MB_8,

			/*Joystick buttons*/
			JOY_1,JOY_2,JOY_3,JOY_4,JOY_5,JOY_6,JOY_7,JOY_8,JOY_9,JOY_10,JOY_11,JOY_12,JOY_13,JOY_14,JOY_15,JOY_16
		};
		/*The count of enum values in @{re::input::Key}. Also the first invalid integer representing a Key.*/
		const unsigned KEY_COUNT = 144;

		/*Describes a key input event. It is passed to the InputManager class.
		Consists of a Key, whether it was pressed, and the time the event was created.*/
		struct KeyEvent
		{
			/*The key of the event.*/
			Key key;
			/*Whether the key was pressed or released.*/
			bool pressed;


			KeyEvent();
			KeyEvent(Key key, bool pressed);
		};

		enum class KeyState: byte
		{
			Changed = 1,
			Idle = 0,
			Held = 2,
			Released = Idle | Changed,
			Pressed = Held | Changed
		};

		/*Manages input events and stores the current input state.
		@usage:
			Can be registered as a KeyEvent Receiver to a @{re::Window}. After being registered, it can be used to
			fetch the current input state for that Window. @see @{re::input::KeyState}.*/
		class InputManager : public messaging::Receiver<KeyEvent>
		{
			/*Stores the input state of the InputManager.*/
			KeyState keystate[KEY_COUNT];

			void onReceive(const KeyEvent &event) override;
		public:
			/*Creates an InputManager instance. Initializes all keys to be released.
			@note: The new InputManager does not yet listen to any KeyEvent Emitters.*/
			InputManager();
			/*Creates an InputManager instance that listens to the given KeyEvent Emitter.*/
			InputManager(messaging::Emitter<KeyEvent> &emitter);
			/*Returns the KeyState associated with the given Key.
			@param[in] key: The Key enum value representing the Key to return.
			@return: the KeyState associated with key.
			@see InputManager::keystate, KeyState*/
			KeyState getKeyState(Key key) const;

			/*Returns whether the given Key is down or not, ignoring whether it was changed this tick or not.
			@param[in] key: The Key enum value representing the Key to return.
			@return: whether the KeyState is KeyState::Held or KeyState::Idle
				(or their respective KeyState::Changed values).*/
			bool isKeyDown(Key key) const;

			/*Removes the KeyState::Changed flag from the KeyStates. Call this every tick before polling events.*/
			void updateKeyStates();
		};
	}
}

#endif