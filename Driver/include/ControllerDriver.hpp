#ifndef CONTROLLER_DEVICE
#define CONTROLLER_DEVICE

#include <openvr_driver.h>

using namespace vr;

class ControllerDriver : public ITrackedDeviceServerDriver
{
    public:
        EVRInitError Activate(uint32_t unObjectId);
        
        void Deactivate();

        void EnterStandby();

        void* GetComponent(const char* pchComponentNameAndVersion);

        void DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize);

        DriverPose_t GetPose();

        void RunFrame();

    private:
        uint32_t driverId;
        VRInputComponentHandle_t joystick_y;
        VRInputComponentHandle_t trackpad_y;
        VRInputComponentHandle_t joystick_x;
        VRInputComponentHandle_t trackpad_x;

};

#endif /* ControllerDevice.hpp */