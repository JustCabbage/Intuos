#pragma once
#include <windows.h>
#include <SetupAPI.h>
#include <hidsdi.h>
#include <vector>
#include <iostream>

namespace Intuos::Device
{
    struct WacomDevice
    {
        HANDLE DeviceHandle;
        HIDD_ATTRIBUTES HidAttributes;
        std::wstring ProductName;
    };
    std::vector<WacomDevice> GetWacomDevices();
    void CaptureReports(HANDLE DeviceHandle);
} // namespace Intuos::Device