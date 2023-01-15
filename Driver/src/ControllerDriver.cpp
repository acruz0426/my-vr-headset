#include <include/ControllerDriver.hpp>

EVRInitError ControllerDriver::Activate(uint32_t unObjectId)
{
    uint32_t driverId = unObjectId;

    PropertyContainerHandle_t props = VRProperties()->TrackedDeviceToPropertyContainer(driverId);
}

void Deactivate()
{
    // pass   
}

void EnterStandby()
{
    // pass
}

void* GetComponent(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize)
{
    // pass
}

DriverPose_t GetPose()
{
    // pass
}

void RunFrame()
{
    // pass
}