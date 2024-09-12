#include "DeviceDefinitions.hpp"
#include "Device.hpp"
#include "Utilities.hpp"

namespace Intuos::Device
{
    std::vector<WacomDevice> GetWacomDevices()
    {
        GUID HidGUID = {};
        HidD_GetHidGuid(&HidGUID);

        HDEVINFO DeviceInfoSet = SetupDiGetClassDevs(&HidGUID, nullptr, nullptr, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
        if (DeviceInfoSet == INVALID_HANDLE_VALUE)
        {
            std::cerr << "GetWacomDevices: SetupDiGetClassDevs failed\n";
            return {};
        }

        SP_DEVICE_INTERFACE_DATA DeviceInterfaceData = {};
        DeviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

        std::vector<WacomDevice> WacomDevices = {};

        for (DWORD DeviceIndex = 0; SetupDiEnumDeviceInterfaces(DeviceInfoSet, nullptr, &HidGUID, DeviceIndex, &DeviceInterfaceData); DeviceIndex++)
        {
            DWORD RequiredSize = 0;
            SetupDiGetDeviceInterfaceDetail(DeviceInfoSet, &DeviceInterfaceData, nullptr, 0, &RequiredSize, nullptr);

            PSP_DEVICE_INTERFACE_DETAIL_DATA DeviceInterfaceDetailData = reinterpret_cast<PSP_DEVICE_INTERFACE_DETAIL_DATA>(new char[RequiredSize]);
            DeviceInterfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

            if (!SetupDiGetDeviceInterfaceDetail(DeviceInfoSet, &DeviceInterfaceData, DeviceInterfaceDetailData, RequiredSize, nullptr, nullptr))
            {
                std::cerr << "GetWacomDevices: SetupDiGetDeviceInterfaceDetail failed\n";
                delete[] DeviceInterfaceDetailData;
                continue;
            }

            HANDLE DeviceHandle =
                CreateFile(DeviceInterfaceDetailData->DevicePath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, 0, nullptr);
            if (DeviceHandle == INVALID_HANDLE_VALUE)
            {
                delete[] DeviceInterfaceDetailData;
                continue;
            }

            HIDD_ATTRIBUTES HidAttributes = {};
            HidD_GetAttributes(DeviceHandle, &HidAttributes);

            if (HidAttributes.VendorID != WACOM_VENDOR_ID)
            {
                CloseHandle(DeviceHandle);
                delete[] DeviceInterfaceDetailData;
                continue;
            }

            WCHAR ProductName[MAX_PATH] = {};
            if (!HidD_GetProductString(DeviceHandle, ProductName, sizeof(ProductName)))
            {
                std::cerr << "GetWacomDevices: HidD_GetProductString failed\n";
            }

            const WacomDevice Device = {DeviceHandle, HidAttributes, ProductName};
            WacomDevices.push_back(Device);

            delete[] DeviceInterfaceDetailData;
        }

        SetupDiDestroyDeviceInfoList(DeviceInfoSet);
        return WacomDevices;
    }
    void CaptureReports(HANDLE DeviceHandle)
    {
        std::cout << "Reading reports...\n";
        BYTE ReportBuffer[REPORT_SIZE];
        DWORD BytesRead = 0;

        const std::uint32_t ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
        const std::uint32_t ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

        while (ReadFile(DeviceHandle, ReportBuffer, sizeof(ReportBuffer), &BytesRead, nullptr))
        {
            WacomReport Report = *reinterpret_cast<const WacomReport*>(ReportBuffer);
            const Utilities::Vector2i ScreenCoordinates = Utilities::MapToScreenCoordinates(Report.X, Report.Y, ScreenWidth, ScreenHeight);
            Utilities::SimulateMouseMovement(ScreenCoordinates, ScreenWidth, ScreenHeight);

            if (Report.ProximityFlag == WACOM_TOUCH_FLAG)
            {
                Utilities::HoldMouse();
            }
            else
            {
                Utilities::ReleaseMouse();
            }
        }
    }
} // namespace Intuos::Device