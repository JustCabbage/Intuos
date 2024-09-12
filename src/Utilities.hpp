#pragma once
#include <windows.h>
#include <cstdint>

namespace Intuos::Utilities
{
    struct Vector2i
    {
        std::uint32_t x;
        std::uint32_t y;
    };
    void SimulateMouseMovement(const Vector2i& CursorPosition, const std::uint32_t ScreenWidth, const std::uint32_t ScreenHeight);
    Vector2i MapToScreenCoordinates(std::uint16_t DeviceX, std::uint16_t DeviceY, const std::uint32_t ScreenWidth, const std::uint32_t ScreenHeight);
    void HoldMouse();
    void ReleaseMouse();
} // namespace Intuos::Utilities