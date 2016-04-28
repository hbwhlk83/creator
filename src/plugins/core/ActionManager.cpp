

#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QActionGroup>
#include "ActionManager.h"


ActionManager* ActionManager::mInstance = nullptr;

ActionManager* ActionManager::instance() {
	if (mInstance == nullptr) {
		mInstance = new ActionManager();
	}

	return mInstance;
}


void ActionManager::deleteInstance() {
	if (mInstance != nullptr) {
		delete mInstance;
		mInstance = nullptr;
	}
}

ActionManager::ActionManager(QObject* parent /*= nullptr*/) :
	QObject(parent) {

}

ActionManager::~ActionManager() {

}

QMenu* ActionManager::createMenu(const QString& name) {
	QMenu* meu = 0;
	meu = menu(name);
	if (meu == 0) {
		meu = new QMenu;
		mMenus.insert(name, meu);
	}
	return meu;
}

QMenuBar* ActionManager::createMenuBar(const QString& name) {
	QMenuBar* meubar = 0;
	meubar = menubar(name);
	if (meubar == 0) {
		meubar = new QMenuBar;
		mMenubars.insert(name, meubar);
	}
	return meubar;
}

QAction* ActionManager::createAction(const QString& name, const QIcon &icon, const QString &text, QObject* parent/* = 0*/) {
	QAction* act = 0;
	act = action(name);
	if (act == 0) {
		act = new QAction(icon, text, parent);
		mActios.insert(name, act);
	}
	return act;
}

QActionGroup* ActionManager::createActionGroup(const QString& name, QObject* parent/* = 0*/) {
	QActionGroup* actgp = 0;
	actgp = actiongroup(name);
	if (actgp == 0) {
		actgp = new QActionGroup(parent);
		mActionGroups.insert(name, actgp);
	}
	return actgp;
}

QActionGroup* ActionManager::createActionGroup(const QString& name, QAction* act, QObject* parent /*= 0*/) {
	QActionGroup* actgp = createActionGroup(name, parent);
	actgp->addAction(act);
	return actgp;
}

QActionGroup* ActionManager::createActionGroup(const QString& name, QList<QAction*> acts, QObject* parent /*= 0*/) {
	QActionGroup* actgp = createActionGroup(name, parent);
	foreach(QAction* act, acts)	{
		actgp->addAction(act);
	}
	return actgp;
}

QMenu* ActionManager::menu(const QString& name) const {
	const strMenuMap::const_iterator iter = mMenus.constFind(name);
	if (iter != mMenus.constEnd()) {
		return iter.value();
	}
	return 0;
}

QMenuBar* ActionManager::menubar(const QString& name) const {
	const strMenuBarMap::const_iterator iter = mMenubars.constFind(name);
	if (iter != mMenubars.constEnd()) {
		return iter.value();
	}
	return 0;
}

QAction* ActionManager::action(const QString& name) const {
	const strCmdMap::const_iterator iter = mActios.constFind(name);
	if (iter != mActios.constEnd()) {
		return iter.value();
	}
	return 0;
}

QActionGroup* ActionManager::actiongroup(const QString& name) const {
	const strCmdGropMap::const_iterator iter = mActionGroups.constFind(name);
	if (iter != mActionGroups.constEnd()) {
		return iter.value();
	}
	return 0;
}




