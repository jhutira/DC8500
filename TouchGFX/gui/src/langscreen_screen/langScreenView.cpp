#include <gui/langscreen_screen/langScreenView.hpp>
#include <texts/TextKeysAndLanguages.hpp>


langScreenView::langScreenView()
{

}

void langScreenView::setupScreen()
{
    langScreenViewBase::setupScreen();
}

void langScreenView::tearDownScreen()
{
    langScreenViewBase::tearDownScreen();
}

void langScreenView::svkBtnClicked()
{
	presenter->setLanguageId(SK);
	Texts::setLanguage(SK);
	invalidate();
	application().gotoserviceScreenScreenNoTransition();
}

void langScreenView::engBtnClicked()
{
	presenter->setLanguageId(GB);
	Texts::setLanguage(GB);
	invalidate();
	application().gotoserviceScreenScreenNoTransition();
}

