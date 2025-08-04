#include "InputSystem.h"
#include <SDL3/SDL.h>

namespace viper {
    bool InputSystem::Initialize() {
        int numkeys;
        const bool* keyboardState = SDL_GetKeyboardState(&numkeys);

        m_keyboardState.resize(numkeys);
		std::copy(keyboardState, keyboardState + numkeys, m_keyboardState.begin());
		m_prevKeyboardState = m_keyboardState;

        SDL_GetMouseState(&m_mousePosition.x, &m_mousePosition.y);
        m_prevMousePosition = m_mousePosition;

        return true;
    }

    void InputSystem::Shutdown() {
        //
    }

    void InputSystem::Update() {
		//keyboard input
		m_prevKeyboardState = m_keyboardState;
        const bool* keyboardState = SDL_GetKeyboardState(nullptr);
        std::copy(keyboardState, keyboardState + m_keyboardState.size(), m_keyboardState.begin());

		//mosue input
        m_prevMousePosition = m_mousePosition;

		m_prevMouseButtonState = m_mouseButtonState;
        uint32_t mouseButtonState = SDL_GetMouseState(&m_mousePosition.x, &m_mousePosition.y);

        m_mouseButtonState[(uint8_t)MouseButton::Left] = mouseButtonState & SDL_BUTTON_LMASK;
		m_mouseButtonState[(uint8_t)MouseButton::Middle] = mouseButtonState & SDL_BUTTON_MMASK;
		m_mouseButtonState[(uint8_t)MouseButton::Right] = mouseButtonState & SDL_BUTTON_RMASK;
    }
};