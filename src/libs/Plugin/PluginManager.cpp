

#include <QDir>
#include <QDebug>
#include "PluginDesc.h"
#include "PluginManager.h"

PluginManager* PluginManager::mInstance = 0;

static bool lessThanByPluginName(const PluginDesc *one, const PluginDesc *two)
{
	return one->name() < two->name();
}

PluginManager::PluginManager(){
}


PluginManager::~PluginManager(){
}


PluginManager* PluginManager::instance() {
	if (mInstance == 0) {
		mInstance = new PluginManager();
	}

	return mInstance;
}


void PluginManager::setPuginIID(const QString& pluginIID) {
	mPluginIID = pluginIID;
}

void PluginManager::addObject(QObject *obj) {
	{
		QWriteLocker lock(&mLock);
		if (obj == 0) {
			qWarning() << "PluginManagerPrivate::addObject(): trying to add null object";
			return;
		}
		if (mObjects.contains(obj)) {
			qWarning() << "PluginManagerPrivate::addObject(): trying to add duplicate object";
			return;
		}

		mObjects.append(obj);
	}
}

void PluginManager::removeObject(QObject *obj)
{
	if (obj == 0) {
		qWarning() << "PluginManagerPrivate::removeObject(): trying to remove null object";
		return;
	}

	if (!mObjects.contains(obj)) {
		qWarning() << "PluginManagerPrivate::removeObject(): object not in list:"
			<< obj << obj->objectName();
		return;
	}

	QWriteLocker lock(&mLock);
	mObjects.removeAll(obj);
}

QList<QObject *> PluginManager::allObjects() {
	return mObjects;
}

QReadWriteLock * PluginManager::listLock() {
	return &mLock;
}

QObject * PluginManager::getObjectByName(const QString &name) {
	QReadLocker lock(&mLock);
	foreach(QObject *obj, mObjects) {
		if (obj->objectName() == name)
			return obj;
	}

	return 0;
}

QObject * PluginManager::getObjectByClassName(const QString &className) {
	const QByteArray ba = className.toUtf8();
	QReadLocker lock(&mLock);
	foreach(QObject *obj, mObjects) {
		if (obj->inherits(ba.constData()))
			return obj;
	}
	return 0;
}

PluginDesc * PluginManager::pluginByName(const QString &name) const {
	foreach(PluginDesc *obj, mPlugins) {
		if (obj->name() == name) {
			return obj;
		}
	}
	return 0;
}

QStringList PluginManager::getPluginPaths() const {
	return mPluginPaths;
}

void PluginManager::setPluginPaths(const QStringList pluginPaths) {
	mPluginPaths = pluginPaths;
	readPluginPaths();
}

void PluginManager::readPluginPaths() {
	QStringList pluginFiles;
	QStringList searchPaths = mPluginPaths;
	while (!searchPaths.isEmpty()) {
		const QDir dir(searchPaths.takeFirst());
		const QFileInfoList files = dir.entryInfoList(QDir::Files | QDir::NoSymLinks);
		foreach(const QFileInfo &file, files) {
			const QString filePath = file.absoluteFilePath();
			if (QLibrary::isLibrary(filePath))
				pluginFiles.append(filePath);
		}
		const QFileInfoList dirs = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
		foreach(const QFileInfo &subdir, dirs)
			searchPaths << subdir.absoluteFilePath();
	}

	foreach(const QString &pluginFile, pluginFiles) {
		PluginDesc *spec = new PluginDesc;
		if (!spec->read(pluginFile)) { // not a Qt Creator plugin
			delete spec;
			continue;
		}

		mPlugins.append(spec);
	}

	qSort(mPlugins.begin(), mPlugins.end(), lessThanByPluginName);
}

void PluginManager::loadPlugins() {
	foreach(PluginDesc* var, mPlugins) {
		var->loadPlugin();
	}
}

void PluginManager::deleteInstance() {
	if (mInstance != 0) {
		delete mInstance;
		mInstance = 0;
	}
}

void PluginManager::loadPlugin(const QString& plugin) {
	PluginDesc* spec = new PluginDesc;
	if (!spec->read(plugin)) {
		delete spec;
	}
	mPlugins.append(spec);
	spec->loadPlugin();
}

void PluginManager::unloadPlugin(const QString& name) {
	PluginDesc* spec = pluginByName(name);
	if (spec != 0) {
		spec->unloadPlugin();
	}
}





