#pragma once

#include <QMainWindow>

class QMenu;
class QMenuBar;
class QToolBar;
class QStatusBar;
class ActionManager;

class MainWindow : public QMainWindow
{
public:
	MainWindow(QWidget *parent = nullptr, Qt::WindowFlags flags = nullptr);
	~MainWindow();

	bool init();
	void registerDefaultActions();
	void registerDefaultContainers();
private:
	void restoreWindowState();

	//ActionManager
	ActionManager* mActionManager;

	//menubar
	QMenuBar* mainMenuBar;
	QToolBar* mainToolBar;
	QStatusBar* mainStatusBar;
};

