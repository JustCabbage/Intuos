#pragma once
#include <cstdint>

#define WACOM_VENDOR_ID 0x56A // Wacom Co., Ltd
#define REPORT_SIZE 192       // Found working for Intuos S (CTL-4100)
#define DEVICE_X_MIN 0
#define DEVICE_X_MAX 15200
#define DEVICE_Y_MIN 0
#define DEVICE_Y_MAX 9500

#define WACOM_MAGIC_NUMBER 0x10
#define WACOM_PROXIMITY_FLAG 0x60
#define WACOM_TOUCH_FLAG 0x61

// Endianness shenanigans
#pragma pack(push, 1)
struct WacomReport
{
    std::int8_t MagicNumber;   // 0x10 through my testing
    std::int8_t ProximityFlag; // 0x40 when reports are being fed, 0x60 when the pen is in proximity, 0x61 when the pen is touching the tablet

    std::int16_t X;
    std::uint8_t Unknown; // 0x00 through my testing (not sure what this is for)
    std::int16_t Y;
    std::int8_t TheRest[REPORT_SIZE - 6]; // The rest of the report I don't care about
};
#pragma pack(pop)