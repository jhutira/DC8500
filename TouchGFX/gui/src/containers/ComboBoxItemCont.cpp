#include <gui/containers/ComboBoxItemCont.hpp>

ComboBoxItemCont::ComboBoxItemCont() :
	itemSelectedCallback(this, &ComboBoxItemCont::itemSelectedHandler),
    callback(nullptr),
	index(0)
{
    itemBtn.setAction(itemSelectedCallback);
}

void ComboBoxItemCont::initialize()
{
    ComboBoxItemContBase::initialize();
}

void ComboBoxItemCont::setText(const touchgfx::TypedText& t)
{
    itemText.setTypedText(t);
    itemText.invalidate();
}

void ComboBoxItemCont::setIcon(touchgfx::BitmapId bmpId)
{
    //itemIcon.setBitmap(touchgfx::Bitmap(bmpId));
    //itemIcon.invalidate();
}

void ComboBoxItemCont::setIndex(uint16_t i)
{
    index = i;
}

uint16_t ComboBoxItemCont::getIndex() const
{
    return index;
}

const touchgfx::TypedText& ComboBoxItemCont::getText() const
{
    return itemText.getTypedText();
}



void ComboBoxItemCont::setCallback(touchgfx::GenericCallback<const ComboBoxItemCont&>* cb)
{
    callback = cb;
}


void ComboBoxItemCont::itemSelectedHandler(const touchgfx::AbstractButton& src)
{
	if (callback && callback->isValid())
    {
        callback->execute(*this);
    }
}

