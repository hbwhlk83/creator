

#include <QTimer>
#include <QMenu>
#include <QMenuBar>

#include "utils/ActionManager/ActionManager.h"
#include "coreconstans.h"
#include "MainWindow.h"


MainWindow::MainWindow(QWidget *parent/* = nullptr*/, Qt::WindowFlags flags/* = nullptr*/) :
	QMainWindow(parent, flags),
	mainMenuBar(0),
	mainToolBar(0),
	mainStatusBar(0),
	mActionManager(0) {
	
	mActionManager = ActionManager::instance();
}

MainWindow::~MainWindow(){
}

bool MainWindow::init() {
	this->setWindowTitle("LwpCreator");

	registerDefaultContainers();
	//registerDefaultActions();

	QTimer::singleShot(10, this, &MainWindow::restoreWindowState);
	return true;
}

void MainWindow::restoreWindowState(){
	resize(1008, 700);
	show();
}

void MainWindow::registerDefaultContainers() {
	mainMenuBar = mActionManager->createMenuBar(CoreConstants::MENU_BAR);
	setMenuBar(mainMenuBar);
}
