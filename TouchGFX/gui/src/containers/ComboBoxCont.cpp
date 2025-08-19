#include <gui/containers/ComboBoxCont.hpp>
#include <gui/containers/ComboBoxItemCont.hpp>
#include <touchgfx/events/ClickEvent.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <images/BitmapDatabase.hpp>
#include <touchgfx/Color.hpp>
#include <gui/common/DefnGui.hpp>

ComboBoxCont::ComboBoxCont() :
	dropdownCallback(this, &ComboBoxCont::dropdownButtonHandler),
    itemSelectCallback(this, &ComboBoxCont::itemSelectedHandler),
	topLayerContainer(nullptr),
    isDropdownVisible(false),
	maxCount(0),
    currIndex(0)

{
	ddBtn.setAction(dropdownCallback);
	listCont.setVisible(false);
	list_x0 = listCont.getX();
	list_y0 = listCont.getY();
}

void ComboBoxCont::initialize()
{
    ComboBoxContBase::initialize();
}

void ComboBoxCont::setTopLayerContainer(Container* topLayer)
{
    topLayerContainer = topLayer;
}

void ComboBoxCont::setItemChangedCallback(touchgfx::GenericCallback<const ComboBoxCont&, uint16_t>& cb)
{
	onItemChanged = &cb;
}

void ComboBoxCont::dropdownButtonHandler(const touchgfx::AbstractButtonContainer& src)
{
	if (!isDropdownVisible && topLayerContainer)
    {
    	int16_t globalX, globalY;

        //getGlobalCoordinates(this, globalX, globalY);
    	getTopContainerCoordinates(this, topLayerContainer, globalX, globalY);
        globalX += list_x0;
        globalY += list_y0;
    	if (listCont.getParent() != topLayerContainer)
    	{
    	    remove(listCont);
    	    topLayerContainer->add(listCont);

    	}
        listCont.setXY(globalX, globalY);
    }
    else if (topLayerContainer)
    {
    	topLayerContainer->remove(listCont);
        topLayerContainer->invalidate();
        add(listCont);
    }

    isDropdownVisible = !isDropdownVisible;
    listCont.setVisible(isDropdownVisible);
    listCont.invalidate();

    ddBtnClicked();
}

void ComboBoxCont::addItem(const touchgfx::TypedText& t)
{
    ComboBoxItemCont* item = new ComboBoxItemCont();
    item->setText(t);
    item->setIndex(maxCount);
    item->setCallback(&itemSelectCallback);

    itemContainers.push_back(item);
    listLayout.add(*item);
    listLayout.invalidate();

    maxCount++;
    uint16_t itemHeight = item->getHeight();
	uint16_t maxHeight = maxVisibleItems * itemHeight;
	uint16_t contentHeight = maxCount * itemHeight;

	if (contentHeight > maxHeight)
	{
		contentHeight = maxHeight;
	}

	listCont.setHeight(contentHeight+2);
	listBorder.setHeight(contentHeight+2);
	listLayout.setHeight(contentHeight);

	listCont.invalidate();
}

void ComboBoxCont::setSelectedItem(uint16_t index)
{
    if (index < itemContainers.size())
    {
        currIndex = index;
        ddBtn.setText(itemContainers[index]->getText());
        ddBtn.invalidate();
    }
}

const touchgfx::Unicode::UnicodeChar* ComboBoxCont::getSelectedItem() const
{
    if (currIndex >= 0 && currIndex < itemContainers.size())
    {
        return itemContainers[currIndex]->getText().getText();
    }
    return nullptr;
}

uint16_t ComboBoxCont::getSelectedIndex() const
{
    return currIndex;
}

void ComboBoxCont::itemSelectedHandler(const ComboBoxItemCont& item)
{
    setSelectedItem(item.getIndex());
    isDropdownVisible = false;
    listCont.setVisible(false);
    listCont.invalidate();

    if (topLayerContainer)
    {
        topLayerContainer->remove(listCont);
        add(listCont);
    }

    if (onItemChanged && onItemChanged->isValid())
	{
		onItemChanged->execute(*this, currIndex);
	}
}

void ComboBoxCont::getTopContainerCoordinates(Drawable* obj, Container* topLayer, int16_t& globalX, int16_t& globalY)
{
    globalX = 0;
    globalY = 0;

    while (obj != topLayer)
    {
        globalX += obj->getX();
        globalY += obj->getY();
        obj = obj->getParent(); 	// We move up the hierarchy
    }
}

void ComboBoxCont::handleClickEvent(const ClickEvent& evt)
{
	if (isDropdownVisible && evt.getType() == ClickEvent::RELEASED)
	{
		int16_t x = evt.getX();
		int16_t y = evt.getY();

		// Check if the click is outside of listCont and ddBtn
		if (!listCont.getAbsoluteRect().intersect(Rect(x, y, 1, 1)) &&
			!ddBtn.getAbsoluteRect().intersect(Rect(x, y, 1, 1)))
		{
			// Hide dropdown
			isDropdownVisible = false;
			listCont.setVisible(false);
			listCont.invalidate();

			if (topLayerContainer)
			{
				topLayerContainer->remove(listCont);	topLayerContainer->setTouchable(true);
				topLayerContainer->invalidate();
				add(listCont);
				listCont.setXY(list_x0, list_y0);
			}
		}
	}

	Container::handleClickEvent(evt);
}


