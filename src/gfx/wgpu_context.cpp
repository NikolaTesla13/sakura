//
// Created by Asandei Stefan on 07.08.2023.
//

#include "wgpu_context.h"

namespace Sakura {
    WGPUContext::WGPUContext(const Window& window) {
        auto instanceDesc = wgpu::InstanceDescriptor {};
        instanceDesc.nextInChain = nullptr;

        m_Instance = CreateRef<wgpu::Instance>(createInstance(instanceDesc));
        WGPU_CHECK(m_Instance)

        m_Surface = CreateRef<wgpu::Surface>(window.GetWGPUSurface(*m_Instance.get()));
        auto adapterOpts = wgpu::RequestAdapterOptions {};

        adapterOpts.compatibleSurface = *m_Surface.get();
        m_Adapter = CreateRef<wgpu::Adapter>(m_Instance->requestAdapter(adapterOpts));

        auto deviceDesc = wgpu::DeviceDescriptor {};
        deviceDesc.label = "Primary Device";
        deviceDesc.requiredFeaturesCount = 0;
        deviceDesc.requiredLimits = nullptr;
        deviceDesc.defaultQueue.label = "Default Queue";
        m_Device = CreateRef<wgpu::Device>(m_Adapter->requestDevice(deviceDesc));

        SetDeviceCallbacks();
    }

    void WGPUContext::SetDeviceCallbacks() {
        auto callback = [](auto reason, char const * message) -> void {
            std::cout << "Error: type " << reason;
            if (message)
                std::cout << " (message: " << message << ")";
            std::cout << '\n';
        };

        m_Device->setUncapturedErrorCallback(callback);
        m_Device->setDeviceLostCallback(callback);
    }

    WGPUContext::~WGPUContext() {
        m_Device->destroy();

        m_Adapter->release();
        m_Instance->release();
    }
}