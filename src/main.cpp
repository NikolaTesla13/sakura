#include <webgpu/webgpu.hpp>
#include <glfw3webgpu.h>
#include <GLFW/glfw3.h>

#include <iostream>

using namespace wgpu;

int main (int, char**) {
    Instance instance = createInstance(InstanceDescriptor{});
    if (!instance) {
        std::cerr << "Could not initialize WebGPU!" << std::endl;
        return 1;
    }

    if (!glfwInit()) {
        std::cerr << "Could not initialize GLFW!" << std::endl;
        return 1;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(640, 480, "Learn WebGPU", nullptr, nullptr);
    if (!window) {
        std::cerr << "Could not open window!" << std::endl;
        return 1;
    }

    std::cout << "Requesting adapter..." << std::endl;
    Surface surface = glfwGetWGPUSurface(instance, window);
    RequestAdapterOptions adapterOpts{};
    adapterOpts.compatibleSurface = surface;
    Adapter adapter = instance.requestAdapter(adapterOpts);
    std::cout << "Got adapter: " << adapter << std::endl;

    std::cout << "Requesting device..." << std::endl;
    DeviceDescriptor deviceDesc{};
    deviceDesc.label = "My Device";
    deviceDesc.requiredFeaturesCount = 0;
    deviceDesc.requiredLimits = nullptr;
    deviceDesc.defaultQueue.label = "The default queue";
    Device device = adapter.requestDevice(deviceDesc);
    std::cout << "Got device: " << device << std::endl;

    Queue queue = device.getQueue();

    auto onDeviceError = [](WGPUErrorType type, char const* message, void* /* pUserData */) {
        std::cout << "Uncaptured device error: type " << type;
        if (message) std::cout << " (" << message << ")";
        std::cout << std::endl;
    };
    wgpuDeviceSetUncapturedErrorCallback(device, onDeviceError, nullptr /* pUserData */);

    std::cout << "Creating swapchain device..." << std::endl;

    TextureFormat swapChainFormat = TextureFormat::BGRA8Unorm;
    SwapChainDescriptor swapChainDesc = {};
    swapChainDesc.width = 640;
    swapChainDesc.height = 480;
    swapChainDesc.usage = TextureUsage::RenderAttachment;
    swapChainDesc.format = swapChainFormat;
    swapChainDesc.presentMode = PresentMode::Fifo;
    SwapChain swapChain = device.createSwapChain(surface, swapChainDesc);
    std::cout << "Swapchain: " << swapChain << std::endl;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        TextureView nextTexture = swapChain.getCurrentTextureView();
        if (!nextTexture) {
            std::cerr << "Cannot acquire next swap chain texture" << std::endl;
            return 1;
        }

        CommandEncoderDescriptor commandEncoderDesc{};
        commandEncoderDesc.label = "Command Encoder";
        CommandEncoder encoder = device.createCommandEncoder(commandEncoderDesc);

        RenderPassDescriptor renderPassDesc{};

        WGPURenderPassColorAttachment renderPassColorAttachment = {
                .view = nextTexture,
                .resolveTarget = nullptr,
                .loadOp = LoadOp::Clear,
                .storeOp = StoreOp::Store,
                .clearValue = Color{ 0.2, 0.1, 0.9, 1.0}
        };
        renderPassDesc.colorAttachmentCount = 1;
        renderPassDesc.colorAttachments = &renderPassColorAttachment;

        renderPassDesc.depthStencilAttachment = nullptr;
        renderPassDesc.timestampWriteCount = 0;
        renderPassDesc.timestampWrites = nullptr;
        RenderPassEncoder renderPass = encoder.beginRenderPass(renderPassDesc);
        renderPass.end();

        nextTexture.release();

        CommandBufferDescriptor cmdBufferDescriptor{};
        cmdBufferDescriptor.label = "Command buffer";
        CommandBuffer command = encoder.finish(cmdBufferDescriptor);
        queue.submit(command);

        swapChain.present();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}