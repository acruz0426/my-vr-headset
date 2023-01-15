#include <include/HMDDriver.hpp>

EVRInitError HMDDriver::Activate(uint32_t unObjectId)
{
    driverId = unObjectId;

    PropertyContainerHandle_t props = VRProperties()->TrackedDeviceToPropertyContainer(driverId);

    VRProperties()->SetStringProperty(props, Prop_InputProfilePath_String, "Brogurt/input/hmd_profile.json");
    VRProperties()->SetUint64Property(props, Prop_CurrentUniverseId_Uint64, 2); //This is an HMD specific property, so HMD is applied...I think
}

void HMDDriver::Deactivate()
{
    // pass  
    driverId = k_unTrackedDeviceIndexInvalid; 
}

void HMDDriver::EnterStandby()
{
    // pass
}

void* HMDDriver::GetComponent(const char * pchComponentNameAndVersion)
{
    if (strcmp(IVRDriverInput_Version, pchComponentNameAndVersion) == 0)
	{
		return this;
	}
	return NULL;
}

DriverPose_t HMDDriver::GetPose()
{
    //Code for Windows OS
#ifdef __window__

    //Need to check if code actually works.
    char portName[10];
    HANDLE hSerial;
    DWORD bytesWritten;
    DWORD bytesRead;
    char data[] = "getBoardId";
    char buffer[256];

    //Find COM port that is using arduino
    for (int i = 0; i < 256; i++)
    {
        sprintf(portName, "COM%d", i);
        hSerial = CreateFile(portName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hSerial == INVALID_HANDLE_VALUE) {
            continue;
        }

        WriteFile(hSerial, data, sizeof(data), &bytesWritten, NULL);

        ReadFile(hSerial, buffer, sizeof(buffer), &bytesRead, NULL);

        if (strcmp(buffer, "Arduino Uno") == 0)
        {
            std::cout << "Arduino Uno found on port " << portName << std::endl;
            break;
        }
        CloseHandle(hSerial);
    }

    //Create serial communication with arduino board and read in data from arduino
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    GetCommState(hSerial, &dcbSerialPrarams);
    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    SetCommState(hSerial, &dcbSerialParams);

    ReadFile(hSerial, buffer, sizeof(buffer), &bytesRead, NULL);
    std::cout << "Received: " << buffer << std::endl;
    
    
    DriverPose_t = ;
#else
    //Code for Linux OS
    DriverPose_t = ;
#endif
}

void HMDDriver::RunFrame()
{
    // pass
}

void HMDDriver::DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize)
{
    if (unResponseBufferSize >= 1)
	{
		pchResponseBuffer[0] = 0;
	}
}