#ifndef TIMESCREENVIEW_HPP
#define TIMESCREENVIEW_HPP

#include <gui_generated/timescreen_screen/timeScreenViewBase.hpp>
#include <gui/timescreen_screen/timeScreenPresenter.hpp>

class timeScreenView : public timeScreenViewBase
{
public:
    timeScreenView();
    virtual ~timeScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void initTimeTA(uint8_t h, uint8_t m);

    void updateTimeTA();

    void hUpBtn_clicked();
    void hDownBtn_clicked();
    void mUpBtn_clicked();
    void mDownBtn_clicked();
    void okBtn_clicked();

protected:

private:
    uint8_t hour;
    uint8_t minute;
};

#endif // TIMESCREENVIEW_HPP
