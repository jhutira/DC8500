#ifndef NUMPADCONT_KEY_MAPPING_HPP
#define NUMPADCONT_KEY_MAPPING_HPP

#include <touchgfx/widgets/Keyboard.hpp>
using namespace touchgfx;

/**
 * This file contains all the keymappings for the CustomKeyboard.
 */

static const Keyboard::KeyMapping keyMappingsNumeric[10] =
{
    { 1,  49},  // 1
    { 2,  50},  // 2
    { 3,  51},  // 3
    { 4,  52},  // 4
    { 5,  53},  // 5
    { 6,  54},  // 6
    { 7,  55},  // 7
    { 8,  56},  // 8
    { 9,  57},  // 9
    {10,  48},  // 0
};

static const Keyboard::KeyMappingList keyMappingListNumeric =
{
    keyMappingsNumeric,
	10
};


#endif // NUMPADCONT_KEY_MAPPING_HPP
