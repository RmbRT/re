#ifndef __re_inputmanager_hpp_defined
#define __re_inputmanager_hpp_defined

#include "../defines.hpp"
#include "../messaging/Emitter.hpp"
#include "../types.hpp"

#include "../math/Vector.hpp"
#include "../util/Lookup.hpp"

#include <map>

namespace re
{
	namespace input
	{
		struct KeyEvent;
		class InputManager;

		enum class ModifierKey
		{
			kShift,
			kControl,
			kAlt,
			RE_LAST(kSuper)
		};

		typedef util::Lookup<ModifierKey, bool> ModifierKeys;

		struct KeyState
		{
			/** Whether the key is currently pressed. */
			bool pressed;
			/** Whether the key state changed in the last refresh. */
			bool changed;
		};

		/** Contains all the Keys used for input by the Engine. */
		enum class Key
		{
			kUnknown,
			/** F keys. */
			kF1,
			kF2,
			kF3,
			kF4,
			kF5,
			kF6,
			kF7,
			kF8,
			kF9,
			kF10,
			kF11,
			kF12,
			kF13,
			kF14,
			kF15,
			kF16,
			kF17,
			kF18,
			kF19,
			kF20,
			kF21,
			kF22,
			kF23,
			kF24,
			kF25,

			/** Printable keys. */
			kApostrophe,
			kComma,
			kMinus,
			kPeriod,
			kSlash,
			kSemicolon,
			kEqual,
			kSpace,
			kLeftBracket,
			kBackslash,
			kRightBracket,
			kGraveAccent,
			kWorld1,
			kWorld2,

			/** Function keys. */
			kEscape,
			kEnter,
			kTab,
			kBackspace,
			kInsert,
			kDelete,
			kPrintScreen,
			kPause,
			kMenu,

			/** Number keys. */
			k0,
			k1,
			k2,
			k3,
			k4,
			k5,
			k6,
			k7,
			k8,
			k9,

			kRight,
			kLeft,
			kDown,
			kUp,

			kCapsLock,
			kScrollLock,
			kNumLock,

			/** Letter keys. */
			kA,
			kB,
			kC,
			kD,
			kE,
			kF,
			kG,
			kH,
			kI,
			kJ,
			kK,
			kL,
			kM,
			kN,
			kO,
			kP,
			kQ,
			kR,
			kS,
			kT,
			kU,
			kV,
			kW,
			kX,
			kY,
			kZ,

			kKeyPad0,
			kKeyPad1,
			kKeyPad2,
			kKeyPad3,
			kKeyPad4,
			kKeyPad5,
			kKeyPad6,
			kKeyPad7,
			kKeyPad8,
			kKeyPad9,

			kPageUp,
			kPageDown,
			kHome,
			kEnd,
			kLeftShift,
			kLeftControl,
			kLeftAlt,
			kLeftSuper,
			kRightShift,
			kRightControl,
			kRightAlt,
			kRightSuper,

			kKeyPadDecimal,
			kKeyPadDivide,
			kKeyPadMultiply,
			kKeyPadSubtract,
			kKeyPadAdd,
			kKeyPadEnter,
			RE_LAST(kKeyPadEqual)
		};

		/** Includes all mouse buttons. */
		enum class MouseButton
		{
			k1, kLeft=k1,
			k2, kRight=k2,
			k3, kMiddle=k3,
			k4,
			k5,
			k6,
			k7,
			RE_LAST(k8)
		};

		/** Includes all joystick buttons. */
		enum class JoystickButton
		{
			k1,
			k2,
			k3,
			k4,
			k5,
			k6,
			k7,
			k8,
			k9,
			k10,
			k11,
			k12,
			k13,
			k14,
			k15,
			RE_LAST(k16)
		};

		class Keyboard
		{
		public:
			util::Lookup<Key, KeyState> keys;

			void update_states();
		};

		class Joystick
		{
		public:
			std::vector<double> axes;
			util::Lookup<JoystickButton, KeyState> buttons;

			void update_states();
		};

		class Mouse
		{
		public:
			math::dvec2_t position;
			bool moved;
			util::Lookup<MouseButton, KeyState> buttons;

			void update_states();
		};

		namespace detail
		{
			/** Converts a glfw key constant to a Key. */
			Key glfw_constant_to_key(int glfw);
			/** Converts a glfw mouse constant to a MouseButton. */
			MouseButton glfw_constant_to_mouse(int glfw);
			/** Converts a glfw joystick constant to a JoystickButton. */
			JoystickButton glfw_constant_to_joy(int glfw);
		}

		/** Describes a key input event.
			It is passed to the InputManager class. Consists of a Key, whether it was pressed, and the time the event was created. */
		struct KeyEvent
		{
			/** The key of the event. */
			Key key;
			/** Whether the key was pressed or released. */
			bool pressed;

			KeyEvent();
			KeyEvent(Key key, bool pressed);
		};

		struct MouseMoveEvent
		{
			math::dvec2_t position;
		};

		struct MouseButtonEvent
		{
			MouseButton button;
			bool pressed;
		};

		struct JoystickAxesEvent
		{
			size_t joystick;
			std::vector<double> axes;
		};

		struct JoystickButtonEvent
		{
			size_t joystick;
			JoystickButton button;
			bool pressed;
		};

		struct JoystickConnectedEvent
		{
			size_t joystick;
			size_t axes;
		};

		struct JoystickDisconnectedEvent
		{
			size_t joystick;
		};


		/** Manages input events and stores the current input state.
		@usage:
			Can be registered as a KeyEvent Receiver to a `Window`. After being registered, it can be used to fetch the current input state for that Window. @see `KeyState`. */
		class InputManager:
			public messaging::Receiver<KeyEvent>,
			public messaging::Receiver<MouseButtonEvent>,
			public messaging::Receiver<MouseMoveEvent>,
			public messaging::Receiver<JoystickAxesEvent>,
			public messaging::Receiver<JoystickButtonEvent>,
			public messaging::Receiver<JoystickConnectedEvent>,
			public messaging::Receiver<JoystickDisconnectedEvent>
		{
			/** Stores the input state of the InputManager. */
			Keyboard m_keyboard;
			Mouse m_mouse;
			std::map<size_t, Joystick> m_joysticks;

			void onReceive(KeyEvent const& event) override;
			void onReceive(MouseButtonEvent const& event) override;
			void onReceive(MouseMoveEvent const& event) override;
			void onReceive(JoystickAxesEvent const& event) override;
			void onReceive(JoystickButtonEvent const& event) override;
			void onReceive(JoystickConnectedEvent const& event) override;
			void onReceive(JoystickDisconnectedEvent const& event) override;
		public:

			REIL Keyboard const& keyboard() const;
			REIL Mouse const& mouse() const;
			REIL std::map<size_t, Joystick> const& joysticks() const;

			/** Removes the KeyState::Changed flag from the KeyStates. Call this every tick before polling events. */
			void updateKeyStates();
		};
	}
}

#endif