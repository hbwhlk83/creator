
#include "MainWindow.h"
#include "coreplugin.h"

coreplugin::coreplugin():
mMainWindow(0) {

}

coreplugin::~coreplugin(){
	if (mMainWindow != 0) {
		delete mMainWindow;
		mMainWindow = 0;
	}
}

bool coreplugin::initialize() {
	mMainWindow = new MainWindow;
	mMainWindow->init();
	mMainWindow->show();
	return true;
}
