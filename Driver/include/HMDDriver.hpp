#ifndef HMD_DEVICE
#define HMD_DEVICE

#include <openvr_driver.h>
#include <cstring>
#ifdef __windows__
#include <Windows.h>
#else
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#endif

using namespace vr;

class HMDDriver : public TrackedDeviceServerDriver
{
    public:
        EVRInitError Activate(uint32_t unObjectId);

        void Deactivate();

        void EnterStandby();

        void* GetComponent(const char* pchRequestAndVersion);

        void DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize);

        DriverPose_t GetPose();

        void RunFrame();


    private:
        uint32_t driverId;
};

#endif /* HMDDevice.hpp */