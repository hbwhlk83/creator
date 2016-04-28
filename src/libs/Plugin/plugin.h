#ifndef PLUGIN_H
#define PLUGIN_H

#include "plugin_global.h"

#include <QObject>

class PluginDesc;

class PLUGIN_EXPORT IPlugin : public QObject
{
	Q_OBJECT

public:
	IPlugin();
	virtual ~IPlugin();

	virtual bool initialize() = 0;

	PluginDesc* pluginDesc() const { return m_pluginDesc; }

	void addObject(QObject* obj);
	void removeObject(QObject* obj);
private:
	PluginDesc* m_pluginDesc;
};

#endif // PLUGIN_H
