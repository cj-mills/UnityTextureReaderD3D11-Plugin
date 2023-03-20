// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include <d3d11.h>
#include <stdint.h>
#include "IUnityGraphics.h"
#include "IUnityInterface.h"
#include "IUnityGraphicsD3D11.h"

// Global pointers to Unity interfaces.
static IUnityInterfaces* s_UnityInterfaces = nullptr;
static IUnityGraphicsD3D11* s_D3D11 = nullptr;

// Loads the plugin and initializes the interfaces.
extern "C" UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API UnityPluginLoad(IUnityInterfaces * unityInterfaces)
{
    s_UnityInterfaces = unityInterfaces;
    s_D3D11 = s_UnityInterfaces->Get<IUnityGraphicsD3D11>();
}

// Unloads the plugin and resets the interface pointers.
extern "C" UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API UnityPluginUnload()
{
    s_D3D11 = nullptr;
    s_UnityInterfaces = nullptr;
}

// Retrieves pixel data from the texture.
extern "C" UNITY_INTERFACE_EXPORT void* UNITY_INTERFACE_API GetPixelDataFromTexture(void* texturePtr)
{
    if (s_D3D11 == nullptr) return nullptr;

    // Get device and context from the D3D11 interface.
    ID3D11Device* device = s_D3D11->GetDevice();
    ID3D11DeviceContext* deviceContext = nullptr;
    device->GetImmediateContext(&deviceContext);

    // Cast texture pointer and get its description.
    ID3D11Texture2D* texture = static_cast<ID3D11Texture2D*>(texturePtr);
    D3D11_TEXTURE2D_DESC desc;
    texture->GetDesc(&desc);

    // Update texture description for staging.
    desc.BindFlags = 0;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    desc.Usage = D3D11_USAGE_STAGING;
    desc.MiscFlags = 0;

    // Create a staging texture.
    ID3D11Texture2D* stagingTexture = nullptr;
    HRESULT hr = device->CreateTexture2D(&desc, nullptr, &stagingTexture);
    if (FAILED(hr))
    {
        deviceContext->Release();
        return nullptr;
    }

    // Copy the texture to the staging texture.
    deviceContext->CopyResource(stagingTexture, texture);

    // Map the staging texture to access its data.
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    hr = deviceContext->Map(stagingTexture, 0, D3D11_MAP_READ, 0, &mappedResource);
    if (FAILED(hr))
    {
        stagingTexture->Release();
        deviceContext->Release();
        return nullptr;
    }

    // Copy the pixel data from the mapped resource.
    uint8_t* pixelData = new uint8_t[mappedResource.RowPitch * desc.Height];
    memcpy(pixelData, mappedResource.pData, mappedResource.RowPitch * desc.Height);

    // Unmap and release resources.
    deviceContext->Unmap(stagingTexture, 0);
    stagingTexture->Release();
    deviceContext->Release();

    return pixelData;
}

// Frees the memory allocated for pixel data.
extern "C" UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API FreePixelData(void* pixelData)
{
    if (pixelData != nullptr)
    {
        delete[] static_cast<uint8_t*>(pixelData);
    }
}

