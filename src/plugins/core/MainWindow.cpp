

#include <QTimer>
#include <QMenu>
#include <QMenuBar>

#include "ActionManager.h"
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

	QMenu* menu = mActionManager->createMenu(CoreConstants::M_FILE);
	menu->setTitle("&File");
	mainMenuBar->addMenu(menu);

	QMenu* submenu = mActionManager->createMenu(CoreConstants::G_FILE_NEW);
	submenu->setTitle("&New");
	menu->addMenu(submenu);

	submenu = mActionManager->createMenu(CoreConstants::G_FILE_OPEN);
	submenu->setTitle("&Open");
	menu->addMenu(submenu);

	submenu = mActionManager->createMenu(CoreConstants::G_FILE_SAVE);
	submenu->setTitle("&Save");
	menu->addMenu(submenu);

	submenu = mActionManager->createMenu(CoreConstants::G_FILE_OTHER);
	submenu->setTitle("&Other");
	menu->addMenu(submenu);

	submenu = mActionManager->createMenu(CoreConstants::G_FILE_CLOSE);
	submenu->setTitle("&Close");
	menu->addMenu(submenu);

	menu = mActionManager->createMenu(CoreConstants::M_EDIT);
	menu->setTitle("&Edit");
	mainMenuBar->addMenu(menu);

	menu = mActionManager->createMenu(CoreConstants::M_TOOLS);
	menu->setTitle("&Tool");
	mainMenuBar->addMenu(menu);

	menu = mActionManager->createMenu(CoreConstants::M_HELP);
	menu->setTitle("&Help");
	mainMenuBar->addMenu(menu);
}
