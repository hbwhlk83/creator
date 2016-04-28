#pragma once

#include "core_global.h"

#include <QHash>
#include "qobject.h"

class QMenu;
class QMenuBar;
class QAction;
class QActionGroup;

class CORE_EXPORT ActionManager : public QObject {
	Q_OBJECT
public:
	typedef QHash<QString, QMenu *> strMenuMap;
	typedef QHash<QString, QMenuBar *> strMenuBarMap;
	typedef QHash<QString, QAction *> strCmdMap;
	typedef QHash<QString, QActionGroup *> strCmdGropMap;

	static ActionManager* instance();
	static void deleteInstance();

	QMenu* createMenu(const QString& name);
	QMenuBar* createMenuBar(const QString& name);

	QAction* createAction(const QString& name,const QIcon &icon, const QString &text, QObject* parent = 0);
	QActionGroup* createActionGroup(const QString& name, QObject* parent = 0);
	QActionGroup* createActionGroup(const QString& name, QAction* act, QObject* parent = 0);
	QActionGroup* createActionGroup(const QString& name, QList<QAction*> acts, QObject* parent = 0);

	QMenu* menu(const QString& name) const;
	QMenuBar* menubar(const QString& name) const;
	QAction* action(const QString& name) const;
	QActionGroup* actiongroup(const QString& name) const;
private:
	ActionManager(QObject* parent = 0);
	~ActionManager();

	strMenuMap mMenus;
	strMenuBarMap mMenubars;
	strCmdMap mActios;
	strCmdGropMap mActionGroups;

	static ActionManager* mInstance;
};

