#ifndef DEFGUI_HPP
#define DEFGUI_HPP

const char DegCel[] = { 0xB0, 'C', 0 };
const touchgfx::Unicode::UnicodeChar uDegCel[] = { 0xB0, 'C', 0 };

const touchgfx::Unicode::UnicodeChar SERVICE_PASSWORD[] = { '0', '0', '9', '9', 0 };
const touchgfx::Unicode::UnicodeChar EXSERVICE_PASSWORD[] = { '0', '0', '2', '3', 0 };

const touchgfx::Unicode::UnicodeChar EMPTY_STRING[1] = {0};

enum class eTypeValue : uint8_t {
    tUInt = 0,
    tUInt_1Dec = 1
};


#endif // DEFGUI_HPP
