# UnityTextureReaderD3D11-Plugin

This repository contains the Visual Studio project for the UnityTextureReaderD3D11 plugin, a native plugin for Unity that enables efficient access to pixel data from Direct3D11 textures in Unity.

## Overview

The UnityTextureReaderD3D11 plugin allows you to efficiently read pixel data from Direct3D11 textures in Unity. This can be useful when you need to access texture data for various purposes, such as image processing or exporting textures.

The plugin is designed to work with the [UnityTextureReaderD3D](https://github.com/cj-mills/UnityTextureReaderD3D) package, which provides a higher-level C# interface for Unity projects.

## Building the plugin

To build the UnityTextureReaderD3D11 plugin, you will need Visual Studio with support for C++ and the Windows SDK installed. Follow these steps:

1. Clone or download this repository.
2. Open the Visual Studio solution file (`UnityTextureReaderD3D11.sln`) in Visual Studio.
3. Select the desired build configuration (e.g., Debug or Release) and platform (e.g., x64).
4. Build the solution by pressing `Ctrl+Shift+B` or selecting `Build > Build Solution` from the menu.

Upon successful build, you will find the `UnityTextureReaderD3D11.dll` file in the output folder (e.g., `x64/Release` or `x64/Debug`).

## Usage

To use the UnityTextureReaderD3D11 plugin in your Unity project, follow the instructions in the [UnityTextureReaderD3D](https://github.com/yourusername/UnityTextureReaderD3D) package repository.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
