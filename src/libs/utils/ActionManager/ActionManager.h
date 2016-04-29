#pragma once

#include "../utils_global.h"

#include <QHash>
#include "qobject.h"

class QMenu;
class QMenuBar;
class QAction;
class QActionGroup;

struct Group
{
	Group(QString name) : mName(name) {}
	QString mName;
	QList<QObject *> items; // Action * or Menu * or MenuBar*
};

class UTILS_EXPORT ActionManager : public QObject {
	Q_OBJECT
public:
	typedef QHash<QString, QMenu *> strMenuMap;
	typedef QHash<QString, QMenuBar *> strMenuBarMap;
	typedef QHash<QString, QAction *> strCmdMap;

	static ActionManager* instance();
	static void deleteInstance();

	QMenu* createMenu(const QString& name);
	QMenuBar* createMenuBar(const QString& name);
	QAction* createAction(const QString& name, QObject* parent = 0);
	QAction* createSeparator(const QString& name, QObject* parent = 0);
	void appengGroup(const QString& groupname);
	void insertGroup(const QString& before, const QString& group);
	void addAction(const QAction* act, const QString& groupname);

	QMenu* menu(const QString& name) const;
	QMenuBar* menubar(const QString& name) const;
	QAction* action(const QString& name) const;

private:
	ActionManager(QObject* parent = 0);
	~ActionManager();

	strMenuMap mMenus;
	strMenuBarMap mMenubars;
	strCmdMap mActios;
	QList<Group> mGroups;
		
	static ActionManager* mInstance;
};

