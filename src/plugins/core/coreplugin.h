#ifndef COREPLUGIN_H
#define COREPLUGIN_H

#include <QObject>
#include "core_global.h"
#include "Plugin/plugin.h"


class MainWindow;

class CORE_EXPORT coreplugin : public IPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.adesk.LwpCreotrPlugin" FILE "plugin.json")
public:
	coreplugin();
	~coreplugin();

	bool initialize() override;


private:
	MainWindow* mMainWindow;
};

#endif // COREPLUGIN_H
