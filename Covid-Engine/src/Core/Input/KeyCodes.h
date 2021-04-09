#pragma once

namespace Covid
{
    enum class KeyCode
    {
        /// <summary>
        /// This is the keycode that is returned when the key that was pressed on the 
        /// keyboard is an unknow key.
        /// </summary>
        Unknown = -1,

        /* Printable Keys */

        /// <summary>
        /// The space bar key.
        /// </summary>
        Space = 32,

        /// <summary>
        /// '
        /// </summary>
        Apostrophe = 39,

        /// <summary>
        /// ,
        /// </summary>
        Comma = 44,

        /// <summary>
        /// -
        /// </summary>
        Minus = 45,

        /// <summary>
        /// .
        /// </summary>
        Period = 46,

        /// <summary>
        /// /
        /// </summary>
        Slash = 47,

        /// <summary>
        /// Alphanumeric 0
        /// </summary>
        Num_0 = 48,

        /// <summary>
        /// Alphanumeric 1
        /// </summary>
        Num_1,

        /// <summary>
        /// Alphanumeric 2
        /// </summary>
        Num_2,

        /// <summary>
        /// Alphanumeric 3
        /// </summary>
        Num_3,

        /// <summary>
        /// Alphanumeric 4
        /// </summary>
        Num_4,

        /// <summary>
        /// Alphanumeric 5
        /// </summary>
        Num_5,

        /// <summary>
        /// Alphanumeric 6
        /// </summary>
        Num_6,

        /// <summary>
        /// Alphanumeric 7
        /// </summary>
        Num_7,

        /// <summary>
        /// Alphanumeric 8
        /// </summary>
        Num_8,

        /// <summary>
        /// Alphanumeric 9
        /// </summary>
        Num_9,

        /// <summary>
        /// ;
        /// </summary>
        Semicolon = 59,

        /// <summary>
        /// =
        /// </summary>
        Equals = 61,

        A = 65,
        B, C, D, E, F, G, H, I,
        J, K, L, M, N, O, P, Q,
        R, S, T, U, V, X, Y, Z,

        /// <summary>
        /// [
        /// </summary>
        LBracket = 91,

        /// <summary>
        /// \
        /// </summary>
        Backslash,

        /// <summary>
        /// ]
        /// </summary>
        RBracket,

        /// <summary>
        /// `
        /// <para>AKA Backtick</para>
        /// </summary>
        Grave = 96,

        World_1 = 161,
        World_2,

        /* Function Keys */

        Escape = 256,
        Enter = 257,
        Tab = 258,
        Backspace = 259,
        Insert = 260,
        Delete = 261,

        /// <summary>
        /// Right Arrow
        /// </summary>
        Right = 262,

        /// <summary>
        /// Left Arrow
        /// </summary>
        Left,

        /// <summary>
        /// Down Arrow
        /// </summary>
        Down,

        /// <summary>
        /// Up Arrow
        /// </summary>
        Up,

        PageUp,
        PageDown,
        Home,
        End,
        CapsLock = 280,
        ScrollLock,
        NumLock,
        PrintScreen,
        Pause,

        F1 = 290,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        F13,
        F14,
        F15,
        F16,
        F17,
        F18,
        F19,
        F20,
        F21,
        F22,
        F23,
        F24,
        F25,

        /// <summary>
        /// Keypad Number 0
        /// </summary>
        KP_0 = 320,

        /// <summary>
        /// Keypad Number 1
        /// </summary>
        KP_1,

        /// <summary>
        /// Keypad Number 2
        /// </summary>
        KP_2,

        /// <summary>
        /// Keypad Number 3
        /// </summary>
        KP_3,

        /// <summary>
        /// Keypad Number 4
        /// </summary>
        KP_4,

        /// <summary>
        /// Keypad Number 5
        /// </summary>
        KP_5,

        /// <summary>
        /// Keypad Number 6
        /// </summary>
        KP_6,

        /// <summary>
        /// Keypad Number 7
        /// </summary>
        KP_7,

        /// <summary>
        /// Keypad Number 8
        /// </summary>
        KP_8,

        /// <summary>
        /// Keypad Number 9
        /// </summary>
        KP_9,

        KP_Decimal,
        KP_Divide,
        KP_Multiply,
        KP_Subtract,
        KP_Add,
        KP_Enter,
        KP_Equals,

        LShift = 340,
        LCtrl,
        LAlt,
        LSuper,
        RShift,
        RCtrl,
        RAlt,
        RSuper,
        Menu,

        LastKey = Menu
    };
}

