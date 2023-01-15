#include <include/DriverFactory.hpp>

DeviceProvider deviceProvider;

HMD_DLL_EXPORT
void* HmdDriverFactory(const char* pInterfaceName, int* pReturnCode)
{
    if (0 == strcmp(pInterfaceName, IServerTrackedDeviceProvider_Version) == 0)
    {
        return &deviceProvider;
    }

    if(pReturnCode)
    {
        *pReturnCode = vr::VRInitError_Init_InterfaceNotFound;
    }

    return NULL;
}