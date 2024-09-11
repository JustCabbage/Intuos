#include "Utilities.hpp"
#include "DeviceDefinitions.hpp"

namespace Intuos::Utilities
{
    void SendMouseInput(const Vector2i& CursorPosition, const std::uint32_t ScreenWidth, const std::uint32_t ScreenHeight)
    {
        // Windows uses a 16-bit integer to represent the absolute position of the cursor :p hence the 65536.0f
        float NormalizedX = (CursorPosition.x * 65536.0f) / ScreenWidth;
        float NormalizedY = (CursorPosition.y * 65536.0f) / ScreenHeight;

        INPUT Input = {};
        Input.type = INPUT_MOUSE;
        Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
        Input.mi.dx = static_cast<LONG>(NormalizedX);
        Input.mi.dy = static_cast<LONG>(NormalizedY);
        Input.mi.mouseData = NULL;
        Input.mi.dwExtraInfo = NULL;
        Input.mi.time = NULL;
        SendInput(1, &Input, sizeof(INPUT));
    }
    Vector2i MapToScreenCoordinates(std::uint16_t DeviceX, std::uint16_t DeviceY, const std::uint32_t ScreenWidth, const std::uint32_t ScreenHeight)
    {
        float NormalizedX = static_cast<float>(DeviceX - DEVICE_X_MIN) / (DEVICE_X_MAX - DEVICE_X_MIN);
        float NormalizedY = static_cast<float>(DeviceY - DEVICE_Y_MIN) / (DEVICE_Y_MAX - DEVICE_Y_MIN);
        std::uint32_t MappedX = static_cast<uint32_t>(NormalizedX * ScreenWidth);
        std::uint32_t MappedY = static_cast<uint32_t>(NormalizedY * ScreenHeight);
        return {MappedX, MappedY};
    }
    void HoldMouse()
    {
        INPUT Input = {};
        Input.type = INPUT_MOUSE;
        Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        SendInput(1, &Input, sizeof(INPUT));
    }
    void ReleaseMouse()
    {
        INPUT Input = {};
        Input.type = INPUT_MOUSE;
        Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
        SendInput(1, &Input, sizeof(INPUT));
    }
} // namespace Intuos::Utilities