#ifndef COMBOBOXCONT_HPP
#define COMBOBOXCONT_HPP

#include <gui_generated/containers/ComboBoxContBase.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <vector>
#include <touchgfx/Callback.hpp>
#include <gui/containers/ComboBoxItemCont.hpp>

class ComboBoxCont : public ComboBoxContBase
{
public:
    ComboBoxCont();
    virtual ~ComboBoxCont() {}

    virtual void initialize();

    virtual void ddBtnClicked()
    {

    }

    virtual void handleClickEvent(const touchgfx::ClickEvent& evt);

    void setTopLayerContainer(Container* topLayer);

	void addItem(const touchgfx::TypedText& t);
	void setSelectedItem(uint16_t index);
	const touchgfx::Unicode::UnicodeChar* getSelectedItem() const;
	uint16_t getSelectedIndex() const;

	void getTopContainerCoordinates(Drawable* obj, Container* topLayer, int16_t& globalX, int16_t& globalY);

	void setItemChangedCallback(touchgfx::GenericCallback<const ComboBoxCont&, uint16_t>& cb);

protected:
	void dropdownButtonHandler(const touchgfx::AbstractButtonContainer& src);
	void itemSelectedHandler(const ComboBoxItemCont& item);

private:
	touchgfx::Callback<ComboBoxCont, const touchgfx::AbstractButtonContainer&> dropdownCallback;
	touchgfx::Callback<ComboBoxCont, const ComboBoxItemCont&> itemSelectCallback;
	touchgfx::GenericCallback<const ComboBoxCont&, uint16_t>* onItemChanged = nullptr;


	std::vector<ComboBoxItemCont*> itemContainers;
	Container* topLayerContainer;
	bool isDropdownVisible;
	uint16_t maxCount;
	uint16_t currIndex;

	uint16_t list_x0, list_y0;

	const uint16_t maxVisibleItems = 5;
};


#endif // COMBOBOXCONT_HPP
