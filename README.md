# Intuos

Intuos is a Windows-based (for now) HID driver for the [Wacom Intuos S](https://estore.wacom.com/en-gb/wacom-intuos-small-black-ctl-4100k-s.html)

It's built to be as lightweight as possible, although I know drivers definitely already exist for this device, I just wanted something I didnt have to care about, nor configure much. Currently this maps the full tablet area to the full screen, and binds the pen tip to the left mouse button. It works as you'd expect.

There are some features I wish to add in the future, and while this is working, it is by no means complete.

## Build

> To build Intuos, you will need to have CMake installed on your system. If you don't have CMake installed, you can download it from the official [CMake website](https://cmake.org/download/) and follow the installation instructions for your operating system.

Once you have CMake, you can follow these steps:

1. Clone the repository: `git clone --recursive https://github.com/JustCabbage/Intuos.git`
2. Navigate to the project directory: `cd Intuos`
3. Create a build directory: `mkdir build && cd build`
4. Generate the build files: `cmake ..`
5. Build the project: `cmake --build .`

**Please ensure you have the necessary build tools installed for your system. If you are using Windows, you may need to have Visual Studio installed with the C++ workload. For Linux, make sure you have the build-essential package installed.**

As mentioned previously, Intuos currently only supports Windows.

> If you encounter any issues or have any questions, please feel free to [open an issue](https://github.com/JustCabbage/Intuos/issues).

## License

Intuos is currently licensed under the [MIT License](https://github.com/JustCabbage/Intuos/blob/master/LICENSE).
