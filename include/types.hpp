//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: types.hpp,v 1.10 2005/11/15 02:59:08 cozman Exp $

#ifndef PHOTON_TYPES_HPP
#define PHOTON_TYPES_HPP

#include <boost/shared_ptr.hpp>

#include <string>
#include <vector>

#include "GL/glfw.h"   //This file depends on glfw

// Title: Basic Types

namespace photon 
{

// Group: Basic Types

// Type: ubyte
//  Unsigned byte, alias for unsigned char.
typedef unsigned char ubyte;

// Type: uint
//  Alias for unsigned integer.
typedef unsigned int uint;

// Type: scalar
//  Scalar value, used throughout photon in place of double or float
typedef double scalar;

// Group: STL/Boost Types

// Type: StrVec
//  Typedef for vector of strings, which is used throughout photon.
typedef std::vector<std::string> StrVec;

// Type: shared_ptr
//  Shared pointer type. (uses the boost implementation)
using boost::shared_ptr;

// Group: Enums

// Enum: KeyCode
// Enumeration for keys, includes printable characters and special keys.
//
//  Keys are shown roughly in the order they appear on the keyboard to aid 
//  finding a specific key.
//
// Enums:
//  KEY_ESC  - Escape key
//  KEY_F1   - F1 key
//  KEY_F2   - F2 key
//  KEY_F3   - F3 key
//  KEY_F4   - F4 key
//  KEY_F5   - F5 key
//  KEY_F6   - F6 key
//  KEY_F7   - F7 key
//  KEY_F8   - F8 key
//  KEY_F9   - F9 key
//  KEY_F10  - F10 key
//  KEY_F11  - F11 key
//  KEY_F12  - F12 key
//  KEY_F13  - F13 key
//  KEY_F14  - F14 key
//  KEY_F15  - F15 key
//  KEY_F16  - F16 key
//  KEY_F17  - F17 key
//  KEY_F18  - F18 key
//  KEY_F19  - F19 key
//  KEY_F20  - F20 key
//  KEY_F21  - F21 key
//  KEY_F22  - F22 key
//  KEY_F23  - F23 key
//  KEY_F24  - F24 key
//  KEY_F25  - F25 key
//
//  KEY_INSERT   - Insert key
//  KEY_HOME     - Home key
//  KEY_PGUP     - Page up key
//  KEY_DELETE   - Delete key
//  KEY_END      - End key
//  KEY_PGDOWN   - Page down key
//  KEY_UP       - Up arrow key
//  KEY_LEFT     - Left arrow key
//  KEY_DOWN     - Down arrow key
//  KEY_RIGHT    - Right arrow key
//
//  KEY_TILDE    - Tilde key
//  KEY_1        - 1 key
//  KEY_2        - 2 key
//  KEY_3        - 3 key
//  KEY_4        - 4 key
//  KEY_5        - 5 key
//  KEY_6        - 6 key
//  KEY_7        - 7 key
//  KEY_8        - 8 key
//  KEY_9        - 9 key
//  KEY_0        - 0 key
//  KEY_MINUS    - Minus key
//  KEY_EQUAL    - Equal key
//  KEY_BACKSPACE- Backspace key
//
//  KEY_TAB      - Tab key
//  KEY_Q        - Q key
//  KEY_W        - W key
//  KEY_E        - E key
//  KEY_R        - R key
//  KEY_T        - T key
//  KEY_Y        - Y key
//  KEY_U        - U key
//  KEY_I        - I key
//  KEY_O        - O key
//  KEY_P        - P key
//  KEY_LBRAC    - Left bracket [ key
//  KEY_RBRAC    - Right bracket ] key
//  KEY_BKSLASH  - Backslash \ key
//
//  KEY_A        - A key
//  KEY_S        - S key
//  KEY_D        - D key
//  KEY_F        - F key
//  KEY_G        - G key
//  KEY_H        - H key
//  KEY_J        - J key
//  KEY_K        - K key
//  KEY_L        - L key
//  KEY_COLON    - Colon :  key
//  KEY_QUOTE    - Quote " key
//  KEY_RETURN   - Enter/Return key
//
//  KEY_LSHIFT   - Left shift key
//  KEY_Z        - Z key
//  KEY_X        - X key
//  KEY_C        - C key
//  KEY_V        - V key
//  KEY_B        - B key
//  KEY_N        - N key
//  KEY_M        - M key
//  KEY_COMMA    - Comma , key
//  KEY_PERIOD   - Period . key
//  KEY_SLASH    - Slash / key
//  KEY_RSHIFT   - Right shift key
//
//  KEY_LCTRL    - Left control key
//  KEY_LALT     - Left alt key
//  KEY_SPACE    - Space bar key
//  KEY_RALT     - Right alt key
//  KEY_RCTRL    - Right control key
//
//  KEY_NUM_SLASH    - Numpad slash / key
//  KEY_NUM_ASTERIX  - Numpad asterix * key
//  KEY_NUM_MINUS    - Numpad minus - key
//  KEY_NUM_PLUS     - Numpad plus + key
//  KEY_NUM_ENTER    - Numpad enter key
//  KEY_NUM_PERIOD   - Numpad period . key
//  KEY_NUM_0        - Numpad 0 key
//  KEY_NUM_1        - Numpad 1 key
//  KEY_NUM_2        - Numpad 2 key
//  KEY_NUM_3        - Numpad 3 key
//  KEY_NUM_4        - Numpad 4 key
//  KEY_NUM_5        - Numpad 5 key
//  KEY_NUM_6        - Numpad 6 key
//  KEY_NUM_7        - Numpad 7 key
//  KEY_NUM_8        - Numpad 8 key
//  KEY_NUM_9        - Numpad 9 key
enum KeyCode
{
    //TOP ROW
    KEY_ESC  =GLFW_KEY_ESC,
    KEY_F1   =GLFW_KEY_F1,
    KEY_F2   =GLFW_KEY_F2,
    KEY_F3   =GLFW_KEY_F3,
    KEY_F4   =GLFW_KEY_F4,
    KEY_F5   =GLFW_KEY_F5,
    KEY_F6   =GLFW_KEY_F6,
    KEY_F7   =GLFW_KEY_F7,
    KEY_F8   =GLFW_KEY_F8,
    KEY_F9   =GLFW_KEY_F9,
    KEY_F10  =GLFW_KEY_F10,
    KEY_F11  =GLFW_KEY_F11,
    KEY_F12  =GLFW_KEY_F12,
    KEY_F13  =GLFW_KEY_F13,
    KEY_F14  =GLFW_KEY_F14,
    KEY_F15  =GLFW_KEY_F15,
    KEY_F16  =GLFW_KEY_F16,
    KEY_F17  =GLFW_KEY_F17,
    KEY_F18  =GLFW_KEY_F18,
    KEY_F19  =GLFW_KEY_F19,
    KEY_F20  =GLFW_KEY_F20,
    KEY_F21  =GLFW_KEY_F21,
    KEY_F22  =GLFW_KEY_F22,
    KEY_F23  =GLFW_KEY_F23,
    KEY_F24  =GLFW_KEY_F24,
    KEY_F25  =GLFW_KEY_F25,

    //MIDDLE SECTION
    //PRINT SCREEN
    //SCROLL LOCK
    //PAUSE
    KEY_INSERT   =GLFW_KEY_INSERT,
    KEY_HOME     =GLFW_KEY_HOME,
    KEY_PGUP     =GLFW_KEY_PAGEUP,
    KEY_DELETE   =GLFW_KEY_DEL,
    KEY_END      =GLFW_KEY_END,
    KEY_PGDOWN   =GLFW_KEY_PAGEDOWN,
    KEY_UP       =GLFW_KEY_UP,
    KEY_LEFT     =GLFW_KEY_LEFT,
    KEY_DOWN     =GLFW_KEY_DOWN,
    KEY_RIGHT    =GLFW_KEY_RIGHT,

    //TOP ROW
    KEY_TILDE    ='`',
    KEY_1        ='1',
    KEY_2        ='2',
    KEY_3        ='3',
    KEY_4        ='4',
    KEY_5        ='5',
    KEY_6        ='6',
    KEY_7        ='7',
    KEY_8        ='8',
    KEY_9        ='9',
    KEY_0        ='0',
    KEY_MINUS    ='-',
    KEY_EQUAL    ='=',
    KEY_BACKSPACE=GLFW_KEY_BACKSPACE,

    //SECOND ROW
    KEY_TAB      =GLFW_KEY_TAB,
    KEY_Q        ='Q',
    KEY_W        ='W',
    KEY_E        ='E',
    KEY_R        ='R',
    KEY_T        ='T',
    KEY_Y        ='Y',
    KEY_U        ='U',
    KEY_I        ='I',
    KEY_O        ='O',
    KEY_P        ='P',
    KEY_LBRAC    ='[',
    KEY_RBRAC    =']',
    KEY_BKSLASH  ='\\',

    //HOME ROW
    //CAPS LOCK
    KEY_A        ='A',
    KEY_S        ='S',
    KEY_D        ='D',
    KEY_F        ='F',
    KEY_G        ='G',
    KEY_H        ='H',
    KEY_J        ='J',
    KEY_K        ='K',
    KEY_L        ='L',
    KEY_COLON    =';',
    KEY_QUOTE    ='\'',
    KEY_RETURN   =GLFW_KEY_ENTER,

    //BOTTOM ROW
    KEY_LSHIFT   =GLFW_KEY_LSHIFT,
    KEY_Z        ='Z',
    KEY_X        ='X',
    KEY_C        ='C',
    KEY_V        ='V',
    KEY_B        ='B',
    KEY_N        ='N',
    KEY_M        ='M',
    KEY_COMMA    =',',
    KEY_PERIOD   ='.',
    KEY_SLASH    ='/',
    KEY_RSHIFT   =GLFW_KEY_RSHIFT,

    //SPACE ROW
    KEY_LCTRL    =GLFW_KEY_LCTRL,
    //WINDOWS KEY
    KEY_LALT     =GLFW_KEY_LALT,
    KEY_SPACE    =GLFW_KEY_SPACE,
    KEY_RALT     =GLFW_KEY_RALT,
    //WINDOWS KEY
    //TASK KEY
    KEY_RCTRL    =GLFW_KEY_RCTRL,

    //NUMPAD
    //NUMLOCK
    KEY_NUM_SLASH    =GLFW_KEY_KP_DIVIDE,
    KEY_NUM_ASTERIX  =GLFW_KEY_KP_MULTIPLY,
    KEY_NUM_MINUS    =GLFW_KEY_KP_SUBTRACT,
    KEY_NUM_PLUS     =GLFW_KEY_KP_ADD,
    KEY_NUM_ENTER    =GLFW_KEY_KP_ENTER,
    KEY_NUM_PERIOD   =GLFW_KEY_KP_DECIMAL,
    KEY_NUM_0        =GLFW_KEY_KP_0,
    KEY_NUM_1        =GLFW_KEY_KP_1,
    KEY_NUM_2        =GLFW_KEY_KP_2,
    KEY_NUM_3        =GLFW_KEY_KP_3,
    KEY_NUM_4        =GLFW_KEY_KP_4,
    KEY_NUM_5        =GLFW_KEY_KP_5,
    KEY_NUM_6        =GLFW_KEY_KP_6,
    KEY_NUM_7        =GLFW_KEY_KP_7,
    KEY_NUM_8        =GLFW_KEY_KP_8,
    KEY_NUM_9        =GLFW_KEY_KP_9
};

// Enum: MouseButton
// Enumeration defining mouse buttons.
//
//  MB_LEFT     - Left mouse button.
//  MB_MIDDLE   - Middle mouse button.
//  MB_RIGHT    - Right mouse button.
enum MouseButton 
{
    MB_LEFT     =GLFW_MOUSE_BUTTON_LEFT,
    MB_MIDDLE   =GLFW_MOUSE_BUTTON_MIDDLE,
    MB_RIGHT    =GLFW_MOUSE_BUTTON_RIGHT
};

// Enum: ScrollDir
// Enumeration defining scroll direction of mouse wheel.
//
//  SCROLL_UP   - Wheel was scrolled up.
//  SCROLL_DOWN - Wheel was scrolled down.
enum ScrollDir
{
    SCROLL_UP, SCROLL_DOWN
};

// Enum: DisplayMode
// Enumeration defining types of displays.
//
//  DISP_WINDOWED   - Windowed Mode
//  DISP_FULLSCREEN - Fullscreen Mode
enum DisplayMode
{
    DISP_WINDOWED, DISP_FULLSCREEN
};

}

#endif  //PHOTON_TYPES_HPP
