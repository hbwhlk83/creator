

#include <QDir>
#include <QFileInfo>
#include <QJsonArray>
#include <QDebug>
#include "plugin.h"
#include "PluginManager.h"
#include "PluginDesc.h"


namespace {
	const char PLUGIN_METADATA[] = "MetaData";
	const char PLUGIN_NAME[] = "Name";
	const char PLUGIN_VERSION[] = "Version";
	const char PLUGIN_ENABLE_BY_DEFAULT[] = "DefaultEnable";
}


PluginDesc::PluginDesc() :
	mEnabledByDefault(true),
	mPlugin(0){
}


PluginDesc::~PluginDesc(){
}

bool PluginDesc::read(const QString &fileName) {
	mName = mVersion = mLocation = QString();
	QFileInfo fileInfo(fileName);
	mLocation = fileInfo.absolutePath();
	mFilePath = fileInfo.absoluteFilePath();
	loader.setFileName(mFilePath);
	if (loader.fileName().isEmpty()) {
		return false;
	}

	if (!readMetaData(loader.metaData()))
		return false;

	return true;
}

QRegExp &PluginDesc::versionRegExp() {
	static QRegExp reg(QLatin1String("([0-9]+)(?:[.]([0-9]+))?(?:[.]([0-9]+))?(?:_([0-9]+))?"));
	return reg;
}

bool PluginDesc::isValidVersion(const QString &version) {
	return versionRegExp().exactMatch(version);
}

bool PluginDesc::readMetaData(const QJsonObject &metaData) {
	QJsonValue value;
	value = metaData.value(QLatin1String("IID"));
	if (!value.isString()) {
		return false;
	}
	if (value.toString() != PluginManager::pluginIID()) {
		qWarning() << "Plugin ignored (IID does not match)";
		return false;
	}

	value = metaData.value(QLatin1String(PLUGIN_METADATA));
	if (!value.isObject()) {
		qWarning() << "Plugin meta data not found";
		return false;
}
	QJsonObject pluginInfo = value.toObject();

	value = pluginInfo.value(QLatin1String(PLUGIN_NAME));
	if (value.isUndefined()) {
		qWarning() << "Plugin Name Undefined";
		return false;
	}
	if (!value.isString()) {
		qWarning() << "Plugin Name value is't String";
		return false;
	}
	mName = value.toString();

	value = pluginInfo.value(QLatin1String(PLUGIN_VERSION));
	if (value.isUndefined()) {
		qWarning() << "Plugin Version Undefined";
		return false;
	}
	if (!value.isString()) {
		qWarning() << "Plugin Version value is't String";
		return false;
	}
	mVersion = value.toString();
	if (!isValidVersion(mVersion)) {
		qWarning() << "Plugin Version is't Valid";
		return false;
	}

	value = pluginInfo.value(QLatin1String(PLUGIN_ENABLE_BY_DEFAULT));
	if (!value.isUndefined() && !value.isBool()) {
		qWarning() << "Plugin Enable Undefined or is't Bool";
		return false;
	}
	mEnabledByDefault = value.toBool(true);

	return true;
}

void PluginDesc::setEabledByDefault(bool value) {
	mEnabledByDefault = value;
}

bool PluginDesc::loadPlugin() {
	if (!loader.load()) {
		qWarning() << "Error:" << QDir::toNativeSeparators(mFilePath) + QString::fromLatin1(": ") + loader.errorString();
		return false;
	}
	
	IPlugin* pluginObj = NULL;
	if (mEnabledByDefault) 
		pluginObj = qobject_cast<IPlugin*>(loader.instance());

	if (!pluginObj) {
		qWarning() << "Error:" << QDir::toNativeSeparators(mFilePath) + QString::fromLatin1(": ") + "Plugin is not valid (does not derive from IPlugin)";
		loader.unload();
		return false;
	}
	mPlugin = pluginObj;

	mPlugin->initialize();

	return true;
}

bool PluginDesc::unloadPlugin() {
	return loader.unload();
}
