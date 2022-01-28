#include "KeyboardInput.h"

//#define DEBUG_OUTPUT_KEYBOARD_INPUT

#ifdef DEBUG_OUTPUT_KEYBOARD_INPUT
#include<iostream>
#endif // DEBUG_OUTPUT_KEYBOARD_INPUT

KeyboardInput* KeyboardInput::s_instance = 0;

KeyboardInput::KeyboardInput()
{
}

KeyboardInput* KeyboardInput::Instance()
{
    //#ifdef DEBUG_OUTPUT_KEYBOARD_INPUT
    //std::cout << "Called for KeyboardInput::Instance()" << std::endl;
    //#endif // DEBUG_OUTPUT_KEYBOARD_INPUT
    if (s_instance == 0) {
        //#ifdef DEBUG_OUTPUT_KEYBOARD_INPUT
        //std::cout << "Made first KeyboardInput" << std::endl;
        //#endif // DEBUG_OUTPUT_KEYBOARD_INPUT
        s_instance = new KeyboardInput();
    }
    return s_instance;
}

void KeyboardInput::TurnKeyOn(SDL_Keycode key)
{
    /*if (key == SDLK_DOWN || key == SDLK_UP ||
        key == SDLK_LEFT || key == SDLK_RIGHT)
    {
        m_keys_pressed[SDLK_DOWN]  = false;
        m_keys_pressed[SDLK_UP]    = false;
        m_keys_pressed[SDLK_LEFT]  = false;
        m_keys_pressed[SDLK_RIGHT] = false;
    }*/
    m_keys_pressed[key] = true;
    #ifdef DEBUG_OUTPUT_KEYBOARD_INPUT
    std::cout << key << " is pressed" << std::endl;
    #endif // DEBUG_OUTPUT_KEYBOARD_INPUT
}

void KeyboardInput::TurnKeyOff(SDL_Keycode key)
{
    m_keys_pressed[key] = false;
    //m_keys_pressed.erase(key);
    #ifdef DEBUG_OUTPUT_KEYBOARD_INPUT
    std::cout << key << " is released" << std::endl;
    #endif // DEBUG_OUTPUT_KEYBOARD_INPUT
}

bool KeyboardInput::IsKeyOn(SDL_Keycode key)
{
    bool keyPressed = false;
    if (m_keys_pressed.count(key) > 0) {
        keyPressed = m_keys_pressed[key];
        m_keys_pressed[key] = false;
        
    }
    return keyPressed;
}

