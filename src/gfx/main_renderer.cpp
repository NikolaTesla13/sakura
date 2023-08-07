//
// Created by Asandei Stefan on 07.08.2023.
//

#include "main_renderer.h"

namespace Sakura {
    MainRenderer::MainRenderer(const Ref<Window>& window) {
        m_Context = new WGPUContext(*window.get());

        wgpu::TextureFormat swapChainFormat = wgpu::TextureFormat::BGRA8Unorm;
        wgpu::SwapChainDescriptor swapChainDesc = {};
        swapChainDesc.width = 640;
        swapChainDesc.height = 480;
        swapChainDesc.usage = wgpu::TextureUsage::RenderAttachment;
        swapChainDesc.format = swapChainFormat;
        swapChainDesc.presentMode = wgpu::PresentMode::Fifo;

        m_SwapChain = CreateRef<wgpu::SwapChain>(
                m_Context->GetDevice()->createSwapChain(*m_Context->GetSurface().get(), swapChainDesc)
        );
    }

    void MainRenderer::Draw() {
        wgpu::TextureView nextTexture = m_SwapChain->getCurrentTextureView();
        WGPU_CHECK(nextTexture);

        wgpu::CommandEncoderDescriptor commandEncoderDesc{};
        commandEncoderDesc.label = "Command Encoder";
        wgpu::CommandEncoder encoder = m_Context->GetDevice()->createCommandEncoder(commandEncoderDesc);

        WGPURenderPassColorAttachment renderPassColorAttachment = {};
        renderPassColorAttachment.view = nextTexture;
        renderPassColorAttachment.resolveTarget = nullptr;
        renderPassColorAttachment.loadOp = wgpu::LoadOp::Clear;
        renderPassColorAttachment.storeOp = wgpu::StoreOp::Store;
        renderPassColorAttachment.clearValue = wgpu::Color{ 0.9, 0.1, 0.2, 1.0 };

        wgpu::RenderPassDescriptor renderPassDesc{};
        renderPassDesc.colorAttachmentCount = 1;
        renderPassDesc.colorAttachments = &renderPassColorAttachment;
        renderPassDesc.depthStencilAttachment = nullptr;
        renderPassDesc.timestampWriteCount = 0;
        renderPassDesc.timestampWrites = nullptr;

        wgpu::RenderPassEncoder renderPass = encoder.beginRenderPass(renderPassDesc);
        renderPass.end();

        nextTexture.release();

        wgpu::CommandBufferDescriptor cmdBufferDescriptor{};
        cmdBufferDescriptor.label = "Command Buffer";
        wgpu::CommandBuffer command = encoder.finish(cmdBufferDescriptor);
        m_Context->GetQueue().submit(command);

        m_SwapChain->present();
    }

    void MainRenderer::Destroy() {
        delete m_Context;
    }
}