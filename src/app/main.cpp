
#include <QDir>
#include <QStandardPaths>
#include <QtWidgets/QApplication>
#include "utils/hostosinfo.h"
#include "CommandLineParser.h"
#include "LanguageManager.h"
#include "Plugin/PluginManager.h"


static inline QStringList getPluginPaths()
{
	QStringList rc;
	// Figure out root:  Up one from 'bin'
	QDir rootDir = QApplication::applicationDirPath();
	rootDir.cdUp();
	const QString rootDirPath = rootDir.canonicalPath();
	QString pluginPath;
	if (Utils::HostOsInfo::isMacHost()) {
		// 1) "PlugIns" (OS X)
		pluginPath = rootDirPath + QLatin1String("/PlugIns");
		rc.push_back(pluginPath);
	}
	else {
		// 2) "plugins" (Win/Linux)
		pluginPath = rootDirPath;
		pluginPath += QLatin1String("/Debug");
		rc.push_back(pluginPath);
	}

	return rc;
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	CommandLineParser cmdparser;
	if (!cmdparser.parse(app.arguments())) {
		return 0;
	}

	LanguageManager* lagMag = LanguageManager::getInstance();
	if (lagMag != NULL) {
		lagMag->installTranslators();
	}

	PluginManager* pluginMag = PluginManager::instance();
	pluginMag->setPuginIID("org.adesk.LwpCreotrPlugin");

	pluginMag->setPluginPaths(getPluginPaths());
	pluginMag->loadPlugins();
	return app.exec();
}
