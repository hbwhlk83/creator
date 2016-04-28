#pragma once

#include "plugin_global.h"

#include <QPluginLoader>

class IPlugin;

class PLUGIN_EXPORT PluginDesc
{
public:
	PluginDesc();
	~PluginDesc();

	bool read(const QString &fileName);

	QString name() const { return mName; }
	QString version() const { return mVersion; }
	bool isEnabledByDefault() const { return mEnabledByDefault; }

	void setEabledByDefault(bool value);

	QString location() const { return mLocation; }
	QString filePath() const { return mFilePath; }
	QStringList arguments() const { return mArguments; }
	IPlugin* plugin() const { return mPlugin; }

	bool loadPlugin();

protected:
	bool readMetaData(const QJsonObject &metaData);
	QRegExp& versionRegExp();
	bool isValidVersion(const QString &version);

private:
	QPluginLoader loader;

	QString mName;
	QString mVersion;

	bool mEnabledByDefault;

	QString mLocation;
	QString mFilePath;
	QStringList mArguments;

	IPlugin* mPlugin;

};

