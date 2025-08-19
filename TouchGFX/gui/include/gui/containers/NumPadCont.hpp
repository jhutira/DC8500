#ifndef NUMPADCONT_HPP
#define NUMPADCONT_HPP

#include <gui_generated/containers/NumPadContBase.hpp>
#include <touchgfx/widgets/Keyboard.hpp>
#include <functional>


class NumPadCont : public NumPadContBase
{
public:
    NumPadCont();
    virtual ~NumPadCont() {}

    virtual void initialize();

    /*
     * Override setTouchable to also affect the keyboard object inside this
     * CustomKeyboard.
     */
    void setTouchable(bool touch);

    //  void setKeyboardDoneReturnPressedAction(GenericCallback<Unicode::UnicodeChar[]>& callback);

    void clearBuffer();

    void setEnterCallback(std::function<void()> callback);

    Keyboard keyboard;

private:

    /**
     * The size of the buffer that is used by the keyboard.
     * The size determines how much text the keyboard can contain in its textfield.
     */
    static const uint8_t BUFFER_SIZE = 14;

    /**
     * The buffer used by the keyboard for text input.
     */
    Unicode::UnicodeChar buffer[BUFFER_SIZE];

    /**
     * Callback for the backspace button.
     */
    Callback<NumPadCont> backspacePressed;

    /**
     * Callback for the backspace button.
     */
    Callback<NumPadCont> enterPressed;

    /**
     * Callback for when keys are pressed on the keyboard.
     */
    Callback<NumPadCont, Unicode::UnicodeChar> keyPressed;

    /*
     * Sets the correct key mappings of the keyboard according to alpha/numeric and upper-case/lower-case.
     */
    void setKeyMappingList();

    /**
     * Callback handler for the backspace button.
     */
    void backspacePressedHandler();

    /**
     * Callback handler for the enter button.
     */
    void enterPressedHandler();

    /**
     * Callback handler for key presses.
     * @param keyChar The UnicodeChar for the key that was pressed.
     */
    void keyPressedhandler(Unicode::UnicodeChar keyChar);

    GenericCallback < Unicode::UnicodeChar[] > * doneReturnCallback;

    // Saving extern callback function for Enter
    std::function<void()> enterCallback;

protected:
};

#endif // NUMPADCONT_HPP
