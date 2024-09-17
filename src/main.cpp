#include "Device.hpp"
#include <print>
#include <iostream>

using namespace Intuos;

int main()
{
    std::vector<Device::WacomDevice> WacomDevices = Device::GetWacomDevices();

    std::println("Found {} Wacom device(s)", WacomDevices.size());

    if (WacomDevices.empty())
    {
        std::println("No wacom devices found");
        return 0;
    }

    Device::WacomDevice CurrentDevice = WacomDevices.front();
    if (WacomDevices.size() > 1)
    {
        CurrentDevice = WacomDevices.front();

        std::println("Currently Selected Device");
        std::println("Product Id: {}\n", CurrentDevice.HidAttributes.ProductID);
        std::wprintf(L"Product Name: %s\n", CurrentDevice.ProductName.c_str());

        std::println("\nSelect a device >");

        for (size_t i = 0; i < WacomDevices.size(); i++)
        {
            std::wprintf(L"%zd: %d %s\n", i, WacomDevices[i].HidAttributes.ProductID, WacomDevices[i].ProductName.c_str());
        }

        size_t DeviceIndex = 0;
        std::cin >> DeviceIndex;

        if (DeviceIndex >= WacomDevices.size())
        {
            std::println("Invalid device index");
            return 0;
        }

        CurrentDevice = WacomDevices[DeviceIndex];
    }

    std::println("Selected Device");
    std::println("Product Id: {}", CurrentDevice.HidAttributes.ProductID);
    std::wprintf(L"Product Name: %s\n", CurrentDevice.ProductName.c_str());

    Device::CaptureReports(CurrentDevice.DeviceHandle);

    for (Device::WacomDevice& device : WacomDevices)
    {
        CloseHandle(device.DeviceHandle);
    }
    return 0;
}