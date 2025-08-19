#ifndef COMBOBOXITEMCONT_HPP
#define COMBOBOXITEMCONT_HPP

#include <gui_generated/containers/ComboBoxItemContBase.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/Callback.hpp>

class ComboBoxItemCont : public ComboBoxItemContBase
{
public:
    ComboBoxItemCont();
    virtual ~ComboBoxItemCont() {}

    virtual void initialize();

    void setText(const touchgfx::TypedText& t);
    void setIcon(touchgfx::BitmapId bmpId);
    void setIndex(uint16_t i);
    uint16_t getIndex() const;
    const touchgfx::TypedText& getText() const;

    void setCallback(touchgfx::GenericCallback<const ComboBoxItemCont&>* cb);

    touchgfx::Button* getButton() { return &itemBtn; }

protected:
    touchgfx::Callback<ComboBoxItemCont, const touchgfx::AbstractButton&> itemSelectedCallback;

    void itemSelectedHandler(const touchgfx::AbstractButton& src);

    touchgfx::GenericCallback<const ComboBoxItemCont&>* callback;

    //touchgfx::Callback<ComboBoxItemCont, const touchgfx::AbstractButton&> itemSelectedCallback;

    uint16_t index;

};

#endif // COMBOBOXITEMCONT_HPP
