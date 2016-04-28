#ifndef PLUGIN_GLOBAL_H
#define PLUGIN_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef PLUGIN_LIB
# define PLUGIN_EXPORT Q_DECL_EXPORT
#else
# define PLUGIN_EXPORT Q_DECL_IMPORT
#endif

#endif // PLUGIN_GLOBAL_H
