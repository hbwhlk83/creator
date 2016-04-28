#pragma once

#include "plugin_global.h"
#include <QObject>
#include <QWriteLocker>

class PluginDesc;

class PLUGIN_EXPORT PluginManager : public QObject {
	Q_OBJECT

public:
	static PluginManager* instance();
	static void deleteInstance();

	// Object pool operations
	void addObject(QObject *obj);
	void removeObject(QObject *obj);
	QList<QObject *> allObjects();
    QReadWriteLock *listLock();
	template <typename T> static QList<T *> getObjects() {
		QReadLocker lock(m_lock);
		QList<T *> results;
		foreach(QObject *obj, m_Objects) {
			T *result = qobject_cast<T *>(obj);
			if (result)
				results += result;
		}
		return results;
	}
	template <typename T, typename Predicate>
	static QList<T *> getObjects(Predicate predicate) {
		QReadLocker lock(m_lock);
		QList<T *> results;
		foreach(QObject *obj, m_Objects) {
			T *result = qobject_cast<T *>(obj);
			if (result && predicate(result))
				results += result;
		}
		return results;
	}
	template <typename T> static T *getObject()	{
		QReadLocker lock(m_lock);
		foreach(QObject *obj, m_Objects) {
			if (T *result = qobject_cast<T *>(obj))
				return result;
		}
		return 0;
	}
	template <typename T, typename Predicate> static T *getObject(Predicate predicate) {
		QReadLocker lock(m_lock);
		QList<QObject *> all = allObjects();
		foreach(QObject *obj, all) {
			if (T *result = qobject_cast<T *>(obj))
				if (predicate(result))
					return result;
		}
		return 0;
	}

	QStringList getPluginPaths() const;
	void setPluginPaths(const QStringList pluginPaths);

	void readPluginPaths();

	void loadPlugins();

	QObject *getObjectByName(const QString &name);
	QObject *getObjectByClassName(const QString &className);

	PluginDesc *pluginByName(const QString &name) const;

	static QString pluginIID() { return mInstance->mPluginIID; }
	void setPuginIID(const QString& pluginIID);


private:
	PluginManager();
	~PluginManager();

	mutable QReadWriteLock mLock;

	QString mPluginIID;
	QObjectList mObjects;
	QList<PluginDesc*> mPlugins;

	QStringList mPluginPaths;

	static PluginManager* mInstance;
};

