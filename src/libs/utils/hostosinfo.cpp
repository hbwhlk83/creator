
#include "hostosinfo.h"

using namespace Utils;

HostOsInfo::OsType HostOsInfo::hostOs() {

#if defined(Q_OS_WIN)
	return OsTypeWindows;
#elif defined(Q_OS_MAC)
	return OsTypeMac;
#elif defined(Q_OS_LINUX)
	return OsTypeLinux;
#elif defined(Q_OS_UNIX)
	return OsTypeOtherUnix;
#else 
	return OsTypeOther;
#endif
}