#ifndef DRIVER_FACTORY
#define DRIVER_FACTORY

#include <openvr_driver.h>
#include <cstring>
#include <include/DeviceProvider.hpp>

#if defined(__GNUC__) || defined(COMPILER_GCC) || defined(__APPLE__)
#define HMD_DLL_EXPORT extern "C" __attribute__((visibility("default")))
#define HMD_DLL_IMPORT extern "C"
#else
#error "Unsupported Platform."
#endif

//VRDriver deviceProvider;
HMD_DLL_EXPORT void* HmdDriverFactory(const char* pInterfaceName, int* pReturnCode);

#endif /* DriverFactory.hpp */