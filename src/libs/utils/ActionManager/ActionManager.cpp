

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

QAction* ActionManager::createAction(const QString& name, QObject* parent/* = 0*/) {
	QAction* act = 0;
	act = action(name);
	if (act == 0) {
		act = new QAction(parent);
		mActios.insert(name, act);
	}
	return act;
}

QAction* ActionManager::createSeparator(const QString& name, QObject* parent /*= 0*/) {
	QAction* act = createAction(name, parent);
	if (act != 0)
		act->setSeparator(true);
	return act;
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

void ActionManager::appengGroup(const QString& groupname) {
	mGroups.append(Group(groupname));
}

void ActionManager::insertGroup(const QString& before, const QString& group) {
	QList<Group>::iterator it = mGroups.begin();
	while (it != mGroups.end()) {
		if (it->mName == before) {
			mGroups.insert(it, Group(group));
			break;
		}
		++it;
	}
}

void ActionManager::addAction(const QAction* act, const QString& groupname) {
	if (!act || groupname.isEmpty()) {
		return;
	}


}







