/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include QMK_KEYBOARD_CONFIG_H

/* Use I2C or Serial, not both */

#define USE_SERIAL
// #define USE_I2C

/* Select hand configuration */

#define MASTER_LEFT

#define MOUSEKEY_DELAY             50
#define MOUSEKEY_INTERVAL          100
#define MOUSEKEY_MAX_SPEED         50
#define MOUSEKEY_TIME_TO_MAX       50
#define MOUSEKEY_WHEEL_MAX_SPEED   0
#define MOUSEKEY_WHEEL_TIME_TO_MAX 255

#define TAPPING_TERM               200
// #define _MASTER_RIGHT
// #define EE_HANDS

// Link time optimizations
/* #define NO_ACTION_MACRO */
/* #define NO_ACTION_FUNCTION */

#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT

#endif

