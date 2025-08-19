#ifndef MAINSCREENVIEW_HPP
#define MAINSCREENVIEW_HPP

#include <gui_generated/mainscreen_screen/mainScreenViewBase.hpp>
#include <gui/mainscreen_screen/mainScreenPresenter.hpp>

#include <texts/TextKeysAndLanguages.hpp>
#include <images/BitmapDatabase.hpp>
#include <main_util.h>



class mainScreenView : public mainScreenViewBase
{
public:
    mainScreenView();
    virtual ~mainScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();

    void updateTimeTA(uint8_t h, uint8_t m, uint8_t wd);
    void updateDateTA(uint8_t d, uint8_t m, uint8_t y);
    void print_atemp(int16_t t, uint8_t status, touchgfx::Unicode::UnicodeChar *buf, uint16_t bufSize);
    void print_atemp_short(int16_t t, uint8_t status, touchgfx::Unicode::UnicodeChar *buf, uint16_t bufSize);

    void updateOutput(uint8_t n, uint8_t value, uint8_t mode);


    void updatePAirFlap(uint8_t pos, uint8_t m);
    void updateSAirFlap(uint8_t pos, uint8_t m);

    void updateTS1(int16_t t, uint8_t status);
    void updateTS2(int16_t t, uint8_t status);
    void updateTS3(int16_t t, uint8_t status);
    void updateTS4(int16_t t, uint8_t status);
    void updateTS5(int16_t t, uint8_t status);
    void updateTS6(int16_t t, uint8_t status);
    void updateTS7(int16_t t, uint8_t status);
    void updateTS8(int16_t t, uint8_t status);
    void updateTS9(int16_t t, uint8_t status);

    void updateLS(int16_t v, uint8_t status);
    void updateFlowMeter(uint16_t flow, uint8_t vis);

    void updateAccLevel(uint8_t v);

    void updateEnergy(float accEng, float aPwr);

    void updateInfoMsg(TEXTS id_msg);

    void updateProfileSld(uint16_t minV, uint16_t maxV, uint16_t pos);

    void updateDebug();

    void doorBtn_clicked();
    void soundBtn_clicked();
    void profileSldChangeVal(int value);
    void profileSldChangeConf(int value);

    void doorBtn_setLabelDoor(bool doorL);

    void drawScheme(uint8_t sch);

    void showIcons(uint8_t manIcon, uint8_t errIcon );
    void soundBtn_setState(bool press);

private:
    const touchgfx::BitmapId imgSchemes[SCH_COUNT] = {
    	BITMAP_M_SCH1_ID,
		BITMAP_M_SCH2_ID,
		BITMAP_M_SCH3_ID,
		BITMAP_M_SCH4_ID,
		BITMAP_M_SCH5_ID,
		BITMAP_M_SCH6_ID,
		BITMAP_M_SCH7_ID,
		BITMAP_M_SCH8_ID
    };

protected:

    uint8_t initOK = 0;
    static const uint8_t SEN_OK = 0x01;
    static const uint8_t SEN_SH = 0x02;
    static const uint8_t SEN_OP = 0x04;



};

#endif // MAINSCREENVIEW_HPP
