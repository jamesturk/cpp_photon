//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: types.hpp,v 1.4 2005/03/01 07:51:04 cozman Exp $

#ifndef PHOTON_TYPES_HPP
#define PHOTON_TYPES_HPP

#include <boost/shared_ptr.hpp>

#include <string>
#include <vector>

// Title: Basic Types

namespace photon {

// Group: Basic Types

// Type: ubyte
//  Unsigned byte, alias for unsigned char.
typedef unsigned char ubyte;

// Type: uint
//  Alias for unsigned integer.
typedef unsigned int uint;

// Type: scalar
//  Scalar value, used throughout photon. (double or float)
typedef double scalar;

// Group: STL/Boost Types

// Type: StrVec
//  Typedef for vector of strings, which is used all throughout photon.
typedef std::vector<std::string> StrVec;

// Type: shared_ptr
//  Shared pointer type. (uses the boost implementation)
using boost::shared_ptr;

// Group: Enums

// Enum: KeyCode
// Enumeration defining keys, used in <AppCore::keyPressed>.
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

// Enum: MouseButton
// Enumeration defining buttons, used in <AppCore::mouseButtonPressed>.
// 
//  MB_LEFT     - Left mouse button.
//  MB_MIDDLE   - Middle mouse button.
//  MB_RIGHT    - Right mouse button.

}

#endif  //PHOTON_TYPES_HPP
