#include <gui/containers/NumPadCont.hpp>
#include <gui/containers/NumPadCont_Layout.hpp>
#include <gui/containers/NumPadCont_KeyMapping.hpp>
#include <string.h>


static const int NUMPAD_WIDTH_NUMERIC = 310;
static const int NUMPAD_HEIGTH_NUMERIC = 362;
static const int NUMPAD_X_POSITION_NUMERIC = 0 * 12;
static const int NUMPAD_Y_POSITION_NUMERIC = 0 * 315;

NumPadCont::NumPadCont() : keyboard(),
	backspacePressed(this, &NumPadCont::backspacePressedHandler),
	enterPressed(this, &NumPadCont::enterPressedHandler),
    keyPressed(this, &NumPadCont::keyPressedhandler)
{
	//Set the callbacks for the callback areas of the keyboard and set its layout.
	layoutNumeric.callbackAreaArray[0].callback = &backspacePressed;
	layoutNumeric.callbackAreaArray[1].callback = &enterPressed;

	keyboard.setLayout(&layoutNumeric);
	keyboard.setKeyListener(keyPressed);
	keyboard.setPosition(NUMPAD_X_POSITION_NUMERIC, NUMPAD_Y_POSITION_NUMERIC, NUMPAD_WIDTH_NUMERIC, NUMPAD_HEIGTH_NUMERIC);

	keyboard.setTextIndentation();
	memset(buffer, 0, sizeof(buffer));
	keyboard.setBuffer(buffer, BUFFER_SIZE);

	setKeyMappingList();

	add(keyboard);
}


void NumPadCont::initialize()
{
    NumPadContBase::initialize();
}

void NumPadCont::setKeyMappingList()
{
    keyboard.setKeymappingList(&keyMappingListNumeric); // R
    invalidate();
}

void NumPadCont::backspacePressedHandler()
{
    uint16_t pos = keyboard.getBufferPosition();
    if (pos > 0)
    {
        //Delete the previous entry in the buffer and decrement the position.
        // buffer[pos - 1] = 0;
        keyboard.getBuffer()[pos - 1] = 0;
        keyboard.setBufferPosition(pos - 1);
    }
    invalidate();
}

void NumPadCont::enterPressedHandler()
{
	if (enterCallback)
	{
		enterCallback();
	}
    invalidate();
}

void NumPadCont::keyPressedhandler(Unicode::UnicodeChar keyChar)
{
	setKeyMappingList(); // R
    invalidate();
}

void NumPadCont::setTouchable(bool touch)
{
    Container::setTouchable(touch);
    keyboard.setTouchable(touch);
}

void NumPadCont::clearBuffer()
{
    memset(buffer, 0, sizeof(buffer));
    keyboard.setBuffer(buffer, BUFFER_SIZE);

    setKeyMappingList();
}

void NumPadCont::setEnterCallback(std::function<void()> callback)
{
    enterCallback = callback;
}


