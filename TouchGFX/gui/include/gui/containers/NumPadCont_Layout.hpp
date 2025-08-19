#ifndef NUMPADCONT_KEY_LAYOUT_HPP
#define NUMPADCONT_KEY_LAYOUT_HPP

#include <touchgfx/widgets/Keyboard.hpp>
#include <touchgfx/hal/Types.hpp>
#include <fonts/ApplicationFontProvider.hpp>
#include "BitmapDatabase.hpp"
#include <texts/TextKeysAndLanguages.hpp>

using namespace touchgfx;

static const int KEY_WIDTH_NUMERIC  = 70;
static const int KEY_HEIGHT_NUMERIC = 70;
static const int KEY0_WIDTH_NUMERIC  = 144;
static const int KEY0_HEIGHT_NUMERIC = 70;

static const int BACKSPACE_WIDTH_NUMERIC  = 70;
static const int BACKSPACE_HEIGHT_NUMERIC = 144;
static const int ENTER_WIDTH_NUMERIC  = 70;
static const int ENTER_HEIGHT_NUMERIC = 144;


/**
 * Array specifying the keys used in the CustomKeyboard.
 */
static const Keyboard::Key keyArrayNumeric[10] =
{
    { 1, Rect(  9, 210,	KEY_WIDTH_NUMERIC, KEY_HEIGHT_NUMERIC), BITMAP_NUMPAD_BTN_PRESS_ID},
    { 2, Rect( 83, 210, KEY_WIDTH_NUMERIC, KEY_HEIGHT_NUMERIC), BITMAP_NUMPAD_BTN_PRESS_ID},
    { 3, Rect(157, 210, KEY_WIDTH_NUMERIC, KEY_HEIGHT_NUMERIC), BITMAP_NUMPAD_BTN_PRESS_ID},
    { 4, Rect(  9, 136, KEY_WIDTH_NUMERIC, KEY_HEIGHT_NUMERIC), BITMAP_NUMPAD_BTN_PRESS_ID},
    { 5, Rect( 83, 136, KEY_WIDTH_NUMERIC, KEY_HEIGHT_NUMERIC), BITMAP_NUMPAD_BTN_PRESS_ID},
    { 6, Rect(157, 136,	KEY_WIDTH_NUMERIC, KEY_HEIGHT_NUMERIC), BITMAP_NUMPAD_BTN_PRESS_ID},
    { 7, Rect(  9,  62, KEY_WIDTH_NUMERIC, KEY_HEIGHT_NUMERIC), BITMAP_NUMPAD_BTN_PRESS_ID},
    { 8, Rect( 83, 	62,	KEY_WIDTH_NUMERIC, KEY_HEIGHT_NUMERIC), BITMAP_NUMPAD_BTN_PRESS_ID},
    { 9, Rect(157, 	62,	KEY_WIDTH_NUMERIC, KEY_HEIGHT_NUMERIC), BITMAP_NUMPAD_BTN_PRESS_ID},
    {10, Rect(  9, 285,	KEY0_WIDTH_NUMERIC, KEY0_HEIGHT_NUMERIC), BITMAP_NUMPAD_BTN21_PRESS_ID},
};

/**
 * Callback areas for the special buttons on the CustomKeyboard.
 */
 static Keyboard::CallbackArea callbackAreasNumeric[2] =
{
    {Rect(230,  62, BACKSPACE_WIDTH_NUMERIC, BACKSPACE_HEIGHT_NUMERIC), 0, BITMAP_NUMPAD_BACKSPACE_PRESS_ID },   // backspace
	{Rect(230, 210, ENTER_WIDTH_NUMERIC, ENTER_HEIGHT_NUMERIC), 0, BITMAP_NUMPAD_ENTER_PRESS_ID },   			 // enter
		};

/**
 * The layout for the CustomKeyboard.
 */
static const Keyboard::Layout layoutNumeric =
{
    BITMAP_NUMPAD_BG_ID,
    keyArrayNumeric,
	10,
    callbackAreasNumeric,
    2,
	Rect(15, 12, 270, 32),
    TypedText(T_ENTEREDTEXT),
#if !defined(USE_BPP) || USE_BPP==16
    0x8888,
#elif USE_BPP==24
	0x1B3C64,
#elif USE_BPP==4
    0xF,
#elif USE_BPP==2
    0x3,
#else
#error Unknown USE_BPP
#endif
    Typography::NUMPAD,
#if !defined(USE_BPP) || USE_BPP==16
	0x1B3C64,
#elif USE_BPP==24
	0x1B3C64,
#endif
};

#endif // NUMPADCONT_KEY_LAYOUT_HPP
