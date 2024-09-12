#include "Device.hpp"

using namespace Intuos;

int main()
{
    std::vector<Device::WacomDevice> WacomDevices = Device::GetWacomDevices();

    std::cout << "Found " << WacomDevices.size() << " Wacom device(s)\n";

    if (WacomDevices.empty())
    {
        std::cout << "No Wacom devices found\n";
        return 0;
    }

    Device::WacomDevice CurrentDevice = WacomDevices.front();
    if (WacomDevices.size() > 1)
    {
        CurrentDevice = WacomDevices.front();
        std::cout << "Currently Selected Device\n";
        std::cout << "Product ID: " << CurrentDevice.HidAttributes.ProductID << "\n\n";
        std::wcout << "Product Name: " << std::wstring(CurrentDevice.ProductName.begin(), CurrentDevice.ProductName.end()) << "\n";

        std::cout << "\nSelect a device >\n";

        for (size_t i = 0; i < WacomDevices.size(); i++)
        {
            std::wcout << i << ": " << WacomDevices[i].HidAttributes.ProductID << " " << std::wstring(WacomDevices[i].ProductName.begin(), WacomDevices[i].ProductName.end())
                       << "\n";
        }

        size_t DeviceIndex = 0;
        std::cin >> DeviceIndex;

        if (DeviceIndex >= WacomDevices.size())
        {
            std::cout << "Invalid device index\n";
            return 0;
        }

        CurrentDevice = WacomDevices[DeviceIndex];
    }

    std::cout << "Selected Device\n";
    std::cout << "Product ID: " << CurrentDevice.HidAttributes.ProductID << "\n";
    std::wcout << "Product Name: " << std::wstring(CurrentDevice.ProductName.begin(), CurrentDevice.ProductName.end()) << "\n";

    Device::CaptureReports(CurrentDevice.DeviceHandle);

    for (auto& device : WacomDevices)
    {
        CloseHandle(device.DeviceHandle);
    }
    return 0;
}