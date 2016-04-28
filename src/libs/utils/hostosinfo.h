
#ifndef HOSTOSINFO_H
#define HOSTOSINFO_H

#include "utils_global.h"

namespace Utils {

// Add more as needed.


class UTILS_EXPORT HostOsInfo {

public:
	

	enum OsType { OsTypeWindows, OsTypeLinux, OsTypeMac, OsTypeOtherUnix, OsTypeOther };

	enum HostArchitecture {
		HostArchitectureX86, 
		HostArchitectureAMD64, 
		HostArchitectureItanium,
		HostArchitectureArm, 
		HostArchitectureUnknown
	};

	static OsType hostOs();
	static bool isWindowsHost() { return hostOs() == OsType::OsTypeWindows; }
	static bool isMacHost() { return hostOs() == OsType::OsTypeMac; }
	static bool isLinuxHost() { return hostOs() == OsType::OsTypeLinux; }
};

} // namespace Utils

#endif //HOSTOSINFO_H
