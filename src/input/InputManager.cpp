#include "InputManager.hpp"
#include "../LogFile.hpp"

namespace re
{
	namespace input
	{
		KeyEvent::KeyEvent(): key(), pressed(false)	{	}
		KeyEvent::KeyEvent(Key key, bool pressed): key(key), pressed(pressed)	{	}

		InputManager::InputManager() : messaging::Receiver<KeyEvent>()
		{
			memset(keystate, (int)KeyState::Idle, KEY_COUNT);
		}

		InputManager::InputManager(messaging::Emitter<KeyEvent> &emitter) : messaging::Receiver<KeyEvent>(emitter)
		{
			memset(keystate, (int)KeyState::Idle, KEY_COUNT);
		}

		KeyState InputManager::getKeyState(Key key) const
		{
			return keystate[int(key)];
		}

		bool InputManager::isKeyDown(Key key) const
		{
			return (byte(keystate[int(key)]) & ~byte(KeyState::Changed)) == byte(KeyState::Held); 
		}

		void InputManager::onReceive(const KeyEvent &event)
		{
			RE_LOG("Key %i %s.", event.key, event.pressed?"pressed":"released");

			keystate[int(event.key)] = event.pressed ? KeyState::Pressed : KeyState::Released;
		}

		void InputManager::updateKeyStates()
		{
			for(size_t i = 0; i < _countof(keystate); i++)
				keystate[i] = KeyState(byte(keystate[i]) & ~byte(KeyState::Changed));
		}
	}
}