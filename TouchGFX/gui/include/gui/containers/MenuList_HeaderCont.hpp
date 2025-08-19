#ifndef MENULIST_HEADERCONT_HPP
#define MENULIST_HEADERCONT_HPP

#include <gui_generated/containers/MenuList_HeaderContBase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

class MenuList_HeaderCont : public MenuList_HeaderContBase
{
public:
    MenuList_HeaderCont();
    virtual ~MenuList_HeaderCont() {}

    virtual void initialize();

    /**
      * Initialize this containers widgets
      */
     void setupListItem(TEXTS nameTextID);
protected:
};

#endif // MENULIST_HEADERCONT_HPP
