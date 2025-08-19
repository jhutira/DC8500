#ifndef MANUALSCREENVIEW_HPP
#define MANUALSCREENVIEW_HPP

#include <gui_generated/manualscreen_screen/manualScreenViewBase.hpp>
#include <gui/manualscreen_screen/manualScreenPresenter.hpp>

class manualScreenView : public manualScreenViewBase
{
public:
	#define bAUTO 2
	#define bON  1
	#define bOFF 0

	manualScreenView();
    virtual ~manualScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void initOutput(uint8_t n, uint8_t mode);


    void initPFlap(uint8_t man, uint8_t pos);
    void initSFlap(uint8_t man, uint8_t pos);

    void pfUpBtn_clicked();
	void pfDownBtn_clicked();
	void pfAutoBtn_clicked();

	void sfUpBtn_clicked();
	void sfDownBtn_clicked();
	void sfAutoBtn_clicked();

	void rbOnP1_clicked();
	void rbOffP1_clicked();
	void rbAutoP1_clicked();

	void rbOnP2_clicked();
	void rbOffP2_clicked();
	void rbAutoP2_clicked();

	void rbOnY1_clicked();
	void rbOffY1_clicked();
	void rbAutoY1_clicked();

	void rbOnY2_clicked();
	void rbOffY2_clicked();
	void rbAutoY2_clicked();

	void rbOnY3_clicked();
	void rbOffY3_clicked();
	void rbAutoY3_clicked();

	uint8_t pf_man;
	uint8_t pf_pos;
	uint8_t sf_man;
	uint8_t sf_pos;
	uint8_t p1_mode;
	uint8_t p2_mode;
	uint8_t y1_mode;
	uint8_t y2_mode;
	uint8_t y3_mode;


protected:
};

#endif // MANUALSCREENVIEW_HPP
