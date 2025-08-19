#ifndef DATESCREENVIEW_HPP
#define DATESCREENVIEW_HPP

#include <gui_generated/datescreen_screen/dateScreenViewBase.hpp>
#include <gui/datescreen_screen/dateScreenPresenter.hpp>

class dateScreenView : public dateScreenViewBase
{
public:
    dateScreenView();
    virtual ~dateScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void initDateTA(uint8_t d, uint8_t m, uint8_t y);
    void updateDateTA();

    void dUpBtn_clicked();
    void dDownBtn_clicked();
    void mUpBtn_clicked();
    void mDownBtn_clicked();
    void yUpBtn_clicked();
    void yDownBtn_();
    void okBtn_clicked();

protected:

private:
    uint8_t date;
    uint8_t month;
    uint8_t year;
};

#endif // DATESCREENVIEW_HPP
