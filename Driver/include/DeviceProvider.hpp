#ifndef DEVICE_PROVIDER
#define DEVICE_PROVIDER

#include <ControllerDriver.hpp>
#include <openvr_driver.h>
using namespace vr;

class DeviceProvider : public IServerTrackedDeviceProvider
{
    public:
        EVRInitError Init(IVRDriverContext* pDriverContext);
        void Cleanup();
        const char* const* GetInterfaceVersions();
        void RunFrame();
        bool ShouldBlockStandbyMode();
        void EnterStandby();
        void LeaveStandby();
    private:
        ControllerDriver* controllerDriver;
};

#endif /* DeviceProvider.hpp */