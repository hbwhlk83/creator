
#include "plugin.h"
#include "pluginManager.h"


IPlugin::IPlugin() {}
IPlugin::~IPlugin() {}

void IPlugin::addObject(QObject* obj) {
	PluginManager::instance()->addObject(obj);
}

void IPlugin::removeObject(QObject* obj) {
	PluginManager::instance()->removeObject(obj);
}