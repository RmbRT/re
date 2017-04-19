#include "InputManager.hpp"
#include "../LogFile.hpp"

#include <cstring>

namespace re
{
	namespace input
	{
		KeyEvent::KeyEvent(): key(), pressed(false)	{	}
		KeyEvent::KeyEvent(Key key, bool pressed): key(key), pressed(pressed)	{	}

		InputManager::InputManager() : messaging::Receiver<KeyEvent>()
		{
			std::memset(keystate, (int)KeyState::Idle, KEY_COUNT);
		}

		InputManager::InputManager(messaging::Emitter<KeyEvent> &emitter) : messaging::Receiver<KeyEvent>(emitter)
		{
			std::memset(keystate, (int)KeyState::Idle, KEY_COUNT);
		}

		KeyState InputManager::getKeyState(Key key) const
		{
			return keystate[int(key)];
		}

		bool InputManager::isKeyDown(Key key) const
		{
			return (byte_t(keystate[int(key)]) & ~byte_t(KeyState::Changed)) == byte_t(KeyState::Held);
		}

		void InputManager::onReceive(const KeyEvent &event)
		{
			RE_LOG("Key %i %s.", event.key, event.pressed?"pressed":"released");

			keystate[int(event.key)] = event.pressed ? KeyState::Pressed : KeyState::Released;
		}

		void InputManager::updateKeyStates()
		{
			for(size_t i = 0; i < _countof(keystate); i++)
				keystate[i] = KeyState(byte_t(keystate[i]) & ~byte_t(KeyState::Changed));
		}
	}
}